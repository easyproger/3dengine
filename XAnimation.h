//
//  XAnimation.h
//  
//
//  Created by easy proger on 01.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef ____XAnimation__
#define ____XAnimation__

#include <iostream>
#include <vector>

#include "XMathTypes.h"
#include "XAnimTypes.h"
#include "XMathBase.h"

#define MAX_BONES 40

class XAnimation {
    
public:
    XAnimation(){
        isValid = false;
        loading = false;
		skinningAnimation = 0;
		frameAnimation = 0;
		numAnimationFrames = 0;
        idInCache = 0;
		anim_frames = NULL;
        pathForFile = "";
        countUsed = 0;
	};
    virtual ~XAnimation(){
		if (numAnimationFrames && anim_frames) {
			free(anim_frames);
		}
	};
    
    
    void release() {
        if (countUsed > 0) {
            countUsed--;
            if (countUsed<=0) {
                removeData();
                countUsed = 0;
                isValid = false;
            }
        }
    }
    
    uint countUsed;
    
    std::string pathForFile;
    uint indexAnimationInFile;
    
    bool loading;
    bool isValid;
    uint idInCache;
    bool skinningAnimation;
	bool frameAnimation; 

	uint numAnimationFrames;
	AnimationFrame* anim_frames;
	void setNumAnimationFrames(uint value);

	virtual void removeData() {
        if (numAnimationFrames && anim_frames) {
            free(anim_frames);
        }
        anim_frames = NULL;
        loading = false;
        isValid = false;
        idInCache = 0;
        skinningAnimation = false;
        frameAnimation = false;
        numAnimationFrames = 0;
        indexAnimationInFile = 0;
        pathForFile = "";
    }
};

class SkinningAnimation:public XAnimation {
public:
    SkinningAnimation();
    ~SkinningAnimation() {
		XAnimation::~XAnimation();
        if (numAnimationFrames && frames) {
            for (unsigned int f = 0; f < numAnimationFrames; f++) {
                SkinningFrame* frame = &frames[f];
                free(frame->pos);
                free(frame->rot);
                free(frame->parentID);
            }
            free(frames);
        }
    }
    
    void removeData() {
		
        if (numAnimationFrames && frames) {
            for (unsigned int f = 0; f < numAnimationFrames; f++) {
                SkinningFrame* frame = &frames[f];
                free(frame->pos);
                free(frame->rot);
                free(frame->parentID);
            }
            free(frames);
        }
        isValid = false;
        numBones = 0;
        bones.resize(0);

		XAnimation::removeData();
    }
    
    void setNumBones(uint value);
    SkinningFrame* frames;
    uint numBones;
    
    std::vector<BoneInfo> bones;
private:

	
};


typedef struct{
    XAnimation*animation;
    uint currentFrameID;
}FrameAnimationInfo;

typedef struct{
    SkinningAnimation*animation;
    uint currentFrameID;
    float weightTrack;
    uint typeBlend;
}SkinAnimationInfo;

#endif /* defined(____XAnimation__) */
