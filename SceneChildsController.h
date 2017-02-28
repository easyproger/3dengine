//
//  SceneChildsController.h
//  XTech
//
//  Created by easy proger on 13.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __SceneChildsController__
#define __SceneChildsController__

#include <vector>
#include <iostream>
#include "BaseRenderObject.h"
#include <vector>
#include "ShaderCache.h"

#include "XObject.h"
#include "XRenderTypes.h"


#include "SceneNode.h"



class SceneChildsController {
public:
    SceneChildsController();
    ~ SceneChildsController();
    void addChild(SceneNode*child);
    
    
    std::vector<SceneNode*> childsList;
    
    
    void createQueryList();
    
    XQuery*querys;
    
    uint sizeQuerys;
    
    XQuery* getNewQuery();
    bool sceneWithShadows;
private:
    uint lastTechnicsID;
    void callbackItemInView(SceneNode*child);
    uint sizeAlloced;
    uint numQuerys;
};

#endif
