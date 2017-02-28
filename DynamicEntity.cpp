//
//  DynamicEntity.cpp
//
//  Created by easy proger on 01.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "DynamicEntity.h"
#include "SkinningMath.h"
#include "XMathBase.h"

#include <sstream>



void DynamicEntity::playAnimation(uint idInCache,bool loop,float*skinAnimIndx,float*frameAnimIndx){
    XAnimation*anim = _animationsCache->getAnimation(idInCache);
	(*skinAnimIndx)=-1;
	(*frameAnimIndx)=-1;
    if (anim) {
		if (anim->skinningAnimation) {
            SkinAnimationInfo*info = (SkinAnimationInfo*)malloc(sizeof(SkinAnimationInfo));
            info->animation = (SkinningAnimation*) anim;
            info->currentFrameID = 0;
            info->weightTrack = 1.0;
            info->typeBlend = ANIMATION_BLEND_INTERPOLATION;
            if (skinningAnimations.size() > 2) {
                SkinAnimationInfo*infoD = skinningAnimations[0];
                free(infoD);
                skinningAnimations.erase(skinningAnimations.begin());
            }
            skinningAnimations.push_back(info);
            (*skinAnimIndx)=skinningAnimations.size()-1;
        }
		if (anim->frameAnimation) {
			FrameAnimationInfo*info = (FrameAnimationInfo*)malloc(sizeof(FrameAnimationInfo));
			info->animation = anim;
			info->currentFrameID = 0;

			if (frameAnimations.size() > 2) {
                FrameAnimationInfo*infoD = frameAnimations[0];
                free(infoD);
                frameAnimations.erase(frameAnimations.begin());
            }
            frameAnimations.push_back(info);
            (*frameAnimIndx)=frameAnimations.size()-1;
		}
    }
}



uint DynamicEntity::getFrameAnimation(uint idAnim,uint type) {
	if (type == 0) {
		SkinAnimationInfo *animInfo = skinningAnimations[idAnim];
    	return animInfo->currentFrameID;
	}else if (type == 1) {
		FrameAnimationInfo *animInfo = frameAnimations[idAnim];
        if (!animInfo->animation->isValid) {
            // here need request reload animation !
            _animationsCache->requestLoadAnimation(animInfo->animation);
        }
    	return animInfo->currentFrameID;
	}
    return 0;
}
void DynamicEntity::setFrameAnimation(uint idFrame,uint idAnim,uint type) {
    if (type == 0) {
		SkinAnimationInfo *animInfo = skinningAnimations[idAnim];
		animInfo->currentFrameID = idFrame;
    	if (animInfo->currentFrameID > animInfo->animation->numAnimationFrames-1) {
        	animInfo->currentFrameID= 0;
    	}
	}else if (type == 1) {
		FrameAnimationInfo *animInfo = frameAnimations[idAnim];
		animInfo->currentFrameID = idFrame;
    	if (animInfo->currentFrameID > animInfo->animation->numAnimationFrames-1) {
        	animInfo->currentFrameID= 0;
    	}
	}
}
FrameAnimationInfo* DynamicEntity::getFrameAnimation(uint idAnim) {
	return frameAnimations[idAnim];
}
SkinningFrame* DynamicEntity::getSkinAnimation(bool update) {
    
    
    if (cache->size() > 1000) {
        std::map<std::string, SkinningFrame*>::iterator it=cache->begin();
        for (int i = 0; i<100; i++) {
            removeSkinningFrame(it->second);
            cache->erase(it++);
        }
    }

    
    
    
    
    std::string udid = "";
    
    for (unsigned int i = 0; i < skinningAnimations.size(); i++) {
        SkinAnimationInfo *animInfo = skinningAnimations[i];
        if (animInfo) {
            if (!animInfo->animation->isValid) {
                // here need request reload animation !
                _animationsCache->requestLoadAnimation(animInfo->animation);
                continue;
            }
            char str[255];
            itostr(animInfo->animation->idInCache,str);
            udid+=str;
			udid+="-";
            itostr(animInfo->currentFrameID,str);
            udid+=str;
            udid+="|";
        }
    }
    
    
    
    std::map<std::string, SkinningFrame*>::iterator it=cache->find(udid);
    if(it!=cache->end()) {
        return (*it).second;
    }else {
        // math skinning !!!
        Mesh*mesh = this->getMesh();
        if (mesh && mesh->bindFrame) {
            SkinningFrame*frame = getSkinningFrame(&skinningAnimations,mesh->bindFrame,mesh->numBones,&mesh->boneIerarhy);
            (*cache)[udid] = frame;
            return frame;
        }
    }
    
    return NULL;
}

char* DynamicEntity::itoa(int val, int base){
    
    static char buf[32] = {0};
    
    int i = 30;
    
    for(; val && i ; --i, val /= base)
        
        buf[i] = "0123456789abcdef"[val % base];
    
    return &buf[i+1];
    
}