//
//  SceneNode.cpp
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#include "SceneNode.h"
#include "Scene.h"




SceneNode::SceneNode()
{
 
    
    double now = 0;
    uid = now;
    
    Matrix4x4LoadIdentity(&matrix);
    
    
    shaderCashed = (ShaderCacheInRenderObject*)malloc(sizeof(ShaderCacheInRenderObject)*10);
    
    for (int i=0;i<10; i++) 
        shaderCashed[i].shader = 0;
    
    
    isVisible = true;
    
    x = 0;
    y = 0;
    z = 0;
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
    

	scaleX = 1.0;
	scaleY = 1.0;
	scaleZ = 1.0;

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
    

	float ident[9] ={ 1.0,0.0,0.0,
	                  0.0,1.0,0.0,
	                  0.0,0.0,1.0 };

	XMatrix3MakeWithArray(&normalMatrix,&ident[0]);
	  
}



void SceneNode::calculateNormalMatrix()
{
    XMatrix4GetMatrix3(&modelViewMatrix,&normalMatrix);
    bool isInvertable = false;
	normalMatrix = XMatrix3Invert(&normalMatrix, &isInvertable);
    isNormalMatrixDerty = false;
}

const float DEG2RAD = PI / 180.0f;



void SceneNode::calculateTransformMatrix(){
    
    XMatrix4MakeWithArray(&modelViewMatrix,
                          1.0,0.0,0.0,0.0,
                          0.0,1.0,0.0,0.0,
                          0.0,0.0,1.0,0.0,
                          0.0,0.0,0.0,1.0);

	XMatrix4Scale(&modelViewMatrix, scaleX, scaleY, scaleZ);
	
    XMatrix4RotationX(&tmpMatrix,rotationX*DEG2RAD);
    XMatrix4Mult(&tmpMatrix2, &tmpMatrix, &modelViewMatrix);
    XMatrix4MakeWithArray(&modelViewMatrix, &tmpMatrix2.m[0]);
	
	XMatrix4RotationY(&tmpMatrix,rotationY*DEG2RAD);
    XMatrix4Mult(&tmpMatrix2, &tmpMatrix, &modelViewMatrix);
    XMatrix4MakeWithArray(&modelViewMatrix, &tmpMatrix2.m[0]);

	XMatrix4RotationZ(&tmpMatrix,rotationZ*DEG2RAD);
    XMatrix4Mult(&tmpMatrix2, &tmpMatrix, &modelViewMatrix);
    XMatrix4MakeWithArray(&modelViewMatrix, &tmpMatrix2.m[0]);
	
	XMatrix4Translate(&modelViewMatrix,x, y, z);

    if (diffScaleX!=0 || diffScaleY!=0 || diffScaleZ!=0) {
        for (unsigned int i=0;i<childs.size();i++) childs[i]->addScale(diffScaleX,diffScaleY,diffScaleZ);
        diffScaleX = 0;
        diffScaleY = 0;
        diffScaleZ = 0;
    }
    if (diffRotationZ!=0) {
        for (unsigned int i=0;i<childs.size();i++) childs[i]->addRZ(diffRotationZ);
        diffRotationZ = 0;
    }
    if (diffRotationY!=0) {
        
        for (unsigned int i=0;i<childs.size();i++) childs[i]->addRY(diffRotationY);
        diffRotationY = 0;
    }
    if (diffRotationX!=0) {
        
        for (unsigned int i=0;i<childs.size();i++) childs[i]->addRX(diffRotationX);
        diffRotationX = 0;
    }
    
    if (diffZ!=0 || diffY!=0 || diffX!=0) {
        for (unsigned int i=0;i<childs.size();i++) childs[i]->addTransform(diffX,diffY,diffZ);
        diffZ = 0;
        diffY = 0;
        diffX = 0;
    }
    
    
    
    isTransformMatrixDerty = false;
}




