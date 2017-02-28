//
//  CameraOld.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 08.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//


#ifndef __XCamera__
#define __XCamera__

#include "XTypes.h"
#include "XMatrix4Math.h"
#include "XMathTypes.h"


#include "Types.h"
#include "Vectors.h"

class Camera{
private:
    bool isFarCornersDerty,isProjModelViewDerty;
    float mFarPlane,mAspectRatio,mAngle;
    
    //farCorners
    XVector3 cameraPosition;
    
    XVector3 farCorners[4];
    
    XMatrix4 perspectiveMatrix;
    XMatrix4 modelViewMatrix;
    XMatrix4 projModelViewMatrix;
public:
    XMatrix4* getPerspectiveMatrix();
    XMatrix4* getModelViewMatrix();
    XMatrix4* getProjModelViewMatrix();
    XVector3* getCameraPosition();
    
    void setPerspectivematrix(float* data);
    void resetModelViewMatrix();
    
    XVector3* getFarcorners();
    
    float getFarPlane();
    void calculateFarCorners();
    void lookAt(const vec3& pos, const vec3& point, const vec3& up);
   
    
    
    void setModelViewMatrix(float* matrix);
    void setPerspective(float angle, float width, float height, float nearZ,  float farPlane);
    Camera();
};

#endif /* defined(__XCamera__) */