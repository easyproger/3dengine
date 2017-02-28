//
//  XAnimation.cpp
//  
//
//  Created by easy proger on 01.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "XAnimation.h"




SkinningAnimation::SkinningAnimation() {
    
    frames = NULL;
}



void SkinningAnimation::setNumBones(uint value) {
    numBones = value;
}

void XAnimation::setNumAnimationFrames(uint value) {
    numAnimationFrames = value;
}
