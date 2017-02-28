//
//  XAnimations.cpp
//  
//
//  Created by easy proger on 02.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "XAnimations.h"


XAnimation* XAnimations::getAnimation(uint id) {
    if (id <=animationsCache.size()-1 ) {
        
        if (animationsCache[id]->isValid) {
            // here need request reload animation !
            requestLoadAnimation(animationsCache[id]);
        }
        
        return animationsCache[id];
    }
    return NULL;
}
XAnimation* XAnimations::getAnimation(const char*pathForAnim) {
    if (cacheIDS.find(pathForAnim) != cacheIDS.end()) {
        int indxInCache = cacheIDS[pathForAnim];
        return animationsCache[indxInCache];
    }
    return NULL;
}

void XAnimations::requestLoadAnimation(XAnimation*animation) {
    if (reloading) {
        return;
    }
    
    if (animation->loading) {
        return;
    }
    animation->loading = true;
    animationsRequest.push_back(animation);
}

void XAnimations::clear() {
    for (int i = 0; i < animationsCache.size(); i++) {
        XAnimation*anim = animationsCache[i];
        if (anim) {
            anim->removeData();
        }
    }
    
    animationsCache.resize(0);
    cacheIDS.erase(cacheIDS.begin(),cacheIDS.end());


	std::map<std::string, SkinningFrame*>::iterator it=_skinCache->begin();
	while(it!=_skinCache->end()) {
		removeSkinningFrame(it->second);
        _skinCache->erase(it++);
	}



}



void XAnimations::correctCache() {
    for (int i = 0; i < animationsCache.size(); i++) {
        XAnimation*anim = animationsCache[i];
        if (anim) {
            anim->release();
        }
    }
}


void XAnimations::addAnimation(const char*cacheString,XAnimation*anim) {

    if (cacheIDS.find(cacheString) != cacheIDS.end()) {
        return;
    }
    
    if (anim) {
        anim->idInCache = animationsCache.size();
        cacheIDS[cacheString] = anim->idInCache;
        animationsCache.push_back(anim);
    }
}

XAnimation* XAnimations::addAnimation(const char*pathForAnim,const char*cacheString,int indexAnim) {

    if (cacheIDS.find(cacheString) != cacheIDS.end()) {
        int indxInCache = cacheIDS[cacheString];
        return animationsCache[indxInCache];
    }
    
    XAnimation* anim = _loader->loadAnimationFile(pathForAnim,indexAnim);
    if (anim) {
        anim->idInCache = animationsCache.size();
        cacheIDS[cacheString] = anim->idInCache;
        animationsCache.push_back(anim);
    }
    return anim;
}