//
//  FileLoader.cpp
//  
//
//  Created by easy proger on 05.07.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "FileLoader.h"

#include "Mesh.h"
#include "SkinnedMesh.h"

#include <string>
#include "forsyth.h"

#include "FlagsForShaderCompile.h"
#include "XMatrix4Math.h"
#include "SkinningMath.h"

FileLoader::FileLoader(MeshCache*meshCache) {
    _meshCache = meshCache;
}

XAnimation* FileLoader::loadAnimation(FILE*file) {
    XAnimation*anim = NULL;
    return loadAnimation(file, anim);
}

XAnimation* FileLoader::loadAnimation(FILE*file,XAnimation*anim) {
    int lenghtName = 0;
    fread(&lenghtName,    1,    sizeof(int), file);// len name

    char* nameMesh = (char*)malloc(sizeof(char)*lenghtName+1); // alloc mem
    // loading !
    memset(nameMesh,    0, lenghtName*sizeof(char));
    fread(&nameMesh[0],    1, sizeof(char)*lenghtName, file);// load name
        
    nameMesh[lenghtName] = 0;

    std::string nameMeshStd = nameMesh;

    free(nameMesh);
    nameMesh = NULL;
        

	bool skinning = false;
	bool frameAnimation = false;

	fread(&skinning, 1, sizeof(char), file); // 
	fread(&frameAnimation, 1, sizeof(char), file); // 

	int numAnimationFrames = 0;
	fread(&numAnimationFrames,    1,    sizeof(int), file);//tx

    if (skinning) {// skinning
        int numBones = 0;
            
        fread(&numBones,    1,    sizeof(int), file);//tx

        
        SkinningAnimation *skinAnim;
        
        if (!anim) {
            skinAnim = new SkinningAnimation();
        }else {
            skinAnim = (SkinningAnimation *)anim;
        }
        
        anim = (XAnimation*)skinAnim;
        
        if (!skinAnim) return NULL;
        
	    skinAnim->skinningAnimation = true;
            
        if (skinAnim) {
            skinAnim->frames = (SkinningFrame *)malloc(sizeof(SkinningFrame)*numAnimationFrames);
            skinAnim->setNumBones(numBones);
            skinAnim->setNumAnimationFrames(numAnimationFrames);
            skinAnim->bones.resize(numBones);
            for (int f = 0; f < numAnimationFrames; f++) {
                    
                SkinningFrame*frame = &skinAnim->frames[f];
                frame->pos = (XVector3*)malloc(sizeof(XVector3)*numBones);
                frame->rot = (XVector4*)malloc(sizeof(XVector4)*numBones);
                frame->parentID = (int*)malloc(sizeof(int)*numBones);
                    
                for (int bi = 0; bi < numBones;bi++){
                    fread(&frame->parentID[bi],1, sizeof(int), file);
                    fread(&frame->pos[bi],1, sizeof(XVector3), file);
                    fread(&frame->rot[bi],1, sizeof(XVector4), file);
                    if (f == 0) {
                        skinAnim->bones[bi].boneID = bi;
                        skinAnim->bones[bi].parentID = frame->parentID[bi];
                    }
                }
            }
            sortBones(&skinAnim->bones);
        }
        anim = skinAnim;
    }
    if (frameAnimation) {
		// hm need create ? 
		if (!anim) anim = new XAnimation();

		anim->frameAnimation = true;
		anim->anim_frames = (AnimationFrame *)malloc(sizeof(AnimationFrame)*numAnimationFrames);
		anim->setNumAnimationFrames(numAnimationFrames);

		for (int f = 0; f < numAnimationFrames; f++) {
			AnimationFrame*frame = &anim->anim_frames[f];
			fread(&frame->mat,1,   sizeof(XMatrix4), file);
		}
	}
   
    if (anim) {
        anim->countUsed = 1;
        anim->isValid = true;
    }
    return anim;
}



