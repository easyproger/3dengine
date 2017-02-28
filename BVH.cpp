//
//  BVH.cpp
//
//  Created by easy proger on 11.05.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "BVH.h"




BVH::BVH(std::vector<SceneNode*>* objects,unsigned int leafSize): nNodes(0), nLeafs(0), leafSize(leafSize), build_prims(objects), flatTree(NULL) {
    
    
    
}


BVH::~BVH() {
    delete[] flatTree;
}


struct BVHBuildEntry {
    // If non-zero then this is the index of the parent. (used in offsets)
    unsigned int parent;
    // The range of objects in the object list covered by this node.
    unsigned int start, end;
};

void BVH::build(){
	/*
    BVHBuildEntry todo[128];
    unsigned int stackptr = 0;
	const unsigned int Untouched    = 0xffffffff;
	const unsigned int TouchedTwice = 0xfffffffd;
    
    // Push the root
    todo[stackptr].start = 0;
    todo[stackptr].end = (unsigned int)build_prims->size();
    todo[stackptr].parent = 0xfffffffc;
    stackptr++;
    
	BVHFlatNode node;
	std::vector<BVHFlatNode> buildnodes;
	buildnodes.reserve(build_prims->size()*2);
    
    while(stackptr > 0) {
		// Pop the next item off of the stack
		BVHBuildEntry &bnode( todo[--stackptr] );
		unsigned int start = bnode.start;
		unsigned int end = bnode.end;
		unsigned int nPrims = end - start;
        
		nNodes++;
		node.start = start;
		node.nPrims = nPrims;
		node.rightOffset = Untouched;
        
   
		// Calculate the bounding box for this node
		XBoundingBox *bb( (*build_prims)[start]->getBBox());
		XBoundingBox *bc = new XBoundingBox(); // XTODO : delete nodes after delete flatTree !
        bc->setVector((*build_prims)[start]->getCentroid());
        
		for(unsigned int p = start+1; p < end; ++p) {
			bb->expandToInclude( (*build_prims)[p]->getBBox());
			bc->expandToInclude( (*build_prims)[p]->getCentroid());
		}
		node.bbox = bb;
        
        // If the number of primitives at this point is less than the leaf
        // size, then this will become a leaf. (Signified by rightOffset == 0)
		if(nPrims <= leafSize) {
			node.rightOffset = 0;
			nLeafs++;
		}
		
		buildnodes.push_back(node);
		
		// Child touches parent...
		// Special case: Don't do this for the root.
		if(bnode.parent != 0xfffffffc) {
			buildnodes[bnode.parent].rightOffset --;
            
			// When this is the second touch, this is the right child.
			// The right child sets up the offset for the flat tree.
			if( buildnodes[bnode.parent].rightOffset == TouchedTwice ) {
				buildnodes[bnode.parent].rightOffset = nNodes - 1 - bnode.parent;
			}
		}
        
		// If this is a leaf, no need to subdivide.
		if(node.rightOffset == 0)
			continue;
        
		// Set the split dimensions
		unsigned int split_dim = bc->maxDimension();
        
		// Split on the center of the longest axis
		float split_coord = .5f * (bc->minPt.v[split_dim] + bc->maxPt.v[split_dim]);
		
		// Partition the list of objects on this split
		unsigned int mid = start;
		for(unsigned int i=start;i<end;++i) {
			if( (*build_prims)[i]->getCentroid()->v[split_dim] < split_coord ) {
				std::swap( (*build_prims)[i], (*build_prims)[mid] );
				++mid;
			}
		}
        
		// If we get a bad split, just choose the center...
		if(mid == start || mid == end) {
			mid = start + (end-start)/2;
		}
        
		// Push right child
		todo[stackptr].start = mid;
		todo[stackptr].end = end;
		todo[stackptr].parent = nNodes-1;
		stackptr++;
		
		// Push left child
		todo[stackptr].start = start;
		todo[stackptr].end = mid;
		todo[stackptr].parent = nNodes-1;
		stackptr++;
    }
    
	// Copy the temp node data to a flat array
	flatTree = new BVHFlatNode[nNodes];
	for(unsigned int n=0; n<nNodes; ++n) 
		flatTree[n] = buildnodes[n];
		*/
}