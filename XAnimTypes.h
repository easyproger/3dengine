//
//  XAnimTypes.h
//  
//
//  Created by easy proger on 01.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _XAnimTypes_h
#define _XAnimTypes_h


#include "XMathTypes.h"


typedef struct{
	XMatrix4 mat;
}AnimationFrame;

typedef struct{
    XVector3 *pos;
    XVector4 *rot;
    int *parentID;
    XMatrix4*mat;
	void remove(){
		free(pos);
    	free(rot);
    	free(parentID);
		free(mat);
	}
}SkinningFrame;


#endif
