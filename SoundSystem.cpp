//
//  SoundSystem.cpp
//  
//
//  Created by easy proger on 10.07.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "SoundSystem.h"


SoundSystem::SoundSystem() {
    lastPlayedTrack = 0;
    currentIndxForCache = -1;
    initializeOpenAL();
    
    
}

SoundSystem::~SoundSystem() {
    destroyOpenAL();
}

bool SoundSystem::initializeOpenAL()
{
    // Позиция слушателя.
    ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
    
    // Скорость слушателя.
    ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
    
    // Ориентация слушателя. (Первые 3 элемента – направление «на», последние 3 – «вверх»)
    ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
    
    // Открываем заданное по умолчанию устройство
    pDevice = alcOpenDevice(NULL);
    // Проверка на ошибки
    
    ALenum error = alGetError();
    
    if (AL_NO_ERROR != error) {
        printf("Error %d when attemping to open device", error);
    }
    
    if (!pDevice)
    {
        printf("Default sound device not present");
        return false;
    }
    // Создаем контекст рендеринга
    pContext = alcCreateContext(pDevice, NULL);

     error = alGetError();
    if (error != AL_NO_ERROR) return false;
    
    // Делаем контекст текущим
    alcMakeContextCurrent(pContext);
    
    // Устанавливаем параметры слушателя
    // Позиция
    alListenerfv(AL_POSITION,    ListenerPos);
    // Скорость
    alListenerfv(AL_VELOCITY,    ListenerVel);
    // Ориентация
    alListenerfv(AL_ORIENTATION, ListenerOri);
    return true;
}
std::string GetFileExtension(const std::string& FileName)
{
    if(FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of(".")+1);
    return "";
}



int SoundSystem::addFile(char*pathToFile) {
    std::string fileExt(pathToFile);
    if(fileExt.find_last_of(".") != std::string::npos) {
        fileExt = fileExt.substr(fileExt.find_last_of(".")+1);
        
        if (std::strcmp(fileExt.c_str(), "WAV") == 0) {
            // check for extension example
        }else {
            //return -1;
        }
        
    }else {
        return -1;
    }
    
    
    SoundData *data = new SoundData();
    data->loaded = false;
    data->filePath = pathToFile;
    fileLibs.push_back(data);
    
    
    return fileLibs.size()-1;
}


void SoundSystem::playSound(uint id) {
    if (id >= fileLibs.size()) return;
    
    SoundData *data = fileLibs[id];
    
    errors.clear();
    
    if (!data->loaded) {
        if (loadedTracks.size() >= MAX_SOUNDS_LOAD) {
            currentIndxForCache++;
            if (currentIndxForCache >= MAX_SOUNDS_LOAD) {
                currentIndxForCache = 0;
            }
            uint id_destroy = loadedTracks[currentIndxForCache];
            SoundData *dataToDestroy = fileLibs[id_destroy];
            
            if (dataToDestroy->loaded) {
                destroySound(dataToDestroy);
            }
            loadedTracks[currentIndxForCache] = id;
        }else {
            loadedTracks.push_back(id);
        }
        

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		FILE * fi = fopen( data->filePath.c_str(),"rb");

	    if(fi == NULL)
		    return;

		fseek(fi,0,SEEK_END);
	    uint fileSize = ftell(fi);
		fseek(fi,0,SEEK_SET);

		unsigned char *buffer = (unsigned char *)malloc(fileSize);
		if (fread(buffer, 1, fileSize, fi) != fileSize)
	    {
		    free(buffer);
		    fclose(fi);
		    return;
	    }
	    fclose(fi);

#else
		 AudioFileID fileID = 0;
        CFURLRef url = CFURLCreateWithString(kCFAllocatorDefault, CFStringCreateWithCString(kCFAllocatorDefault, data->filePath.c_str(), NULL), NULL);
        OSStatus result = AudioFileOpenURL(url, kAudioFileReadPermission, 0, &fileID);
        errors.push_back(result);
        
        
        UInt32 fileSize = 0;
        UInt32 propSize = sizeof(UInt64);
        result = noErr;
        result = AudioFileGetProperty(fileID, kAudioFilePropertyAudioDataByteCount, &propSize, &fileSize);
        errors.push_back(result);
        
        
        unsigned char *buffer = (unsigned char *)malloc(fileSize);
        result = noErr;
        result = AudioFileReadBytes(fileID, false, 0, &fileSize, buffer);
        errors.push_back(result);
        AudioFileClose(fileID);
#endif
        
        
        
        
        
        data->bufferID = 0;
        
        alGenBuffers(1, &data->bufferID);
        alBufferData(data->bufferID, AL_FORMAT_STEREO16, buffer, fileSize, 44100);
        
        free(buffer);
        
        data->sourceID = 0;
        alGenSources(1, &data->sourceID);
        alSourcei(data->sourceID, AL_BUFFER, data->bufferID);
        alSourcef(data->sourceID, AL_PITCH, 1.0f);
        alSourcef(data->sourceID, AL_GAIN, 1.0f);
        alSourcei(data->sourceID, AL_LOOPING, AL_FALSE);
        printf("created buffer ID:%d %d\n",data->bufferID,data->sourceID);
        data->loaded = true;
    }
    
    
    alSourcePlay(data->sourceID);
    
    
    
}

void SoundSystem::destroySound(SoundData*d) {
    
    alSourceStop(d->sourceID);
    
    alBufferData(d->bufferID, AL_FORMAT_STEREO16, 0, 0, 0);
    alSourcei(d->sourceID, AL_BUFFER, 0);
    
    alDeleteBuffers(1, &d->bufferID);
    alDeleteSources(1, &d->sourceID);
    
    
    
    printf("removed buffer ID:%d %d\n",d->bufferID,d->sourceID);
    
    d->loaded = false;
}

int SoundSystem::loadFile(char*pathToFile) {
    
    std::string fileExt(pathToFile);
    if(fileExt.find_last_of(".") != std::string::npos) {
        fileExt = fileExt.substr(fileExt.find_last_of(".")+1);
        
        if (std::strcmp(fileExt.c_str(), "WAV") == 0) {
            
        }else {
            return -1;
        }
        
    }else {
        return -1;
    }
    
    
    FILE* file = fopen(pathToFile, "rb");
	if (!file) {
		return -1;
	}

    

    
    return -1;
}


void SoundSystem::destroyOpenAL()
{
    // Очищаем все буффера
    //for (TBuf::iterator i = Buffers.begin(); i != Buffers.end(); i++)
    //    alDeleteBuffers(1, &i->second.ID);
    
    for (int i = 0; i < loadedTracks.size(); i++) {
        uint id = loadedTracks[i];
        SoundData *d = fileLibs[id];
        if (d->loaded) {
            destroySound(d);
        }
		delete d;
    }
    
    // Выключаем текущий контекст
    alcMakeContextCurrent(NULL);
    // Уничтожаем контекст
    alcDestroyContext(pContext);
    // Закрываем звуковое устройство
    alcCloseDevice(pDevice);
}