//
//  XDebugLoger.h
//  XTech
//
//  Created by easy proger on 14.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __XDebugLoger__
#define __XDebugLoger__

#include "XSingleton.h"
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include "TGAImage.h"


using namespace std;
using namespace Xengine;
class XDebugLoger: public XSingleton<XDebugLoger> {
public:
    XDebugLoger();
    ~XDebugLoger(){};
    void init();
private:
    bool initialized;
};



#endif /* defined(__XDebugLoger__) */
