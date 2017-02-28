//
//  XRenderTypes.h
//  XTech
//
//  Created by easy proger on 14.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef XTech_XRenderTypes_h
#define XTech_XRenderTypes_h

#include "SceneNode.h"


#define SHOW_AR 1

typedef struct {

    // пока не юзается // далее нужно будет думать о инстанс батчинге
    // я думаю на устройствах которые не держат 3 версию ЕС нет смысла вообще выводить много геометрии соотв нету смысла в батчинге 
    
}XBatch;


typedef struct{
    SceneNode* *list;
    uint sizeAlloced;
    uint size;
    
    int renderID;
    int queryID;
}XQuery;



#endif
