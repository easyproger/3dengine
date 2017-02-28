//
//  BaseLight.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 26.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#ifndef BASE_LIGHT_H__
#define BASE_LIGHT_H__
#include <iostream>

#include "XTypes.h"
#include "XMatrix4Math.h"
#include "XMathTypes.h"
#include "Vectors.h"
#include "Types.h"
#include "Texture.h"



class BaseLight {
protected:
    bool isTransformDerty;
    
public:
    
    void init();
   
    void lookAt(const vec3& pos, const vec3& point, const vec3& up);
    void setOrthoMatrix(float left, float right,
                                float bottom, float top,
                                float nearZ, float farZ);

    
    XMatrix4 * getPerspectiveMatrix();
    XMatrix4 * getModelViewMatrix();
    XMatrix4 * getProjModelViewMatrix();
    XMatrix4 * getProjModelViewMatrixST();
    
    XVector3 position;
private:
    XMatrix4 modelViewMatrix;
    XMatrix4 perspectiveMatrix;
    XMatrix4 projModelViewMatrix;
    XMatrix4 projModelViewMatrixST;
    
    XMatrix4 scaledTransletedProjMatrix;
    
    bool isProjModelViewMatrixSTDerty;
    bool isProjModelViewMatrixDerty;
    
    
};

#endif