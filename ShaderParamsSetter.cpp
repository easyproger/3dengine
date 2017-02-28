 //
//  ShaderParamsSetter.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 26.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "ShaderParamsSetter.h"

ShaderParamsSetter::ShaderParamsSetter(Camera*camera,uint depthBuffer,uint normalAndMaterialBuffer,uint albedoBuffer,uint lightBuffer){
    this->camera                  = camera;
    this->depthBuffer             = depthBuffer;
    this->normalAndMaterialBuffer = normalAndMaterialBuffer;
    this->albedoBuffer            = albedoBuffer;
    this->lightBuffer             = lightBuffer;
    
    
    
    indexTexture = 0;
    
    texIDS[0] = GL_TEXTURE0;
    texIDS[1] = GL_TEXTURE1;
    texIDS[2] = GL_TEXTURE2;
    texIDS[3] = GL_TEXTURE3;
    texIDS[4] = GL_TEXTURE4;
    texIDS[5] = GL_TEXTURE5;
    texIDS[6] = GL_TEXTURE6;
    texIDS[7] = GL_TEXTURE7;
    texIDS[8] = GL_TEXTURE8;
    texIDS[9] = GL_TEXTURE9;
    
}

Camera*ShaderParamsSetter::getCamera(){
    return camera;
}
void ShaderParamsSetter::resetTextureIndex(){
    indexTexture = 0;
}

void ShaderParamsSetter::setLight(BaseLight*light){
    indexTexture = 0;
    this->light = light;
}
void ShaderParamsSetter::setRenderObject(BaseRenderObject*renderObject){
    indexTexture = 0;
    baseRenderObject = renderObject;
}

void ShaderParamsSetter::setDepthBuffer(uint texID){
    depthBuffer = texID;
}

void ShaderParamsSetter::setObjectSpecularMapTextureUniform(uint idUniform){
    glActiveTexture ( texIDS[indexTexture] );
    Material*mat = baseRenderObject->getMaterial();
    glBindTexture   ( GL_TEXTURE_2D,  mat->specularTexture->texID);
    glUniform1i (idUniform,indexTexture);
    indexTexture++;
}
void ShaderParamsSetter::setObjectNormalMapTextureUniform(uint idUniform){
    glActiveTexture ( texIDS[indexTexture] );
    Material*mat = baseRenderObject->getMaterial();
    glBindTexture   ( GL_TEXTURE_2D,  mat->normalMapTexture->texID);
    glUniform1i (idUniform,indexTexture);
    indexTexture++;
}
void ShaderParamsSetter::setObjectDiffuseTextureUniform(uint idUniform){
    glActiveTexture ( texIDS[indexTexture] );
    Material*mat = baseRenderObject->getMaterial();
    glBindTexture   ( GL_TEXTURE_2D,  mat->diffuseTexture->texID);
    glUniform1i (idUniform,indexTexture);
    indexTexture++;
}
void ShaderParamsSetter::setCameraPositionUniform(uint idUniform){
    XVector3* cameraPosition = camera->getCameraPosition();
    glUniform3f(idUniform,cameraPosition->x,cameraPosition->y,cameraPosition->z);
}
void ShaderParamsSetter::setCameraViewInverse3x3Uniform(uint idUniform){
    
    printf("Hey create inverse matrix for setCameraViewInverse3x3Uniform from camera ;) \n");
    
    //glUniformMatrix3fv(idUniform, 1, false, &camera->getInverseView3x3()->m[0][0]);
}
void ShaderParamsSetter::setLightPositionUniform(uint idUniform){
    glUniform3f(idUniform, light->position.x,light->position.y,light->position.z);
}
void ShaderParamsSetter::setModelNormalMatrixUniform(uint idUniform){
    glUniformMatrix3fv(idUniform, 1, false, &baseRenderObject->getNormalMatrix()->m[0]);
}
void ShaderParamsSetter::setFarPlaneUniform(uint idUniform){
    glUniform1f(idUniform,camera->getFarPlane());
}
void ShaderParamsSetter::setWorldObjectMatrixUniform(uint idUniform){
    glUniformMatrix4fv(idUniform, 1, false, &baseRenderObject->getModelViewMatrix()->m[0]);
}
void ShaderParamsSetter::setCameraViewMatrixUniform(uint idUniform){
    glUniformMatrix4fv(idUniform, 1, false, &camera->getModelViewMatrix()->m[0]);
}
void ShaderParamsSetter::setPerspectiveMatrixUniform(uint idUniform){
    glUniformMatrix4fv(idUniform, 1, false,  &camera->getPerspectiveMatrix()->m[0]);
}
void ShaderParamsSetter::setPerspectiveViewInverseUniform(uint idUniform){
    printf("Hey create inverse matrix for ShaderParamsSetter from camera ;) \n");
   // glUniformMatrix4fv(idUniform, 1, false,  &camera->getProjViewInverse()->m[0][0]);
}

