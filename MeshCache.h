//
//  MeshCache.h
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef MESHCACHE_H__
#define MESHCACHE_H__

#include "XSingleton.h"

#include "Mesh.h"
#include "Types.h"
#include "stdlib.h"
#include <map>
#include <string>


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <GL/glew.h>
#else
#include <OpenGLES/ES2/gl.h>
#endif

#include <vector>


namespace Xengine
{

    typedef struct{
        uint startOffset;
        uint size;
        
        uint indexChunk;
        Mesh * mesh;
    }StoredData;
    
    class MeshCache;
    
    class  MeshCache 
    {
    public:
         
        MeshCache();
        ~MeshCache();
        
        uint addNotLoaded(Mesh*model);
        void addMesh(Mesh*model);
        uint getIDByName(char* nameChar);
        Mesh* get(uint idmesh);
        void initialize();
        uint indexModels;
        uint allocedMeshs;
        
        
        std::vector<Mesh*> meshs;
        
        void createVBOIndex();
        void createVBOVertex();
        
        void loadIChunk(Mesh*model,uint chunkI);
        void loadVChunk(Mesh*model,uint chunkI);
        void sendToGPU(Mesh*model);
    private:
        uint currentIDVBOV;
        uint currentIDVBOI;
        
        uint createdNumVBO;
        uint createdNumIBO;
        
        
        
        std::vector<StoredData*> storedDatasV[MAX_VBOS];
        std::vector<StoredData*> storedDatasI[MAX_VBOS];
        
        GLuint modelVertexBuffers[MAX_VBOS];
        GLuint modelIndexBuffers[MAX_VBOS];
        uint offsetModelVertexBuffer[MAX_VBOS];
        uint offsetModelIndexBuffer[MAX_VBOS];
        
    };
}

#endif