void FileLoader::loadSceneAnimations(const char*path,std::vector<XAnimation*>*anims,std::vector<int>*indexs) {
    XAnimation*anim = NULL;
    
    FILE* file = fopen(path, "rb");
    if (!file) {
        return ;
    }
    
    char*format = (char*)malloc(33   * sizeof(char));
    char version   = 0;
    memset(format,    0, 33*sizeof(char));
    fread(&format[0], 1, 33*sizeof(char), file);
    
    if (std::strcmp(format, "XTECH ANIM**********************")==0)
    {
        int numMeshAnimations = 0;
        fread(&numMeshAnimations,    1,    sizeof(int), file);
        
        fread(&version,   1,            sizeof(char), file);//version
        std::vector<int> offsets;
        offsets.resize(numMeshAnimations);
        loadOffsets(file,numMeshAnimations,&offsets);
        
        for (int i = 0; i < indexs->size(); i++) {
            
            
            fseek(file, offsets[(*indexs)[i]], SEEK_SET);
            
            anim = loadAnimation(file);
            
            if (anim) {
                anim->isValid = true;
                anim->indexAnimationInFile = (*indexs)[i];
                anim->pathForFile = path;
            }
            anims->push_back(anim);
        }
    }
    free(format);
    fclose(file);
}

XAnimation * FileLoader::loadAnimationFile(const char* pathFile,int indexAnim) {
    XAnimation*anim = NULL;
    loadAnimationFile(pathFile, indexAnim, anim);
    return anim;
}


void FileLoader::loadAnimationFile(const char* pathFile,int indexAnim,XAnimation*anim) {
    
    FILE* file = fopen(pathFile, "rb");
	if (!file) {
		return ;
	}
    
    char*format = (char*)malloc(33   * sizeof(char));
    char version   = 0;
    memset(format,    0, 33*sizeof(char));
	fread(&format[0], 1, 33*sizeof(char), file);
    
    if (std::strcmp(format, "XTECH ANIM**********************")==0)
    {
        
        int numMeshAnimations = 0;
		fread(&numMeshAnimations,    1,    sizeof(int), file);

        fread(&version,   1,            sizeof(char), file);//version
		std::vector<int> offsets;
		offsets.resize(numMeshAnimations);
		loadOffsets(file,numMeshAnimations,&offsets);

		fseek(file, offsets[indexAnim], SEEK_SET);

		loadAnimation(file,anim);
        
        if (anim) {
            anim->isValid = true;
            anim->indexAnimationInFile = indexAnim;
            anim->pathForFile = pathFile;
        }
    }

    free(format);
    fclose(file);
}



int FileLoader::getTypeMesh(const char* path,int indexMesh) {
    
    FILE* file = fopen(path, "rb");
    if (!file) {
        return -1;
    }
    
    size_t offset = 33*sizeof(char);
    fseek(file, offset, SEEK_SET);
    
    int numMeshes = 0;
    fread(&numMeshes, 1,  sizeof(int),  file);//numMeshes
    
    
    
    offset+=sizeof(int)+sizeof(char)+ sizeof(float)*9 +sizeof(char) +sizeof(float)*3;
    
    
    for (int i = 0; i < numMeshes; i++) {
        
        fseek(file, offset, SEEK_SET);
        
        int lenghtName = 0;
        fread(&lenghtName,    1,    sizeof(int), file);// len name
        
        offset+=sizeof(int);
        
        char* nameMesh = (char*)malloc(sizeof(char)*lenghtName); // alloc mem
        // loading !
        memset(nameMesh,    0, lenghtName*sizeof(char));
        fread(&nameMesh[0],    1, sizeof(char)*lenghtName, file);// load name
        
        offset+=sizeof(char)*lenghtName;
        offset+=sizeof(char)*5;
        
        fseek(file, offset, SEEK_SET);
        
        bool skinned;
        fread(&skinned,   1,    sizeof(char), file);//c
        
        free(nameMesh);
        if (i == indexMesh) {
            if (skinned) {
                return SKINING_MESH;
            }else {
                return NORMAL_MESH;
            }
            break;
        }
    }
    
    
    return -1;
}


