//
//  BaseRenderObject.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 26.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "BaseRenderObject.h"
#include "XUDID.h"


BaseRenderObject::BaseRenderObject(){
    castShadow = false;
    resaveShadow = false;
    tehnic = BACK_BUFFER_TEHNICS;
    model = NULL;
    udid = XUDID::me()->getUDID();
	XMatrix4MakeWithArray(&modelViewMatrix,
		               1.0,0.0,0.0,0.0,
                       0.0,1.0,0.0,0.0,
                       0.0,0.0,1.0,0.0,
                       0.0,0.0,0.0,1.0);


    resetTransformMatrix();
 
}
BaseRenderObject::~BaseRenderObject(){
    
}


uint BaseRenderObject::getUDID() {
    return udid;
}

XBoundingBox* BaseRenderObject::getBBox() {
    // XTODO : bbox create ! ( need get bbox from mesh )
    return NULL;
}
XVector3* BaseRenderObject::getCentroid() {
    // XTODO : calulate bbox ;
    return NULL;
}


void BaseRenderObject::clearViewMatrix() {
    XMatrix4MakeWithArray(&modelViewMatrix,
                          1.0,0.0,0.0,0.0,
                          0.0,1.0,0.0,0.0,
                          0.0,0.0,1.0,0.0,
                          0.0,0.0,0.0,1.0);
}

void BaseRenderObject::resetTransformMatrix(){
    x = 0;
    y = 0;
    z = 0;
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    
    diffX = 0;
    diffY = 0;
    diffZ = 0;
    diffRotationX = 0;
    diffRotationY = 0;
    diffRotationZ = 0;
    diffScaleX = 0;
    diffScaleY = 0;
    diffScaleZ = 0;
    
    isTransformMatrixDerty = false;
    isNormalMatrixDerty    = false;
}

Matrix4x4* BaseRenderObject::getTransformMatrix(){
    if (isTransformMatrixDerty) {
        calculateTransformMatrix();
    }
    return &matrix;
}

void BaseRenderObject::setModelViewMatrixF(float*data) {
	isNormalMatrixDerty = true;
    XMatrix4MakeWithArray(&modelViewMatrix, data);
}



XMatrix4* BaseRenderObject::getModelViewMatrix() {
    if (isTransformMatrixDerty) {
        calculateTransformMatrix();
    }
    return &modelViewMatrix;
}


void BaseRenderObject::setNormalMatrix(float*data){
	//XTODO: its bad idea ! but for test 
	normalMatrix = XMatrix3MakeWithArray(data);

}

XMatrix3* BaseRenderObject::getNormalMatrix(){
    if (isTransformMatrixDerty){
        calculateTransformMatrix();
    }
    if (isNormalMatrixDerty){
        calculateNormalMatrix();
    }
    return &normalMatrix;
}

Material*BaseRenderObject::getMaterial(){
    return material;
}
void BaseRenderObject::setMaterial(Material*mtl){
    material = mtl;
}
Mesh*BaseRenderObject::getMesh(){
    return model;
}

void BaseRenderObject::setMesh(Mesh*mesh){
    model = mesh;
}

