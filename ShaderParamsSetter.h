//
//  ShaderParamsSetter.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 26.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//


#ifndef SHADER_PARAMS_SETTER_H__
#define SHADER_PARAMS_SETTER_H__

#include "Camera.h"
#include "BaseRenderObject.h"
#include "BaseLight.h"

#include "stdio.h"
#include "Types.h"
#include "FrameBuffer.h"

class ShaderParamsSetter {
    
    BaseLight*light;
    BaseRenderObject*baseRenderObject;
    Camera*camera;
    int indexTexture;
    int texIDS[10];
    uint depthBuffer;
    uint normalAndMaterialBuffer;
    uint albedoBuffer;
    uint lightBuffer;
public:
    
    void resetTextureIndex();
    
    Camera*getCamera();
    
    
    
    ShaderParamsSetter(Camera*camera,uint depthBuffer,uint normalAndMaterialBuffer,uint albedoBuffer,uint lightBuffer);
    ~ShaderParamsSetter(){};
    
    void setDepthBuffer(uint texID);
    void setLight(BaseLight*light);
    void setRenderObject(BaseRenderObject*renderObject);
    void setLightBuffer(FrameBuffer*frameBuffer);
    
    
    
    //
    
    void setLightProjViewMatrixUniform(uint idUniform);
    void setLightViewMatrixUniform(uint idUniform);
    void setPerspectiveLightMatrixUniform(uint idUniform);
    void setLightProjViewMatrixSTUniform(uint idUniform);
    void setProjCameraModelViewUniform(uint idUniform);
    
    void setAlbedoBufferUniform(uint idUniform);
    void setNormalAndMaterialBufferUniform(uint idUniform);
    void setDepthBufferUniform(uint idUniform);
    void setPerspectiveViewInverseUniform(uint idUniform);
    void setObjectSpecularMapTextureUniform(uint idUniform);
    void setObjectDiffuseTextureUniform(uint idUniform);
    void setObjectNormalMapTextureUniform(uint idUniform);
    void setCameraPositionUniform(uint idUniform);
    void setCameraViewInverse3x3Uniform(uint idUniform);
    void setGeometryBufferUniform(uint idUniform);
    void setLightBufferUniform(uint idUniform);
    void setLightPositionUniform(uint idUniform);
    void setModelNormalMatrixUniform(uint idUniform);
    void setFarPlaneUniform(uint idUniform);
    void setWorldObjectMatrixUniform(uint idUniform);
    void setPerspectiveMatrixUniform(uint idUniform);
    void setCameraViewMatrixUniform(uint idUniform);
    void setBonesTranslations(uint idUniform);
    void setBonesRotations(uint idUniform);
};

#endif