std::string FileLoader::loadStaticMesh(FILE*file,Mesh*model,bool reload) {
    int lenghtName = 0;
    fread(&lenghtName,    1,    sizeof(int), file);// len name
    
    char* nameMesh = (char*)malloc(sizeof(char)*lenghtName); // alloc mem
    // loading !
    memset(nameMesh,    0, lenghtName*sizeof(char));
    fread(&nameMesh[0],    1, sizeof(char)*lenghtName, file);// load name
    
    std::string nameMeshStd = nameMesh;
    
    free(nameMesh);
    nameMesh = NULL;
    
    bool haveTX,haveT,haveB,haveN,haveC,skinned;
    
    fread(&haveTX,    1,    sizeof(char), file);//tx
    fread(&haveT,     1,    sizeof(char), file);//t
    fread(&haveB,     1,    sizeof(char), file);//b
    fread(&haveN,     1,    sizeof(char), file);//n
    fread(&haveC,     1,    sizeof(char), file);//c
    fread(&skinned,   1,    sizeof(char), file);//c
    
    /*
     fread(&model->bboxCenter, 1,    sizeof(XVector3),  file);//numVertex
     fread(&model->bboxWidth,  1,    sizeof(XVector3),  file);//numVertex
     */

    fread(&model->numAllVertex, 1,    sizeof(int),  file);//numVertex
    fread(&model->numAllFaces,  1,    sizeof(int),  file);//numFaces
    
    uint maxVertexInChunk;
    fread(&maxVertexInChunk, 1,    sizeof(int),  file);//
    
    uint numChunks;
    fread(&numChunks, 1,    sizeof(int),  file);//
    
    model->numTextureCoordinats = haveTX;
    model->tangent  = haveT;
    model->binormal = haveB;
    model->normal   = haveN;
    model->color    = haveC;
    model->skinned  = skinned;
    
    uint sizeVertex = model->getSizeVertex();
    
    model->numChunks = numChunks;
    
    for (unsigned int i = 0; i < numChunks; i++) {
        
        uint chunkNumVertx,chunkNumFaces;
        fread(&chunkNumVertx, 1,    sizeof(int),  file);//
        fread(&chunkNumFaces, 1,    sizeof(int),  file);//
        
        model->numVertexC[i] = chunkNumVertx;
        model->numFacesC[i] = chunkNumFaces;
        
        uint sizeChunkVertex = chunkNumVertx*sizeVertex;
        uint sizeChunkFaces  = chunkNumFaces*(3*sizeof(facesType));
        
        model->vertex[i] = malloc(sizeChunkVertex);
        model->faces[i] = malloc(sizeChunkFaces);
        
        fread(model->vertex[i],1, sizeChunkVertex, file);
        fread(model->faces[i],           1, sizeChunkFaces,  file);
        
        
        //model->faces[i] = reorderForsyth(fases, chunkNumFaces, chunkNumVertx);
        //free(fases);
    }
    
    if (skinned) {
        unsigned int numBones = 0;
        fread(&numBones, 1,    sizeof(int),  file);//
        
        
        SkinnedMesh*skinnedMesh = (SkinnedMesh*)model;
        skinnedMesh->vertexDeclaration|=SKINING_MESH;
        skinnedMesh->numBones = numBones;
        if (skinnedMesh) {
            
            skinnedMesh->bindFrame->pos = (XVector3*)malloc(sizeof(XVector3)*numBones);
            skinnedMesh->bindFrame->rot = (XVector4*)malloc(sizeof(XVector4)*numBones);
            skinnedMesh->bindFrame->parentID = (int*)malloc(sizeof(int)*numBones);
            skinnedMesh->bindFrame->mat = (XMatrix4*)malloc(sizeof(XMatrix4)*numBones);
            
            
            skinnedMesh->boneIerarhy.resize(numBones);
            for (unsigned int i = 0; i < numBones;i++) {
                fread(&skinnedMesh->bindFrame->parentID[i],1, sizeof(int), file);
                fread(&skinnedMesh->bindFrame->pos[i],1, sizeof(XVector3), file);
                fread(&skinnedMesh->bindFrame->rot[i],1, sizeof(XVector4), file);
                skinnedMesh->boneIerarhy[i].boneID = i;
                skinnedMesh->boneIerarhy[i].parentID = skinnedMesh->bindFrame->parentID[i];
            }
            sortBones(&skinnedMesh->boneIerarhy);
            
            
            for (unsigned int bi = 0; bi < skinnedMesh->boneIerarhy.size(); bi++) {
                BoneInfo*boneInfo = &skinnedMesh->boneIerarhy[bi];
                XMatrix4MakeWithQuaternionAndTranslation2(&skinnedMesh->bindFrame->mat[boneInfo->boneID], &skinnedMesh->bindFrame->rot[boneInfo->boneID], &skinnedMesh->bindFrame->pos[boneInfo->boneID]);
            }
            
    
            
        }else {
            throw "not skinned mesh !";
        }
    }
    
    
    
    
    
    return nameMeshStd;
}

