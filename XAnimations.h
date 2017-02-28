//
//  XAnimations.h
//  
//
//  Created by easy proger on 02.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef ____XAnimations__
#define ____XAnimations__

#include <iostream>
#include "XAnimation.h"
#include "FileLoader.h"

class XAnimations {
public:
    XAnimations(FileLoader*loader,std::map<std::string,SkinningFrame*>*skinAnimatorCache){
        _loader = loader;
		_skinCache = skinAnimatorCache;
        reloading = false;
    };
    ~XAnimations(){};
    
    std::vector<XAnimation*> animationsRequest;
    std::vector<XAnimation*> animationsLoading;
    
    void clear();
    void correctCache();
    void reload();
    void requestLoadAnimation(XAnimation*animation);
    XAnimation* getAnimation(const char*pathForAnim);
    XAnimation* getAnimation(uint id);
    void addAnimation(const char*cacheString,XAnimation*anim) ;
	XAnimation* addAnimation(const char*pathForAnim,const char*cacheString,int indexAnim);
    bool reloading;
private:
    FileLoader*_loader;
    std::map<std::string,SkinningFrame*>*_skinCache;
    std::map<std::string, int> cacheIDS;
    std::vector<XAnimation*> animationsCache;
    
};


#endif /* defined(____XAnimations__) */
