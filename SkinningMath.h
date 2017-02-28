//
//  SkinningMath.h
//  
//
//  Created by easy proger on 02.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _SkinningMath_h
#define _SkinningMath_h

#define ANIMATION_TYPE_SKINNING 0
#define ANIMATION_TYPE_FRAME 1
#define ANIMATION_BLEND_INTERPOLATION 0


#include <stdio.h>
#include <iostream>
#include "XAnimTypes.h"
#include "XAnimation.h"

bool preSortBones(BoneInfo i, BoneInfo j);
void getChildsForBone(BoneInfo *boneIn,std::vector<BoneInfo>*bones);
void sortBones (std::vector<BoneInfo>*bones);
std::vector<std::vector<uint>> getSceleton(std::vector<int>*bones);
std::vector<uint> getChildsForBone(uint id,std::vector<int>*bones);
SkinningFrame* getSkinningFrame(std::vector<SkinAnimationInfo *> *skinningInfos,SkinningFrame *bindFrame,uint numBones,std::vector<BoneInfo>*bonesIerarhy);
void removeSkinningFrame(SkinningFrame*f);
#endif