void FileLoader::writeEditorData(Mesh*model){
	FILE* file = fopen(model->pathForFile.c_str(), "r+b");
	if (!file) {
		return;
	}

	int sizeOfSeek = (33*sizeof(char)) + sizeof(int) + sizeof(char);

	fseek(file, sizeOfSeek, SEEK_SET);

    if(model->indexMeshInFile != 0) {
	    printf("not support more 1 mesh for editor !!! \n");
		return;
	}
	
	fwrite(&model->positionData[0],  1, sizeof(float), file); // C
	fwrite(&model->positionData[1],  1, sizeof(float), file); // C
	fwrite(&model->positionData[2],  1, sizeof(float), file); // C

	fwrite(&model->positionData[3],  1, sizeof(float), file); // C
	fwrite(&model->positionData[4],  1, sizeof(float), file); // C
	fwrite(&model->positionData[5],  1, sizeof(float), file); // C

	fwrite(&model->positionData[6],  1, sizeof(float), file); // C
	fwrite(&model->positionData[7],  1, sizeof(float), file); // C
	fwrite(&model->positionData[8],  1, sizeof(float), file); // C

	fwrite(&model->lightFollowToCamera,  1, sizeof(char), file); // C

	fwrite(&model->lightEyEVector[0],  1, sizeof(float), file); // C
	fwrite(&model->lightEyEVector[1],  1, sizeof(float), file); // C
	fwrite(&model->lightEyEVector[2],  1, sizeof(float), file); // C

    fclose(file);
}




void FileLoader::loadScene(const char*path,std::vector<Mesh*>*meshs,std::vector<int>*indexs) {

	FILE* file = fopen(path, "rb");
	if (!file) {
		return;
	}

	char*format = (char*)malloc(33   * sizeof(char));
    char version   = 0;
    memset(format,    0, 33*sizeof(char));
	
	fread(&format[0], 1, 33*sizeof(char), file);
    
    if (std::strcmp(format, "XTECH MESH**********************")==0)
    {
		float unusedData;
		char unusedChar;
        int numMeshes = 0;
        fread(&numMeshes,   1,          sizeof(int),  file);//numMeshes
		fread(&version,   1,            sizeof(char), file);//version

		fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C
        
        fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C
        
        fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C
        
        fread(&unusedChar,  1, sizeof(char), file); // C
        
        fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C
        fread(&unusedData,  1, sizeof(float), file); // C

		std::vector<int> offsets;
		offsets.resize(numMeshes);
		offsets[0] = ftell(file);

		if (numMeshes > 1) {
			// load offsets
			loadOffsets(file,numMeshes,&offsets);
			
		}


        
		for (int i = 0; i < indexs->size(); i++) {

			fseek(file, offsets[(*indexs)[i]], SEEK_SET);
		    int lastOffset = ftell(file);

		    int lenghtName = 0;
            fread(&lenghtName,    1,    sizeof(int), file);// len name
			int sizeOfSeek = lastOffset+(sizeof(char)*lenghtName)+sizeof(char)*5+sizeof(int);
    
            bool skinned;
		    fseek(file, sizeOfSeek, SEEK_SET);
            fread(&skinned,   1,    sizeof(char), file);//c

		    fseek(file, lastOffset, SEEK_SET); // restore 

			Mesh*newMesh;
			if (skinned) {
				newMesh = new SkinnedMesh();
			}else {
				newMesh = new Mesh();
			}

			newMesh->pathForFile = path;
			newMesh->indexMeshInFile = (*indexs)[i];
			newMesh->offsetInFile = ftell(file);
			loadStaticMesh(file, newMesh,true);
			fillGPU(newMesh);

			meshs->push_back(newMesh);
		}
	}
    free(format);
    fclose(file);
}

void FileLoader::loadOffsets(FILE*file,int numMeshes,std::vector<int>*offsets) {
	int lastOffset = ftell(file);
	fseek ( file, 0, SEEK_END ); // go to end
	int offsetEnd = ftell ( file );
	offsetEnd-=sizeof(int)*numMeshes;
	fseek(file, offsetEnd, SEEK_SET); // offsets 

	for (int i = 0;i < numMeshes;i++) {
		int offset;
	    fread(&offset,  1, sizeof(int), file); // C
		(*offsets)[i] = offset;
	}
	fseek(file, lastOffset, SEEK_SET);
}

void FileLoader::fillGPU(Mesh*model) {
	for (unsigned int j = 0; j < model->numChunks; j++) {
         if (model->indexChunksVBODamaged[j]) {
             _meshCache->loadVChunk(model, j);
             model->indexChunksVBODamaged[j] = false;
         }else {
             free(model->vertex[j]);
             model->vertex[j] = NULL;
         }
                    
         if (model->indexChunksIBODamaged[j]) {
             _meshCache->loadIChunk(model, j);
             model->indexChunksIBODamaged[j] = false;
         }else {
             free(model->faces[j]);
             model->faces[j] = NULL;
         }
    }
    model->isDamaged = false;
}


