//
//  XUDID.h
//
//  Created by easy proger on 27.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _XUDID_h
#define _XUDID_h

#include "XSingleton.h"
#include "stdio.h"
#include "stdlib.h"
#include <string>


using namespace std;
using namespace Xengine;

class XUDID: public XSingleton<XUDID> {
private:
    bool initialized;
    uint udid;
public:
    uint getUDID(){
        return udid++;
    };
    virtual void initialize() {
        udid = 0;
    }
    XUDID(){};
    ~XUDID(){};
};
#endif
