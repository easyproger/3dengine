//
//  BaseRenderObject.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 26.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
#ifndef BASE_RENDER_OBJECT_H__
#define BASE_RENDER_OBJECT_H__


#include "mathLib.h"
#include "Material.h"
#include "Mesh.h"
#include "XRendererDefines.h"

#include "XMathTypes.h"
#include "XMatrix4Math.h"
#include "XMatrix3Math.h"
#include "XBoundingBox.h"
#include "XAnimTypes.h"


typedef struct {
    int *passes;
    int length;
}PassesObject;


class BaseRenderObject {
    
private:
    
    XBoundingBox*bbox;
    uint udid;
protected:
    XMatrix4 modelViewMatrix;
    Material*material;
    Mesh*model;
    float diffX;
    float diffY;
    float diffZ;
    float diffRotationX;
    float diffRotationY;
    float diffRotationZ;
    float diffScaleX;
    float diffScaleY;
    float diffScaleZ;
    
    Matrix4x4 matrix;
    Matrix4x4 m;
    
    XMatrix3 normalMatrix;
    
    bool isNormalMatrixDerty;
    bool isTransformMatrixDerty;

public:
    XMatrix4* getModelViewMatrix();
    void clearViewMatrix();
    void setModelViewMatrixF(float*data);
    
    
    bool castShadow;
    bool resaveShadow;
    
    
    // заполняется по мере изменения параметров объекта
    PassesObject objectsPasses;
    
    
    float scaleX,scaleY,scaleZ;
    
    float x,y,z;
    float rotationX,rotationZ,rotationY;

    void resetTransformMatrix();
    
    // bbox methods !
    XBoundingBox* getBBox();
    XVector3* getCentroid();
  
    Mesh*getMesh();
    void setMesh(Mesh*mesh);
    
    bool visible;
    Material*getMaterial();
    void setMaterial(Material*mtl);
    
    
    uint tehnic;
    
    
    BaseRenderObject();
    ~BaseRenderObject();
    
    virtual void calculateNormalMatrix(){};
    virtual void calculateTransformMatrix(){};
    virtual SkinningFrame* getSkinAnimation(bool update){return NULL;};
    
    
    
    XMatrix3* getNormalMatrix();
	void setNormalMatrix(float*data);

    Matrix4x4* getTransformMatrix();
    uint getUDID();
};

#endif