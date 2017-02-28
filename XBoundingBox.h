//
//  XboundingBox.h
//  XTech
//
//  Created by easy proger on 26.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __XboundingBox__
#define __XboundingBox__

#include <iostream>

#include "XTypes.h"
#include "XVector4Math.h"
#include "XVector3Math.h"
#include "XMatrix4Math.h"

class XBoundingBox
{
public:
    XVector3 minPt;
    XVector3 maxPt;
    XVector3 extent;
    
    XBoundingBox();
    
    XBoundingBox( const XBoundingBox& other ): minPt(other.minPt), maxPt(other.maxPt) { }
    
    void merge(const XVector3* vec);
    void merge(const XBoundingBox* bbox);
    
    bool intersect(float* hitDist, const XVector3* origPt, const XVector3* dir);
    
    XVector3 point(int i) const {
		XVector3 ret = XVector3Make((i&1)?minPt.x:maxPt.x, (i&2)?minPt.y:maxPt.y, (i&4)?minPt.z:maxPt.z);
		return ret;
	}
    
    
    
    void setVector(XVector3*p);
    void expandToInclude(const XVector3* p);
    void expandToInclude(const XBoundingBox* b);
    unsigned int maxDimension() const;
};


#endif /* defined(__XboundingBox__) */
