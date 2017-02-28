//
//  SkinningMath.h
//  
//
//  Created by easy proger on 02.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//


#include "SkinningMath.h"
#include "XVector3Math.h"
#include "XVector4Math.h"
#include "XMatrix4Math.h"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <algorithm>
#endif

void getChildsForBone(BoneInfo *boneIn,std::vector<BoneInfo>*bones) {
    std::vector<BoneInfo> childs;
    for (unsigned int i =0; i < bones->size(); i++) {
        BoneInfo*bone = &bones->operator[](i);
        int parentID = bone->parentID;
        if (parentID == boneIn->boneID) {
            boneIn->childs.push_back(bone);
            getChildsForBone(bone,bones);
        }
    }
    
}

bool preSortBones(BoneInfo i, BoneInfo j) {
    return i.parentID < j.parentID;
}


void getFlatTreeBones(BoneInfo *boneIn,std::vector<BoneInfo>*bones,uint *index) {

    for (unsigned int i = 0;i< boneIn->childs.size(); i++) {
        
        bones->operator[]((*index)).boneID   = boneIn->childs[i]->boneID;
        bones->operator[]((*index)).parentID = boneIn->childs[i]->parentID;
        (*index)++;
        getFlatTreeBones(boneIn->childs[i],bones,index);
    }
}

void getChildsForBone2(BoneInfo *boneIn,std::vector<BoneInfo*>*bones) {
    std::vector<BoneInfo> childs;
    for (unsigned int i =0; i < bones->size(); i++) {
        BoneInfo*bone = bones->operator[](i);
        int parentID = bone->parentID;
        if (parentID == boneIn->boneID) {
            boneIn->childs.push_back(bone);
            getChildsForBone2(bone,bones);
        }
    }
    
}
bool preSortBones2(BoneInfo *i, BoneInfo *j) {
    return i->parentID < j->parentID;
}
void fillGroups(std::vector<BoneInfo*> *bones_group,BoneInfo*boneRoot,std::vector<BoneInfo>*bones) {
    
    
    std::vector<BoneInfo> childs;
    for (unsigned int i =0; i < bones->size(); i++) {
        BoneInfo*bone = &bones->operator[](i);
        int parentID = bone->parentID;
        if (parentID == boneRoot->boneID) {
            // here
            bones_group->push_back(bone);
            fillGroups(bones_group,bone,bones);
        }
    }
}

bool trynow = false;

void sortBones (std::vector<BoneInfo>*bones) {
    std::vector<BoneInfo> bones_m;
    bones_m.resize(bones->size());
    
    int lastIndex = 0;
    for (int i = 0; i < bones->size(); i++) {
        // search root's
        
        BoneInfo*bone = &(*bones)[i];
        
        if (bone->parentID == -1) {
            std::vector<BoneInfo*> bones_group;
            
            fillGroups(&bones_group,bone,bones);
            
            std::sort(bones_group.begin(), bones_group.end(), preSortBones2);
            bones_group.push_back(bone);
            getChildsForBone2(bone,&bones_group);
            
            
            std::vector<BoneInfo> boneTmp;
            boneTmp.resize(bones_group.size());
            uint index = 1;
            
            boneTmp[0].boneID   = bone->boneID;
            boneTmp[0].parentID = bone->parentID;
            
            getFlatTreeBones(bone,&boneTmp,&index);
            
            for (unsigned int w = 0 ; w < boneTmp.size(); w++) {
                bones_m[lastIndex].boneID   = boneTmp[w].boneID;
                bones_m[lastIndex].parentID = boneTmp[w].parentID;
                lastIndex++;
            }
        }
    }
    for (unsigned int i = 0 ; i < bones->size(); i++) {
        bones->operator[](i).boneID   = bones_m[i].boneID;
        bones->operator[](i).parentID = bones_m[i].parentID;
    }
    
    
 
    return;


    trynow = true;

    std::sort(bones->begin(), bones->end(), preSortBones);
    BoneInfo*bone = &bones->operator[](0);

	getChildsForBone(bone,bones);
    
    
    
    std::vector<BoneInfo> boneTmp;
    boneTmp.resize(bones->size());
    uint index = 1;
    
    
    boneTmp[0].boneID   = bone->boneID;
    boneTmp[0].parentID = bone->parentID;
    
    getFlatTreeBones(bone,&boneTmp,&index);
    
    for (unsigned int i = 0 ; i < bones->size(); i++) {
        bones->operator[](i).boneID   = boneTmp[i].boneID;
        bones->operator[](i).parentID = boneTmp[i].parentID;
    }
    
}

std::vector<std::vector<uint>> getSceleton(std::vector<BoneInfo>*bones) {
    
 
    std::vector<std::vector<uint>> s;
    
    return s;
}

