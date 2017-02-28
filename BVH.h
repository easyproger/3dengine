//
//  BVH.h
//
//  Created by easy proger on 11.05.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __BVH__
#define __BVH__

#include <iostream>
#include "SceneNode.h"


struct BVHFlatNode {
    XBoundingBox *bbox;
    unsigned int start, nPrims, rightOffset;
};


class BVH {
    
    unsigned int nNodes, nLeafs, leafSize;
    std::vector<SceneNode*>* build_prims;
    
public:
    BVH(std::vector<SceneNode*>* objects,unsigned int leafSize);
    ~BVH();
    BVHFlatNode *flatTree;
    void build();
};

#endif /* defined(__BVH__) */
