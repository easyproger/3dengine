//
//  ObjectView.h
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#ifndef SCENENODE_H__
#define SCENENODE_H__

#include "Types.h"
#include "mathLib.h"
#include "Mesh.h"
#include <vector>
#include "Material.h"
#include "ShaderUtils.h"
#include "ShaderCache.h"

#include "BaseRenderObject.h"
#include "Light.h"


class SceneNode:public BaseRenderObject {
    struct ShaderCacheInRenderObject{
        Shader*shader;
    };
    
    ShaderCacheInRenderObject* shaderCashed;
private:
    XMatrix4 tmpMatrix,tmpMatrix2;
    uint flags;

	

public:
    bool isVisible;
    
    SceneNode();
    ~ SceneNode(){};
    
    std::vector<SceneNode*> *childsList;
    
    SceneNode* parent;
     
    double uid;
    
    Shader* getShaderObject(uint pass);
    
    std::vector<SceneNode*> childs;
    std::vector<Light*>     lights;
    
    virtual void calculateNormalMatrix();
    virtual void calculateTransformMatrix();
    virtual SkinningFrame* getSkinAnimation(bool update){return NULL;};
    
    void addX(float value);
    void addY(float value);
    void addZ(float value);
    
    void addRX(float value);
    void addRY(float value);
    void addRZ(float value);
    void addTransform(float x,float y,float z);
    void addScale(float x,float y,float z);
    
    
    void setX(float value);
    void setY(float value);
    void setZ(float value);
    
    void setScaleX(float value);
    void setScaleY(float value);
    void setScaleZ(float value);


	void setRotationX(float value);
    void setRotationY(float value);
    void setRotationZ(float value);
    
    void addChildsToRenderList(std::vector<SceneNode*> *list);
    
    void addLight(Light*object);
    void addChild(SceneNode*object);
    
    void setEnabledSkining(bool v);
    
private:
    
};

#endif