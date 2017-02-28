//
//  XMathBase.h
//  
//
//  Created by easy proger on 02.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef ____XMathBase__
#define ____XMathBase__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>


void itostr(int n, char* c);
void itostr(unsigned val, char* c);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

struct BoneInfo
{
    int boneID;
    int parentID;
    std::vector<BoneInfo*> childs;
};

typedef unsigned int uint;

#endif /* defined(____XMathBase__) */