void SceneNode::setScaleX(float value)
{
    diffScaleX = value-scaleX;
    if (diffScaleX==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    
    scaleX = value;
    
}

void SceneNode::setScaleY(float value)
{
    diffScaleY = value-scaleY;
    if (diffScaleY==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    
    scaleY = value;
    
}

void SceneNode::setScaleZ(float value)
{
    diffScaleZ = value-scaleZ;
    if (diffScaleZ==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    
    scaleZ = value;
}



void SceneNode::setX(float value)
{
    diffX = value-x;
    if (diffX==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    
    x = value;
    
}
void SceneNode::setY(float value)
{
    diffY = value-y;
    if (diffY==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;

    y = value;
   
}
void SceneNode::setZ(float value)
{
    if (value==z) {
        return;
    }
    diffZ = value-z;
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    z = value;
}

void SceneNode::setRotationX(float value)
{
    diffRotationX = value-rotationX;
    if (diffRotationX==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    rotationX = value;
    
}
void SceneNode::setRotationY(float value)
{
    diffRotationY = value-rotationY;
    if (diffRotationY==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    rotationY = value;
    
}
void SceneNode::setRotationZ(float value)
{
    diffRotationZ = value-rotationZ;
    if (diffRotationZ==0) {
        return;
    }
    isTransformMatrixDerty = true;
    isNormalMatrixDerty    = true;
    rotationZ = value;
}

void SceneNode::addRX(float value){
    XMatrix4RotationX(&tmpMatrix,value*DEG2RAD);
    XMatrix4Mult(&tmpMatrix2, &tmpMatrix, &modelViewMatrix);
    XMatrix4MakeWithArray(&modelViewMatrix, &tmpMatrix2.m[0]);
    for (unsigned int i=0;i<childs.size();i++) childs[i]->addRX(value);
}
void SceneNode::addRY(float value){
    XMatrix4RotationY(&tmpMatrix,value*DEG2RAD);
    XMatrix4Mult(&tmpMatrix2, &tmpMatrix, &modelViewMatrix);
    XMatrix4MakeWithArray(&modelViewMatrix, &tmpMatrix2.m[0]);
    for (unsigned int i=0;i<childs.size();i++) childs[i]->addRY(value);
}
void SceneNode::addRZ(float value){
    XMatrix4RotationZ(&tmpMatrix,value*DEG2RAD);
    XMatrix4Mult(&tmpMatrix2, &tmpMatrix, &modelViewMatrix);
    XMatrix4MakeWithArray(&modelViewMatrix, &tmpMatrix2.m[0]);
    for (unsigned int i=0;i<childs.size();i++) childs[i]->addRZ(value);
}



void SceneNode::addTransform(float x,float y,float z){
    XMatrix4AddTranslate(&modelViewMatrix,x, y, z);for (unsigned int i=0;i<childs.size();i++) childs[i]->addTransform(x,y,z);
}

void SceneNode::addScale(float x,float y,float z){
    XMatrix4Scale(&modelViewMatrix,x, y, z);for (unsigned int i=0;i<childs.size();i++) childs[i]->addScale(x,y,z);
}









// nodes methods

void SceneNode::addChildsToRenderList(std::vector<SceneNode*> *list)
{
    list->push_back(this);
    for (unsigned int i = 0;i<childs.size();i++)
    {
        childs[i]->addChildsToRenderList(list);
    }
}

void SceneNode::addLight(Light*object)
{
    lights.push_back(object);
    object->position.x = this->x;
    object->position.y = this->y;
    object->position.z = this->z;
}

void SceneNode::addChild(SceneNode*object)
{
    childs.push_back(object);
    object->parent = this;
}








Shader* SceneNode::getShaderObject(uint pass){
    if(pass > 10) return 0;
    
    //if (!shaderCashed[pass].shader){
        shaderCashed[pass].shader = getShader(material, model, pass);
    //}
    
    return shaderCashed[pass].shader;
}




