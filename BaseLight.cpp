//
//  BaseLight.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 26.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "BaseLight.h"
#include "Camera.h"

void BaseLight::lookAt(const vec3& pos, const vec3& point, const vec3& up)
{
    vec3 d = (point - pos).normalize();
    vec3 s = d.cross(up).normalize();
    vec3 u = s.cross(d).normalize();
    vec3 e(-s.dot(pos), -u.dot(pos), d.dot(pos));
    
    modelViewMatrix.m[0]  = s.x;modelViewMatrix.m[1]  = u.x;modelViewMatrix.m[2]  = -d.x;modelViewMatrix.m[3]  = 0.0;
    modelViewMatrix.m[4]  = s.y;modelViewMatrix.m[5]  = u.y;modelViewMatrix.m[6]  = -d.y;modelViewMatrix.m[7]  = 0.0;
    modelViewMatrix.m[8]  = s.z;modelViewMatrix.m[9]  = u.z;modelViewMatrix.m[10] = -d.z;modelViewMatrix.m[11] = 0.0;
    modelViewMatrix.m[12] = e.x;modelViewMatrix.m[13] = e.y;modelViewMatrix.m[14] =  e.z;modelViewMatrix.m[15] = 1.0;
    
    position.x   = pos.x;
    
    
    position.y   = pos.y;
    position.z   = pos.z;
    isProjModelViewMatrixDerty = true;
    isProjModelViewMatrixSTDerty = true;
}


void BaseLight::setOrthoMatrix(float left, float right,
                                float bottom, float top,
                                float nearZ, float farZ) {


    XMatrix4MakeOrtho(&perspectiveMatrix,left, right, bottom, top, nearZ, farZ);
    
    XMatrix4 bias = {0.5f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.5f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.5f, 0.0f,
                     0.5f, 0.5f, 0.5f, 1.0f};
    
    XMatrix4Mult(&scaledTransletedProjMatrix,&bias, &perspectiveMatrix);

}


void BaseLight::init(){
    //XMatrix4Perspective(&perspectiveMatrix,60.0, 1.0, 0.01, 300.0);
    XMatrix4MakeOrtho(&perspectiveMatrix,-50.0f, 50.0f, -50.0f, 50.0f, 0.01f, 100.0f);
    
    XMatrix4 bias = {0.5f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.5f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.5f, 0.0f,
                     0.5f, 0.5f, 0.5f, 1.0f};
    
    XMatrix4Mult(&scaledTransletedProjMatrix,&bias, &perspectiveMatrix);
}




XMatrix4* BaseLight::getPerspectiveMatrix(){
    return &perspectiveMatrix;
}

XMatrix4* BaseLight::getModelViewMatrix(){
    return &modelViewMatrix;
}

XMatrix4* BaseLight::getProjModelViewMatrix() {
    if (isProjModelViewMatrixDerty) {
        isProjModelViewMatrixDerty = false;
        XMatrix4Mult(&projModelViewMatrix,&perspectiveMatrix, &modelViewMatrix);
        isProjModelViewMatrixSTDerty = true;
    }
    return &projModelViewMatrix;
}

XMatrix4* BaseLight::getProjModelViewMatrixST() {
    if (isProjModelViewMatrixDerty) {
        isProjModelViewMatrixDerty = false;
        XMatrix4Mult(&projModelViewMatrix,&perspectiveMatrix, &modelViewMatrix);
    }
    
    if (isProjModelViewMatrixSTDerty) {
        isProjModelViewMatrixSTDerty = false;
        XMatrix4Mult(&projModelViewMatrixST,&scaledTransletedProjMatrix, &modelViewMatrix);
    }
    
    return &projModelViewMatrixST;
}
