//
//  XboundingBox.cpp
//  XTech
//
//  Created by easy proger on 26.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "XBoundingBox.h"
using namespace std;

// XTODO : all class not tested yet
// need calculate in maxscript minPT and maxPT from model with skeletal animation !



XBoundingBox::XBoundingBox()
	{ 
		minPt.x = 1e33f;
		minPt.y = 1e33f;
		minPt.z = 1e33f;

		maxPt.x = -1e33f;
		maxPt.y = -1e33f;
		maxPt.z = -1e33f;
	};



void XBoundingBox::merge(const XVector3* vec)
{
    minPt.x = min(minPt.x, vec->x);
    minPt.y = min(minPt.y, vec->y);
    minPt.z = min(minPt.z, vec->z);
    
    maxPt.x = max(maxPt.x, vec->x);
    maxPt.y = max(maxPt.y, vec->y);
    maxPt.z = max(maxPt.z, vec->z);
}

void XBoundingBox::merge(const XBoundingBox* bbox)
{
    minPt.x = min(minPt.x, bbox->minPt.x);
    minPt.y = min(minPt.y, bbox->minPt.y);
    minPt.z = min(minPt.z, bbox->minPt.z);
    
    maxPt.x = max(maxPt.x, bbox->maxPt.x);
    maxPt.y = max(maxPt.y, bbox->maxPt.y);
    maxPt.z = max(maxPt.z, bbox->maxPt.z);
}

bool XBoundingBox::intersect(float* hitDist, const XVector3* origPt, const XVector3* dir)
{
    XVector4 sides[6];

	XVector4Make(&sides[0],1, 0, 0,-minPt.x);
	XVector4Make(&sides[1],-1, 0, 0, maxPt.x);
	XVector4Make(&sides[2],0, 1, 0,-minPt.y);
	XVector4Make(&sides[3], 0,-1, 0, maxPt.y);
	XVector4Make(&sides[4],0, 0, 1,-minPt.z);
	XVector4Make(&sides[5],0, 0,-1, maxPt.z);



    *hitDist = 0.f;  // safe initial value
    XVector3 hitPt = *origPt;
    
    bool inside = false;
    
    for ( int i=0; (i < 6) && !inside; i++ )
    {
        float cosTheta = XVector4Dot(&sides[i], dir,0.0); // dot normal ( last * 0.0 )
        float dist     = XVector4Dot(&sides[i], origPt,1.0); // dot coords ( last * 1.0 )
        
        //  if we're nearly intersecting, just punt and call it an intersection
        if ( ALMOST_ZERO(dist) ) return true;
        //  skip nearly (&actually) parallel rays
        if ( ALMOST_ZERO(cosTheta) ) continue;
        //  only interested in intersections along the ray, not before it.
        *hitDist = -dist / cosTheta;
        if ( *hitDist < 0.f ) continue;
        
        
        XVector3MultiplyScalar(&hitPt,dir,*hitDist);
        XVector3Add(&hitPt, origPt);
        
        inside = true;
        
        for ( int j=0; (j<6) && inside; j++ )
        {
            if ( j==i )
                continue;
            float d = XVector4Dot( &sides[j], &hitPt,1.0 );  // dot normal ( last * 0.0 )
            
            inside = ((d + 0.00015) >= 0.f);
        }
    }
    
    return inside;
}


void XBoundingBox::expandToInclude(const XVector3* p) {
    merge(p);
    XVector3Subtract(&extent, &maxPt, &minPt);
}

void XBoundingBox::expandToInclude(const XBoundingBox* b) {
    merge(b);
    XVector3Subtract(&extent, &maxPt, &minPt);
}

unsigned int XBoundingBox::maxDimension() const {
    unsigned int result = 0;
    if(extent.y > extent.x) result = 1;
    if(extent.z > extent.y) result = 2;
    return result;
}


void XBoundingBox::setVector(XVector3*p){

    
	minPt.x = p->x;
	minPt.y = p->y;
	minPt.z = p->z;
	maxPt.x = p->x;
	maxPt.y = p->y;
	maxPt.z = p->z;

    XVector3Subtract(&extent, &maxPt, &minPt);
}

//  Transform an axis-aligned bounding box by the specified matrix, and compute a new axis-aligned bounding box
void XFormBoundingBox( XBoundingBox* result, const XBoundingBox* src, const XMatrix4* matrix )
{
    XVector3  pts[8];
    for ( int i=0; i<8; i++ )
        pts[i] = src->point(i);
    
	result->minPt.x = 3.3e33f;
	result->minPt.y = 3.3e33f;
	result->minPt.z = 3.3e33f;



	result->maxPt.x = -3.3e33f;
	result->maxPt.y = -3.3e33f;
	result->maxPt.z = -3.3e33f;

    XVector3 tmp;
    
    for (int i=0; i<8; i++)
    {
        //XMatrix4MultiplyAndProjectVector3(&tmp, matrix, &pts[i]);
        result->merge(&tmp);
    }
}






