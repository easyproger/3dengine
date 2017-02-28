//
//  SceneGraph.cpp
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#include "SceneGraph.h"
SceneGraph::SceneGraph(){
    childController = new SceneChildsController();
    
}





void SceneGraph::createListObjects()
{
    childController->childsList.clear();
    for (unsigned int i = 0;i<childs.size();i++)
    {
        childs[i]->addChildsToRenderList(&childController->childsList);
    }
    childController->createQueryList();
}



void SceneGraph::addLightinTree(Light *object)
{
    listLights.push_back(object);
    lights.push_back(object);
}


void SceneGraph::addObjectinTree(SceneNode *object)
{
    childs.push_back(object);
    object->parent = NULL;
}