void FileLoader::reloadChunkInMesh(Mesh*model) {
    
    FILE* file = fopen(model->pathForFile.c_str(), "rb");
	if (!file) {
		return;
	}
    
    model->typeMesh = FILE_LOADED_LOCAL;
    
    char*format = (char*)malloc(33   * sizeof(char));
    char version   = 0;
    memset(format,    0, 33*sizeof(char));
	
	fread(&format[0], 1, 33*sizeof(char), file);
    
    if (std::strcmp(format, "XTECH MESH**********************")==0)
    {
        int numMeshes = 0;
        fread(&numMeshes,   1,          sizeof(int),  file);//numMeshes
        fread(&version,   1,            sizeof(char), file);//version
        
        // scene param
        
        fread(&model->positionData[0],  1, sizeof(float), file); // C
        fread(&model->positionData[1],  1, sizeof(float), file); // C
        fread(&model->positionData[2],  1, sizeof(float), file); // C
        
        fread(&model->positionData[3],  1, sizeof(float), file); // C
        fread(&model->positionData[4],  1, sizeof(float), file); // C
        fread(&model->positionData[5],  1, sizeof(float), file); // C
        
        fread(&model->positionData[6],  1, sizeof(float), file); // C
        fread(&model->positionData[7],  1, sizeof(float), file); // C
        fread(&model->positionData[8],  1, sizeof(float), file); // C
        
        fread(&model->lightFollowToCamera,  1, sizeof(char), file); // C
        
        fread(&model->lightEyEVector[0],  1, sizeof(float), file); // C
        fread(&model->lightEyEVector[1],  1, sizeof(float), file); // C
        fread(&model->lightEyEVector[2],  1, sizeof(float), file); // C
        

		if (model->offsetInFile == 0 && model->indexMeshInFile > 0) {
			std::vector<int> offsets;
			offsets.resize(numMeshes);
			offsets[0] = ftell(file);

			if (numMeshes > 1) {
				loadOffsets(file,numMeshes,&offsets);
				model->offsetInFile = offsets[model->indexMeshInFile];
			}
		}
        
        if (model->offsetInFile != 0)
		fseek(file, model->offsetInFile, SEEK_SET);

        loadStaticMesh(file, model,true);
	    fillGPU(model);
        
    }
    
    free(format);
    format = NULL;
    
    fclose(file);
}






/*
void FileLoader::reloadChunkInMesh(Mesh*model) {
    
    FILE* file = fopen(model->pathForFile.c_str(), "rb");
	if (!file) {
		return;
	}
    
    
  
    
    model->numTextureCoordinats = 1;
    model->normal   = true;
    model->skinned  = true;
    
    uint sizeVertex = 0;
    model->calculateSizeVertex(0,0);
    sizeVertex = model->sizeVertex;
    
    model->numChunks = 1;
    
    int i = 0;
        
        uint chunkNumVertx,chunkNumFaces;
        fread(&chunkNumVertx, 1,    sizeof(int),  file);//
        fread(&chunkNumFaces, 1,    sizeof(int),  file);//
    
    chunkNumFaces/=3;
    
        model->numVertexC[i] = chunkNumVertx;
        model->numFacesC[i] = chunkNumFaces;
    
    
    model->numAllFaces = chunkNumFaces;
    model->numAllVertex = chunkNumVertx;
    
        
        uint sizeChunkVertex = chunkNumVertx*sizeVertex;
        uint sizeChunkFaces  = chunkNumFaces*(3*sizeof(facesType));
        
        model->vertex[i] = malloc(sizeChunkVertex);
        model->faces[i] = malloc(sizeChunkFaces);
    
    VertexIndexType* fases = (VertexIndexType*)malloc(sizeChunkFaces);
    
    fread(model->vertex[i],1, sizeChunkVertex, file);
    fread(fases,           1, sizeChunkFaces,  file);
    
    
    model->faces[i] = reorderForsyth(fases, chunkNumFaces, chunkNumVertx);
    free(fases);
    
    
    uint magicNumber = 0;
    fread(&magicNumber, 1,    sizeof(int),  file);//
    
    
    _meshCache->loadVChunk(model, 0);
    _meshCache->loadIChunk(model, 0);
    
    
    fclose(file);
}



*/














