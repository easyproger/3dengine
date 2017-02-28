//
//  DynamicEntity.h
//
//  Created by easy proger on 01.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef ____DynamicEntity__
#define ____DynamicEntity__

#include <iostream>
#include "SceneNode.h"
#include "XAnimation.h"
#include "XAnimations.h"


class DynamicEntity:public SceneNode {
public:
    DynamicEntity(std::map<std::string,SkinningFrame*>*skinAnimatorCache,XAnimations*animationsCache){
        cache = skinAnimatorCache;
        _animationsCache = animationsCache;
    };
    ~DynamicEntity(){
        for (unsigned int i = 0; i < skinningAnimations.size(); i++) {
            free(skinningAnimations[i]);
        }
        for (unsigned int i = 0; i < frameAnimations.size(); i++) {
            free(frameAnimations[i]);
        }
        frameAnimations.clear();
    };
    
    uint getFrameAnimation(uint idAnim,uint type);
    void setFrameAnimation(uint idFrame,uint idAnim,uint type);
    void playAnimation(uint idInCache,bool loop,float*skinAnimIndx,float*frameAnimIndx);

    virtual FrameAnimationInfo* getFrameAnimation(uint idAnim);
    virtual SkinningFrame* getSkinAnimation(bool update);
private:
    std::map<std::string,SkinningFrame*> *cache;
    XAnimations*_animationsCache;
    char* itoa(int val, int base);
    std::vector<SkinAnimationInfo *> skinningAnimations;
	std::vector<FrameAnimationInfo *> frameAnimations;
};



#endif /* defined(____DynamicEntity__) */
