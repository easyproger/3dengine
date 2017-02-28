//
//  Mesh.cpp
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#include "Mesh.h"
#include "FlagsForShaderCompile.h"

Mesh::Mesh()
{
	offsetInFile = 0;
    bindFrame = NULL;
    numBones = 0;
    asyncLoaded = false;
    loadingViaHttp = false;
    idModel = 0;
    vertexDeclaration = NORMAL_MESH;
    normal = false;
    binormal = false;
    tangent = false;
    skinned = false;
    color = false;
    numTextureCoordinats = 0;
    indexMeshInFile = 0;
    isDamaged = true;
    for (int i = 0; i < MAX_CHUNKS; i++) {
        indexChunksVBODamaged[i] = true;
        indexChunksIBODamaged[i] = true;
    }
    
    
}

void Mesh::setAsDamaged() {
	isDamaged = true;
    for (int i = 0; i < MAX_CHUNKS; i++) {
        indexChunksVBODamaged[i] = true;
        indexChunksIBODamaged[i] = true;
    }
}

void Mesh::setAsDamagedVBOChunk(uint chunk){
    indexChunksVBODamaged[chunk] = true;
    isDamaged = true;
}
void Mesh::setAsDamagedIBOChunk(uint chunk){
    indexChunksIBODamaged[chunk] = true;
    isDamaged = true;
}



uint Mesh::getSizeVertex() {
    sizeVertex      = 3*sizeof(float);
    
    if (numTextureCoordinats == 1) {
        sizeVertex += 2*sizeof(float);
    }
    if (tangent) {
        sizeVertex += 3*sizeof(float);
    }
    if (binormal) {
        sizeVertex += 3*sizeof(float);
    }
    if (normal) {
        sizeVertex += 3*sizeof(float);
    }
    if (color) {
        sizeVertex += 3*sizeof(float);
    }
    if (skinned) {
        sizeVertex += 4*sizeof(float);
        sizeVertex += 4*sizeof(float);
    }
    return sizeVertex;
}

void Mesh::calculateOffsets(uint offset,uint index)
{
    sizeVertex      = 3*sizeof(float);
    offsets[index][ATTRIBUTE__OBJECT_POSITION] = (GLvoid*)(0+offset);
    
    if (numTextureCoordinats == 1) {
        offsets[index][ATTRIBUTE_TEXTURE_COORDINATS_1] = (GLvoid*)(sizeVertex+offset);
        sizeVertex += 2*sizeof(float);
    }
    if (tangent) {
        offsets[index][ATTRIBUTE_TANGENT] = (GLvoid*)(sizeVertex+offset);
        sizeVertex += 3*sizeof(float);
    }
    if (binormal) {
        offsets[index][ATTRIBUTE_BINORMAL] = (GLvoid*)(sizeVertex+offset);
        sizeVertex += 3*sizeof(float);
    }
    if (normal) {
        offsets[index][ATTRIBUTE_NORMAL] = (GLvoid*)(sizeVertex+offset);
        sizeVertex += 3*sizeof(float);
    }
    if (color) {
        offsets[index][ATTRIBUTE_COLOR] = (GLvoid*)(sizeVertex+offset);
        sizeVertex += 3*sizeof(float);
    }
    if (skinned) {
        offsets[index][ATTRIBUTE_BONES_WEIGHT] = (GLvoid*)(sizeVertex+offset);
        sizeVertex += 4*sizeof(float);
        
        offsets[index][ATTRIBUTE_BONES_IDS] = (GLvoid*)(sizeVertex+offset);
        sizeVertex += 4*sizeof(float);
    }
    
};
