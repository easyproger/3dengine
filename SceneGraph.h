//
//  SceneGraph.h
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#ifndef SCENEGRAPH_H__
#define SCENEGRAPH_H__

#include "SceneNode.h"
#include <vector>
#include "SceneChildsController.h"


class SceneGraph {
public:
    
    
    SceneChildsController*childController;
    
    
    SceneGraph();
    ~SceneGraph(){};
    
    float x,y,z;
    void createListObjects();
    
    void addLightinTree(Light *object);
    void addObjectinTree(SceneNode *object);
    std::vector<SceneNode*> childs;
    std::vector<Light*> lights;
    std::vector<SceneNode*> listObjects;
    std::vector<Light*> listLights;
};
#endif