//
//  SceneChildsController.cpp
//  XTech
//
//  Created by easy proger on 13.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "SceneChildsController.h"
#if defined(X_DEBUG)
#include "XDebugLoger.h"
#endif






SceneChildsController::~SceneChildsController() {
    for (unsigned int i = 0; i<sizeAlloced; i++) {
        free(querys[i].list);
    }
    free(querys);
}

SceneChildsController::SceneChildsController() {
    //RenderList* depthData = new RenderList();
    
    sizeAlloced = 0;
    numQuerys = 0;
    querys = (XQuery*)malloc(sizeof(XQuery));
    lastTechnicsID = 0;
    sceneWithShadows = false;
    sizeQuerys = 0;
}


#include "SceneNode.h"


void SceneChildsController::callbackItemInView(SceneNode*child) {
    XQuery * xQ;
    
    SceneNode**list = NULL;
    if (lastTechnicsID != child->tehnic) {
        lastTechnicsID = child->tehnic;
        xQ = getNewQuery();
        
        xQ->size = 0;
        xQ->sizeAlloced = 0;
    }else {
        xQ = &querys[numQuerys]; // не проверяем аллок так как он должен быть выделен
    }
    xQ->queryID = lastTechnicsID;
    list = xQ->list;
    
    
    if (xQ->size+1 >= xQ->sizeAlloced) {
        xQ->sizeAlloced+=10;
        xQ->list = (SceneNode**)realloc(xQ->list, sizeof(SceneNode*)*xQ->sizeAlloced);
    }
    
    
    
    
    xQ->list[xQ->size] = child;
    xQ->size++;
}



XQuery* SceneChildsController::getNewQuery() {
    numQuerys++;sizeQuerys++;
    if (numQuerys+1>=sizeAlloced) {
        sizeAlloced+=10;
        querys = (XQuery*)realloc(querys,sizeof(XQuery)*sizeAlloced);
        for (unsigned int i = numQuerys; i<sizeAlloced; i++) {
            querys[i].list = (SceneNode**)malloc(sizeof(SceneNode*));
            querys[i].sizeAlloced = 0;
            querys[i].renderID = 0;
            querys[i].size = 0;
        }
    }
    return &querys[numQuerys];
}

void SceneChildsController::createQueryList() {
    // XTODO : need create system culing
   

    lastTechnicsID = 0;
    
    
    XQuery * xQ;
    numQuerys = -1;
    sizeQuerys = 0;
    
    // FRUSTRUM shadow заглушка
    if (sceneWithShadows) {
        xQ = getNewQuery();
        
        xQ->queryID = SHADOW_DEPTH_TEHNICS;
        xQ->size = 0;
        xQ->sizeAlloced = 0;
        lastTechnicsID = SHADOW_DEPTH_TEHNICS;
        
        for (unsigned int i = 0; i < childsList.size(); i++) {
            SceneNode* child = childsList[i];
            if (!child->getMesh()) {
                continue;
            }
            
            if (child->castShadow){
                if (xQ->size+1 >= xQ->sizeAlloced) {
                    xQ->sizeAlloced+=10;
                    xQ->list = (SceneNode**)realloc(xQ->list, sizeof(SceneNode*)*xQ->sizeAlloced);
                }
                xQ->list[xQ->size] = child;
                xQ->size++;
            }
            // check view frustrum if yes go callBackItemInView
            
            // FRUSTRUM View заглушка
            callbackItemInView(childsList[i]);
        }
    }else {
        
        
        // теней нет объекты идут с простого фрустума
        for (unsigned int i = 0; i < childsList.size(); i++) {
            SceneNode* child = childsList[i];
            if (!child->getMesh()) {
                continue;
            }
            // check view frustrum if yes go callBackItemInView
            // FRUSTRUM View заглушка
            callbackItemInView(childsList[i]);
        }
    }
    
}


void SceneChildsController::addChild(SceneNode*child) {
    childsList.push_back(child);
}