void printMatrix(float*array) {
    int rowID = 0;
    for (int row=0; row<4; row++)
    {
        for(int columns=0; columns<4; columns++) {
            printf("%f     ", array[rowID]);
            rowID++;
        }
        printf("\n");
    }
}


void removeSkinningFrame(SkinningFrame*f) {
    free(f->pos);
    free(f->rot);
    free(f->parentID);
    free(f);
}


SkinningFrame* getSkinningFrame(std::vector<SkinAnimationInfo *> *skinningInfos,SkinningFrame *bindFrame,uint numBones,std::vector<BoneInfo>*bonesIerarhy) {
    // result frame
    SkinningFrame*frameResult = (SkinningFrame*)malloc(sizeof(SkinningFrame));
    // alloc mem result frame
    frameResult->pos = (XVector3*)malloc(sizeof(XVector3)*numBones);
    frameResult->rot = (XVector4*)malloc(sizeof(XVector4)*numBones);
    frameResult->parentID = (int*)malloc(sizeof(int)*numBones);
    
    // clearing mem on result frame
    memset(frameResult->pos,      0, sizeof(XVector3)*numBones);
    memset(frameResult->rot,      0, sizeof(XVector4)*numBones);
    memset(frameResult->parentID, 0, sizeof(int)*numBones);
    
    
    //XTODO: bad idea ! need translate to global tmp matrixes !!!
    XMatrix4*matrixForCalculate  = (XMatrix4*)malloc(sizeof(XMatrix4)*numBones);
    XMatrix4*matrixForCalculate2 = (XMatrix4*)malloc(sizeof(XMatrix4)*numBones);
    
    for (unsigned int skinAnimationID = 0; skinAnimationID < skinningInfos->size(); skinAnimationID++) {
        SkinAnimationInfo *info = skinningInfos->operator[](skinAnimationID);
        if (info->animation->numBones != numBones) {
            continue;
        }
        
       
        
        
        uint numFramesOnNewAnimation = info->animation->numAnimationFrames;
        uint needleFrameID = info->currentFrameID;
        if (needleFrameID >= numFramesOnNewAnimation) {
            needleFrameID = numFramesOnNewAnimation-1;
        }
        
        SkinningFrame*blendedFrame = &info->animation->frames[needleFrameID];
        if (!blendedFrame) {
            continue;
        }
        
        for (unsigned int bi = 0; bi < bonesIerarhy->size(); bi++) {
            BoneInfo*boneInfo = &bonesIerarhy->operator[](bi);
            XVector3Lepr( &frameResult->pos[boneInfo->boneID], &frameResult->pos[boneInfo->boneID], &blendedFrame->pos[boneInfo->boneID], info->weightTrack);
            XQuaternion4Slerp(&frameResult->rot[boneInfo->boneID], &frameResult->rot[boneInfo->boneID], &blendedFrame->rot[boneInfo->boneID], info->weightTrack);
            XMatrix4MakeWithQuaternionAndTranslation3(&matrixForCalculate[boneInfo->boneID], &frameResult->rot[boneInfo->boneID], &frameResult->pos[boneInfo->boneID]);
        }
       
        
        for (unsigned int b = 0; b < bonesIerarhy->size(); b++) {
            BoneInfo*boneInfo = &bonesIerarhy->operator[](b);
            if (boneInfo->parentID == -1) {
                XMatrix4MakeWithArray(&matrixForCalculate2[boneInfo->boneID], &matrixForCalculate[boneInfo->boneID].m[0]);
            }else {
                XMatrix4Mult(&matrixForCalculate2[boneInfo->boneID], &matrixForCalculate[boneInfo->boneID], &matrixForCalculate2[boneInfo->parentID]);
            }
        }
        
        for (unsigned int b = 0; b < bonesIerarhy->size(); b++) {
            BoneInfo*boneInfo = &bonesIerarhy->operator[](b);
            
            //XTODO: remove transpose !
            XMatrix4Transpose(&matrixForCalculate2[boneInfo->boneID], &matrixForCalculate2[boneInfo->boneID]);
            XMatrix4Mult(&matrixForCalculate[boneInfo->boneID], &matrixForCalculate2[boneInfo->boneID], &bindFrame->mat[boneInfo->boneID]);
            
            XQuaternionMakeWithMatrix2(&frameResult->rot[boneInfo->boneID],&matrixForCalculate[boneInfo->boneID]);
            frameResult->pos[boneInfo->boneID].x = matrixForCalculate[boneInfo->boneID].m[12];
            frameResult->pos[boneInfo->boneID].y = matrixForCalculate[boneInfo->boneID].m[13];
            frameResult->pos[boneInfo->boneID].z = matrixForCalculate[boneInfo->boneID].m[14];
        }
    }
    
    
    free(matrixForCalculate);
    free(matrixForCalculate2);
    
    return frameResult;
}



