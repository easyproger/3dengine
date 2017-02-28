//
//  XMathBase.cpp
//  
//
//  Created by easy proger on 02.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "XMathBase.h"
using namespace std;




const char digit_pairs[201] = {
    "00010203040506070809"
    "10111213141516171819"
    "20212223242526272829"
    "30313233343536373839"
    "40414243444546474849"
    "50515253545556575859"
    "60616263646566676869"
    "70717273747576777879"
    "80818283848586878889"
    "90919293949596979899"
};

void itostr(int n, char* c) {
    int sign = -(n<0);
    unsigned int val = (n^sign)-sign;
    
    int size;
    if(val>=10000) {
        if(val>=10000000) {
            if(val>=1000000000) {
                size=10;
            }
            else if(val>=100000000) {
                size=9;
            }
            else size=8;
        }
        else {
            if(val>=1000000) {
                size=7;
            }
            else if(val>=100000) {
                size=6;
            }
            else size=5;
        }
    }
    else {
        if(val>=100) {
            if(val>=1000) {
                size=4;
            }
            else size=3;
        }
        else {
            if(val>=10) {
                size=2;
            }
            else if(n==0) {
                c[0]='0';
                c[1] = '\0';
                return;
            }
            else size=1;
        }
    }
    size -= sign;
    if(sign)
        *c='-';
    
    c += size-1;
    while(val>=100) {
        int pos = val % 100;
        val /= 100;
        *(short*)(c-1)=*(short*)(digit_pairs+2*pos);
        c-=2;
    }
    while(val>0) {
        *c--='0' + (val % 10);
        val /= 10;
    }
    c[size+1] = '\0';
}

void itostr(unsigned val, char* c)
{
    int size;
    if(val>=10000)
    {
        if(val>=10000000)
        {
            if(val>=1000000000)
                size=10;
            else if(val>=100000000)
                size=9;
            else
                size=8;
        }
        else
        {
            if(val>=1000000)
                size=7;
            else if(val>=100000)
                size=6;
            else
                size=5;
        }
    }
    else
    {
        if(val>=100)
        {
            if(val>=1000)
                size=4;
            else
                size=3;
        }
        else
        {
            if(val>=10)
                size=2;
            else if (val==0) {
                c[0]='0';
                c[1] = '\0';
                return;
            }
            else
                size=1;
        }
    }
    
    c += size-1;
    while(val>=100)
    {
        int pos = val % 100;
        val /= 100;
        *(short*)(c-1)=*(short*)(digit_pairs+2*pos);
        c-=2;
    }
    while(val>0)
    {
        *c--='0' + (val % 10);
        val /= 10;
    }
    c[size+1] = '\0';
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

