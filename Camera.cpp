//
//  Camera.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 08.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "Camera.h"

Camera::Camera(){

    isFarCornersDerty = false;
    isProjModelViewDerty = true;
};




void Camera::setPerspective(float angle, float width, float height, float nearZ,  float farPlane) {
    mFarPlane = farPlane;
    mAspectRatio = (float) width / (float) height;
    mAngle = angle;
    
    
    XMatrix4Perspective(&perspectiveMatrix,angle, mAspectRatio, nearZ, farPlane);
    
    isFarCornersDerty = false;
    isProjModelViewDerty = true;
}


void Camera::setPerspectivematrix(float* data) {
    XMatrix4MakeWithArray(&perspectiveMatrix, data);
    isFarCornersDerty = false;
    isProjModelViewDerty = true;
}

void Camera::lookAt(const vec3& pos, const vec3& point, const vec3& up)
{
    vec3 d = (point - pos).normalize();
    vec3 s = d.cross(up).normalize();
    vec3 u = s.cross(d).normalize();
    vec3 e(-s.dot(pos), -u.dot(pos), d.dot(pos));
    
    modelViewMatrix.m[0]  = s.x;modelViewMatrix.m[1]  = u.x;modelViewMatrix.m[2]  = -d.x;modelViewMatrix.m[3]  = 0.0;
    modelViewMatrix.m[4]  = s.y;modelViewMatrix.m[5]  = u.y;modelViewMatrix.m[6]  = -d.y;modelViewMatrix.m[7]  = 0.0;
    modelViewMatrix.m[8]  = s.z;modelViewMatrix.m[9]  = u.z;modelViewMatrix.m[10] = -d.z;modelViewMatrix.m[11] = 0.0;
    modelViewMatrix.m[12] = e.x;modelViewMatrix.m[13] = e.y;modelViewMatrix.m[14] =  e.z;modelViewMatrix.m[15] = 1.0;
    
    
    /*
     viewMatrix.m[0][0] = s.x; viewMatrix.m[0][1] = u.x; viewMatrix.m[0][2] = -d.x; viewMatrix.m[0][3] = 0.0;
     viewMatrix.m[1][0] = s.y; viewMatrix.m[1][1] = u.y; viewMatrix.m[1][2] = -d.y; viewMatrix.m[1][3] = 0.0;
     viewMatrix.m[2][0] = s.z; viewMatrix.m[2][1] = u.z; viewMatrix.m[2][2] = -d.z; viewMatrix.m[2][3] = 0.0;
     viewMatrix.m[3][0] = e.x; viewMatrix.m[3][1] = e.y; viewMatrix.m[3][2] =  e.z; viewMatrix.m[3][3] = 1.0;
     */
    
    isProjModelViewDerty = true;
    
    cameraPosition.x = pos.x;
    cameraPosition.y = pos.y;
    cameraPosition.z = pos.z;
}

void Camera::resetModelViewMatrix() {
    modelViewMatrix.m[0]  = 1.0;modelViewMatrix.m[1]  = 0.0;modelViewMatrix.m[2]  = 0.0;modelViewMatrix.m[3]  = 0.0;
    modelViewMatrix.m[4]  = 0.0;modelViewMatrix.m[5]  = 1.0;modelViewMatrix.m[6]  = 0.0;modelViewMatrix.m[7]  = 0.0;
    modelViewMatrix.m[8]  = 0.0;modelViewMatrix.m[9]  = 0.0;modelViewMatrix.m[10] = 1.0;modelViewMatrix.m[11] = 0.0;
    modelViewMatrix.m[12] = 0.0;modelViewMatrix.m[13] = 0.0;modelViewMatrix.m[14] = 0.0;modelViewMatrix.m[15] = 1.0;
    
    cameraPosition.x = 0;
    cameraPosition.y = 0;
    cameraPosition.z = 0;
    
    isProjModelViewDerty = true;
}
void Camera::setModelViewMatrix(float* matrix) {
    XMatrix4MakeWithArray(&modelViewMatrix, matrix);
 
    
    isProjModelViewDerty = true;
}
XVector3* Camera::getCameraPosition() {
    return &cameraPosition;
}
XMatrix4* Camera::getPerspectiveMatrix() {
    return &perspectiveMatrix;
}

XMatrix4* Camera::getModelViewMatrix() {
    return &modelViewMatrix;
}

XMatrix4* Camera::getProjModelViewMatrix() {
    if (isProjModelViewDerty) {
        isProjModelViewDerty = false;
        XMatrix4Mult(&projModelViewMatrix, &perspectiveMatrix, &modelViewMatrix);
    }
    return &projModelViewMatrix;
}


void Camera::calculateFarCorners(){
    
    float FOV =  (mAngle * PI) / 180.0f;
    float tanHalfFOV = tanf(FOV/ 2.0f);
    float farY       = tanHalfFOV * mFarPlane;
    float farX       = farY       * mAspectRatio;
    



	farCorners[0] = XVector3Make(-farX, -farY, -mFarPlane);
    farCorners[1] = XVector3Make( farX, -farY, -mFarPlane);
    farCorners[2] = XVector3Make( farX,  farY, -mFarPlane);
    farCorners[3] = XVector3Make(-farX,  farY, -mFarPlane);
}
float Camera::getFarPlane(){
    return mFarPlane;
}

XVector3* Camera::getFarcorners(){
    if (isFarCornersDerty) {
        isFarCornersDerty = false;
        calculateFarCorners();
    }
    return &farCorners[0];
}





/*
Matrix4x4*Camera::getProjViewInverse(){
    Matrix4x4LoadIdentity(&projViewInverse);
    Matrix4x4Multiply(&projViewInverse,&perspectiveMatrix4x4, &viewMatrix );
    Matrix4x4Inverse1(&projViewInverse);
    
    return &projViewInverse;
}
Matrix3x3*Camera::getInverseView3x3(){
    Matrix4x4Copy(&viewMatrixInv,  &viewMatrix);
    Matrix4x4Inverse1(&viewMatrixInv);
    Matrix4to3(&viewInverse3x3, &viewMatrixInv);
    return &viewInverse3x3;
}
*/


