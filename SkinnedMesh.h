//
//  SkinnedMesh.h
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#ifndef SKINNEDMESH_H__
#define SKINNEDMESH_H__

#include "mathLib.h"
#include "Mesh.h"
#include "XAnimTypes.h"




class SkinnedMesh:public Mesh {
public:
    SkinnedMesh(){
        bindFrame = (SkinningFrame*)malloc(sizeof(SkinningFrame));
    };
    ~SkinnedMesh(){
        free(bindFrame);
    };
    
    
    virtual XVector3* getBindTranslate();
    virtual XVector4* getBindPoseRotation();
    
    //collect state ! ))
    
    
        
    
    
};

#endif