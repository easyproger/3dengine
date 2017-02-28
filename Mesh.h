//
//  Mesh.h
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef MESH_H__
#define MESH_H__
#define MAX_ATTRIBUTES 40

#define FILE_LOADED_LOCAL 1
#define FILE_GENERATED    2

#include "stdio.h"
#include "stdlib.h"
#include "Types.h"
#include "mathLib.h"
#include "XMathTypes.h"
#include "SkinningMath.h"

enum VERTEX_DECLARATION {
    VERTEX_DECLARATION_SCINNED_MESH,
    VERTEX_DECLARATION_NORMAL,
    VERTEX_DECLARATION_TANGENTS,
    VERTEX_DECLARATION_BINORMAL,
    VERTEX_DECLARATION_TEXTURE_COORDINATS_1,
    VERTEX_DECLARATION_COLOR,
    VERTEX_DECLARATION_TEXTURE_COORDINATS_3,
    VERTEX_DECLARATION_TEXTURE_COORDINATS_4
};
enum ATTRIBUTES {
    ATTRIBUTE__OBJECT_POSITION     = 1,
    ATTRIBUTE_NORMAL               = 2,
    ATTRIBUTE_BINORMAL             = 3,
    ATTRIBUTE_TANGENT              = 4,
    ATTRIBUTE_TEXTURE_COORDINATS_1 = 5,
    ATTRIBUTE_COLOR                = 6,
    ATTRIBUTE_TEXTURE_COORDINATS_3 = 7,
    ATTRIBUTE_TEXTURE_COORDINATS_4 = 8,
    ATTRIBUTE_FAR_CORNERS          = 9,
    ATTRIBUTE_BONES_WEIGHT         = 10,
    ATTRIBUTE_BONES_IDS            = 11
};

#include "XAnimTypes.h"


class Mesh {
    
public:
	int offsetInFile;
    SkinningFrame*bindFrame;
    std::vector<BoneInfo> boneIerarhy;
    int numBones;
	float positionData[9];
   
    uint typeMesh;
    
    uint indxInCache;
    
    //XTODO: .... 
    std::string urlForFile;
    bool loadingViaHttp;
    bool asyncLoaded;
    char lightFollowToCamera;
	float lightEyEVector[3];

    
    std::string pathForFile;
    
    uint indexMeshInFile;
    
    XVector3 boundingBoxMinPT;
    XVector3 boundingBoxMaxPT;
    
    XVector3 bboxWidth;
    XVector3 bboxCenter;
    
    XVector3 bboxSize;
    
    Mesh();
    virtual ~Mesh(){};
    virtual void calculateOffsets(uint offset,uint index);
 
    virtual XVector3* getBindTranslate(){return NULL;};
    virtual XVector4* getBindPoseRotation(){return NULL;};
    
    
    uint vertexDeclaration;
    
    
    bool color;
    bool skinned;
    bool normal;
    bool tangent;
    bool binormal;
    uint numTextureCoordinats;
    
    
    
    
    
    void *vertex[MAX_CHUNKS];
    void *faces[MAX_CHUNKS];
    
    
    
    uint sizeVertex;
    
    uint numAllVertex;
    uint numAllFaces;
    
    
    
    
    // new data
    
    //XTODO: delete chunks !
    uint numVertexC[MAX_CHUNKS];
    uint numFacesC[MAX_CHUNKS];
    
    uint numChunks;
    
    uint vertexBufferID[MAX_CHUNKS];
    uint indexBufferID[MAX_CHUNKS];
    
    uint getSizeVertex();
    void setAsDamagedVBOChunk(uint chunk);
    void setAsDamagedIBOChunk(uint chunk);
    void setAsDamaged();
    
    
    GLvoid * indexOffset[MAX_CHUNKS];
    
    GLvoid *offsets[MAX_CHUNKS][MAX_ATTRIBUTES];
    
    uint sizeSeparate;
    
    
    
    bool isDamaged;

    
    uint idModel;
    bool indexChunksVBODamaged[MAX_CHUNKS];
    bool indexChunksIBODamaged[MAX_CHUNKS];
private:
    
    
    
    int numVBOChunksDamaged;
};

#endif