//
//  ShaderLib.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 14.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "ShaderLib.h"
#include "Scene.h"
ShaderLib::ShaderLib(){
    
 
}
void ShaderLib::get(Material*mat ,Mesh*model, uint pass,vector<string> *outList){
    string shaderName = "baseShading.xml";
    
    uint flagsMaterial = mat->flags;
    uint vertexFlags   = model->vertexDeclaration;
    
    
    switch (pass) {
        case SHADOW_DEPTH_TEHNICS:
            // XTODO : mb use array ?
            if ((vertexFlags & NORMAL_MESH) == NORMAL_MESH)   outList->push_back("shadowMaps.xml");
            if ((vertexFlags & SKINING_MESH) == SKINING_MESH) outList->push_back("skining.xml");
            break;
        case BACK_BUFFER_TEHNICS:
            if ((flagsMaterial & NORMAL_MATERIAL)      == NORMAL_MATERIAL)                      outList->push_back("normalMaterial.xml");
            if ((flagsMaterial & COLOR_MATERIAL)       == COLOR_MATERIAL)                       outList->push_back("colorMaterial.xml");
            if ((flagsMaterial & NORMAL_MAP_MATERIAL)  == NORMAL_MAP_MATERIAL)                  outList->push_back("normalMapMaterial.xml");
            
            
            
            if ((flagsMaterial & DYNAMIC_PER_VERTEX_BASE_LIGHT) == DYNAMIC_PER_VERTEX_BASE_LIGHT) outList->push_back("baseDynamicPerVertexLight.xml");
            if ((flagsMaterial & DYNAMIC_PER_PIXEL_BASE_LIGHT) == DYNAMIC_PER_PIXEL_BASE_LIGHT) outList->push_back("baseDynamicPerPixelLight.xml");
            if ((flagsMaterial & RESAVE_SHADOW_SM)             == RESAVE_SHADOW_SM)             outList->push_back("ShadowMapsBackBuffer.xml");
            
            if ((vertexFlags & SKINING_MESH) == SKINING_MESH) outList->push_back("skining.xml");
            break;
        default:
            break;
    }
    
    
    
   
}
