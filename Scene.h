//
//  Scene.h
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#ifndef SCENE_H__
#define SCENE_H__

#include "SceneNode.h"
#include "mathLib.h"
#include <vector>

using namespace std;

class Scene {
    
    typedef struct {
        std::vector<int> passes;
    }RenderList;
    
    
    
    
    
    /*
     так для начала получаем структуру в которой
     
     
     -> lists [
     list->[
     passes->[
     depth->
     main->
     ]
     objects->[
     data->
     ]
     ]
     ....
     ]
     
     
     */
    
public:
    
    
    Scene(int theWidth,int theHeight);
    ~Scene();
    void addOnObjectList(SceneNode *object);
    void addChild(SceneNode *object);
    void createList();
    int width;
    int height;
   
private:
};

#endif