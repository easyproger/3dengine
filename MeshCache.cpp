//
//  MeshCache.cpp
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#include "MeshCache.h"


using namespace std;

namespace Xengine
{
    
    MeshCache::MeshCache()
    {
        currentIDVBOV = -1;
        currentIDVBOI = -1;
        createdNumVBO = -1;
        createdNumIBO = -1;
        
        
        initialize();
    }
    MeshCache::~MeshCache()
    {
        
    }
    
    
    void MeshCache::createVBOVertex(){
        currentIDVBOV++;
        glGenBuffers(1, &modelVertexBuffers[currentIDVBOV]);
        glBindBuffer(GL_ARRAY_BUFFER, modelVertexBuffers[currentIDVBOV]);
        glBufferData(GL_ARRAY_BUFFER, maxSizeVBO, 0, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        offsetModelVertexBuffer[currentIDVBOV] = 0;
        createdNumVBO++;
    }
    void MeshCache::createVBOIndex(){
        currentIDVBOI++;
        glGenBuffers(1, &modelIndexBuffers[currentIDVBOI]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIndexBuffers[currentIDVBOI]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxSizeVBO, 0, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        offsetModelIndexBuffer[currentIDVBOI]  = 0;
        createdNumIBO++;
    }
    
    
    void MeshCache::initialize()
    {
        createVBOVertex();
        createVBOIndex();
    }
    
  
    void MeshCache::loadVChunk(Mesh*model,uint chunkI) {
        uint sizeVertexData = model->numVertexC[chunkI] * model->sizeVertex;
        
        
        
        uint currentSizeVertexVBO = maxSizeVBO - offsetModelVertexBuffer[currentIDVBOV];
        
        
        if (sizeVertexData > currentSizeVertexVBO)  {
            
            if (currentIDVBOV>=createdNumVBO) {
                if (createdNumVBO < MAX_VBOS-1 ) {
                    printf("%d \n",createdNumVBO);
                    createVBOVertex();
                }else {
                    printf("wtf");
                    currentIDVBOV = 0; // max VBO created
                }
            }else {
                currentIDVBOV++;
            }
            offsetModelVertexBuffer[currentIDVBOV] = 0;
            
            if (maxSizeVBO < sizeVertexData) {
                printf("EROR vertex vbo small \n");
                throw "EROR vertex vbo small";
            }
        }
        
        
        glBindBuffer(GL_ARRAY_BUFFER, modelVertexBuffers[currentIDVBOV]);
        glBufferSubData(GL_ARRAY_BUFFER, offsetModelVertexBuffer[currentIDVBOV],  sizeVertexData, model->vertex[chunkI]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        
        std::vector<StoredData*>::iterator it = storedDatasV[currentIDVBOV].begin();
        while ( it != storedDatasV[currentIDVBOV].end() )
        {
            StoredData *data = *it;
            
            
            uint blockstart = data->startOffset;
            uint blockEnd   = data->startOffset+data->size;
            
            uint writedBlockStart = offsetModelVertexBuffer[currentIDVBOV];
            uint writedBlockEnded = offsetModelVertexBuffer[currentIDVBOV]+sizeVertexData;
            
          
            bool sss = false;
                
            
            if (blockstart <= writedBlockStart){
                sss = blockEnd >= writedBlockStart;
            }
            else {
                sss = blockstart <= writedBlockEnded;
            };
            
            
            if (sss) {
                Mesh*damagedMesh = data->mesh;
                damagedMesh->setAsDamagedVBOChunk(data->indexChunk);
                it = storedDatasV[currentIDVBOV].erase(it);
                free(data);
            }else {
                ++it;
            }
        }
        
        StoredData *datatostore = (StoredData *)malloc(sizeof(StoredData));
        datatostore->size = sizeVertexData;
        datatostore->startOffset = offsetModelVertexBuffer[currentIDVBOV];
        datatostore->mesh = model;
        datatostore->indexChunk = chunkI;
        storedDatasV[currentIDVBOV].push_back(datatostore);
        
        model->vertexBufferID[chunkI] = modelVertexBuffers[currentIDVBOV];
        model->calculateOffsets(offsetModelVertexBuffer[currentIDVBOV],chunkI);
        offsetModelVertexBuffer[currentIDVBOV]+=sizeVertexData+32;
        
        
        
        
        free(model->vertex[chunkI]);
        model->vertex[chunkI] = NULL;
        

    }
    
    void MeshCache::loadIChunk(Mesh*model,uint chunkI){
        
        uint sizeIndexData = model->numFacesC[chunkI]  *(3*sizeof(facesType));
        
        
        uint currentSizeFacesVBO = maxSizeVBOI - offsetModelIndexBuffer[currentIDVBOI];
        if (sizeIndexData > currentSizeFacesVBO)  {
            
            if (currentIDVBOI >= createdNumIBO) {
                if (createdNumIBO < MAX_VBOS-1 ) {
                    createVBOIndex();
                }else {
                    currentIDVBOI = 0;
                }
            }else {
                currentIDVBOI++;
            }
            offsetModelIndexBuffer[currentIDVBOI] = 0;
            
            
            if (maxSizeVBOI < sizeIndexData) {
                printf("EROR index vbo small ");
                throw "EROR index vbo small";
            }
            
        }
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelIndexBuffers[currentIDVBOI]);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetModelIndexBuffer[currentIDVBOI], sizeIndexData, model->faces[chunkI]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        
        
        
        
        
        std::vector<StoredData*>::iterator itI = storedDatasI[currentIDVBOI].begin();
        while ( itI != storedDatasI[currentIDVBOI].end() )
        {
            StoredData *data = *itI;
            
            
            
            uint blockstart = data->startOffset;
            uint blockEnd   = data->startOffset+data->size;
            
            uint writedBlockStart = offsetModelIndexBuffer[currentIDVBOI];
            uint writedBlockEnded = offsetModelIndexBuffer[currentIDVBOI]+sizeIndexData;
            
            
            bool sss = false;
            
            
            if (blockstart <= writedBlockStart){
                sss = blockEnd >= writedBlockStart;
            }
            else {
                sss = blockstart <= writedBlockEnded;
            };
            
            
            if (sss) {
                Mesh * damagedMesh = data->mesh;
                damagedMesh->setAsDamagedIBOChunk(data->indexChunk);
                itI = storedDatasI[currentIDVBOI].erase(itI);
                free(data);
            }else {
                ++itI;
            }
        }
        
        StoredData* datatostoreI  = (StoredData *)malloc(sizeof(StoredData));
        datatostoreI->size = sizeIndexData;
        datatostoreI->startOffset = offsetModelIndexBuffer[currentIDVBOI];
        datatostoreI->mesh = model;
        datatostoreI->indexChunk = chunkI;
        storedDatasI[currentIDVBOI].push_back(datatostoreI);
        
        
        
        model->indexOffset[chunkI] = (GLvoid*)offsetModelIndexBuffer[currentIDVBOI];
        offsetModelIndexBuffer[currentIDVBOI]+=sizeIndexData+32;
        model->indexBufferID[chunkI] = modelIndexBuffers[currentIDVBOI];
        
        
        
        free(model->faces[chunkI]);
        model->faces[chunkI] = NULL;
    }
    
    void MeshCache::sendToGPU(Mesh*model)
    {
        
        for (unsigned int chunkI = 0; chunkI < MAX_CHUNKS; chunkI++) {
            model->indexChunksIBODamaged[chunkI] = false;
            model->indexChunksVBODamaged[chunkI] = false;
        }
        model->isDamaged = false;
        
        for (unsigned int chunkI = 0; chunkI < model->numChunks; chunkI++) {
            loadVChunk(model, chunkI);
            loadIChunk(model, chunkI);
        }
        
        
    }
    Mesh* MeshCache::get(uint idmesh){ return meshs[idmesh];}
    
    uint MeshCache::addNotLoaded(Mesh*model)
    {
        meshs.push_back(model);
        return meshs.size()-1;
    }
    
    void MeshCache::addMesh(Mesh*model)
    {
        meshs.push_back(model);
        sendToGPU(model);
    }
}
