//
//  Textures.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 13.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "Texture.h"

#include "XTypes.h"

void Texture::createTexture() {
    GLubyte pixels[4*3] = {
        255, 255, 255,
        225, 225, 225,
        155, 155, 155,
        255, 255, 255
    };
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &this->texID);
    glBindTexture(GL_TEXTURE_2D, this->texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    countUsed = 1;
	_isDamaged = false;
    this->width  = 2;
    this->height = 2;
    this->formatTexture = GL_TEXTURE_2D;
}

void Texture::reloadTexture() {
    createTexture(pathForTexture);
}


int Texture::createTexture(const std::string &path) {
    pathForTexture.assign(path.begin(), path.end());
    

    long m_Size = 0;
    bool m_bOpen = false;
    char* m_pData = NULL;
    
    FILE* pFile = fopen(path.c_str(), "rb");
    if (pFile)
    {
        // Get the file size
        fseek(pFile, 0, SEEK_END);
        m_Size = ftell(pFile);
        fseek(pFile, 0, SEEK_SET);
        
        // read the data, append a 0 byte as the data might represent a string
        char* pData = new char[m_Size + 1];
        pData[m_Size] = '\0';
        size_t BytesRead = fread(pData, 1, m_Size, pFile);
        
        if (BytesRead != m_Size)
        {
            delete [] pData;
            m_Size = 0;
        }
        else
        {
            m_pData = pData;
            m_bOpen = true;
        }
        fclose(pFile);
    }else {
        // cant open need create clear texture // mb after some time system change data and we will see normal tex ))
        _isDamaged = false;
        countUsed = 1;
        createTexture();
        return 2;
    }
    
    if (!m_bOpen) {
        texID = 0;
        printf("load texture error\n");
        return 0;
    }
    
    
    
    
    std::string ext = path.substr(path.find_last_of(".") + 1);
    
    uint ret = 0;
	if (std::strcmp(  ext.c_str(),"frame")==0) {
        
        FrameImageHeader*textureHeader =(FrameImageHeader*)malloc(sizeof(FrameImageHeader));
        textureHeader=(FrameImageHeader*)m_pData;
        this->width  = textureHeader->width;
        this->height = textureHeader->height;
        this->formatTexture = GL_TEXTURE_2D;
        
        if (texID != 0) {
            glBindTexture(GL_TEXTURE_2D, texID);
        }else {
            
            glGenTextures(1, &texID);
            glBindTexture(GL_TEXTURE_2D, texID);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        
        
        unsigned char*pTData = (unsigned char*)m_pData+sizeof(FrameImageHeader);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureHeader->width, textureHeader->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pTData);
        glBindTexture(GL_TEXTURE_2D, 0);
        
        _isDamaged = false;
        countUsed = 1;
        
        ret = 1;
    }else if (std::strcmp(  ext.c_str(),"pvr")==0) {
        PVRTextureHeaderV3* psTextureHeader = (PVRTextureHeaderV3*)malloc(sizeof(PVRTextureHeaderV3));
        
        uint m_uiTexture = 0;
        if (PVRTTextureLoadFromPVR(m_pData, &m_uiTexture,psTextureHeader,true) != PVR_SUCCESS) {
            printf("load PVR error\n");
            return 0;
        }
        
        if (psTextureHeader->u32MIPMapCount > 0) {
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        }else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        
        this->width  = psTextureHeader->u32Width;
        this->height = psTextureHeader->u32Height;
        this->formatTexture = GL_TEXTURE_2D;
        this->texID = m_uiTexture;
        
        
        free(psTextureHeader);
        
        _isDamaged = false;
        countUsed = 1;
        ret = 1;
    }
    
    delete [] m_pData; // delete texture data;
    
    return ret;
}


void Texture::releaseTexture() {
    if (countUsed > 0) {
        // used !
        countUsed--;
        if (countUsed <= 0 && !_isDamaged) deleteTexture();
    }else if (!_isDamaged){
        // not used and not deleted !
        deleteTexture();
    }
};

void Texture::deleteTexture() {
    texID = 0;
    glDeleteTextures(1, &texID);
    _isDamaged = true;
    countUsed = 0;
}


void Texture::setTextureID(uint formatTexture,uint texID){
    this->formatTexture = formatTexture;
    this->texID = texID;
}
uint Texture::getTextureID(){
    return texID;
}
uint Texture::getTextureFormat(){
    return formatTexture;
}
uint Texture::createClearTexture(int width,int height,uint formatTexture,uint formatBitsAndChanel,uint formatChanel,uint formatBits) {
    this->formatTexture = formatTexture;
    this->width  = width;
    this->height = height;
    glGenTextures(1, &texID);
    glBindTexture(formatTexture, texID);
    
    glTexParameteri(formatTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(formatTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(formatTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(formatTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glTexImage2D(formatTexture, 0, formatBitsAndChanel, width, height, 0, formatChanel, formatBits, 0);
    glBindTexture(formatTexture, 0);
    return texID;
}
uint Texture::createFrombufferAndUploadTexture(uint formatTexture){
    this->formatTexture = formatTexture;
    glGenTextures(1, &texID);
    glBindTexture(formatTexture, texID);
    glTexParameteri(formatTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(formatTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D( formatTexture, 0, GL_RGB, width, width, 0, GL_RGB, GL_UNSIGNED_BYTE,imageData );
    glBindTexture(formatTexture, 0);
    
    return texID;
}