// new math )
void ShaderParamsSetter::setPerspectiveLightMatrixUniform(uint idUniform){
    glUniformMatrix4fv(idUniform, 1, false,  &light->getPerspectiveMatrix()->m[0]);
}
void ShaderParamsSetter::setLightViewMatrixUniform(uint idUniform){
    glUniformMatrix4fv(idUniform, 1, false,  &light->getModelViewMatrix()->m[0]);
}
void ShaderParamsSetter::setLightProjViewMatrixUniform(uint idUniform) {
    glUniformMatrix4fv(idUniform, 1, false, &light->getProjModelViewMatrix()->m[0]);
}
void ShaderParamsSetter::setLightProjViewMatrixSTUniform(uint idUniform) {
    glUniformMatrix4fv(idUniform, 1, false, &light->getProjModelViewMatrixST()->m[0]);
}
void ShaderParamsSetter::setProjCameraModelViewUniform(uint idUniform) {
    glUniformMatrix4fv(idUniform, 1, false,  &camera->getProjModelViewMatrix()->m[0]);
}

void ShaderParamsSetter::setBonesTranslations(uint idUniform) {
    Mesh*mesh = baseRenderObject->getMesh();
    SkinningFrame*frame = baseRenderObject->getSkinAnimation(true);
    if (frame)
    glUniform3fv(idUniform,mesh->numBones, &frame->pos->v[0]);
}

void ShaderParamsSetter::setBonesRotations(uint idUniform) {
    Mesh*mesh = baseRenderObject->getMesh();
    SkinningFrame*frame = baseRenderObject->getSkinAnimation(false);
    if (frame)
    glUniform4fv(idUniform,mesh->numBones, &frame->rot->v[0]);
    
}



void ShaderParamsSetter::setLightBufferUniform(uint idUniform){   
    glActiveTexture ( texIDS[indexTexture] );
    glBindTexture   ( GL_TEXTURE_2D, lightBuffer); 
    glUniform1i (idUniform,indexTexture);
    indexTexture++;
}
void ShaderParamsSetter::setAlbedoBufferUniform(uint idUniform){   
    glActiveTexture ( texIDS[indexTexture] );
    glBindTexture   ( GL_TEXTURE_2D, albedoBuffer); 
    glUniform1i (idUniform,indexTexture);
    indexTexture++;
}
void ShaderParamsSetter::setNormalAndMaterialBufferUniform(uint idUniform){   
    glActiveTexture ( texIDS[indexTexture] );
    glBindTexture   ( GL_TEXTURE_2D, normalAndMaterialBuffer); 
    glUniform1i (idUniform,indexTexture);
    indexTexture++;
}
void ShaderParamsSetter::setDepthBufferUniform(uint idUniform){   
    glActiveTexture ( texIDS[indexTexture] );
    glBindTexture   ( GL_TEXTURE_2D, depthBuffer); 
    glUniform1i (idUniform,indexTexture);
    indexTexture++;
}



