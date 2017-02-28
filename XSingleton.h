//
//  Singleton.h
//  ShadowMapsTestProject
//
//  Created by easy on 25.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
#ifndef ___SINGLETON_H__
#define ___SINGLETON_H__



namespace Xengine
{
    
    template <typename T>
    class XSingleton
    {
        static T *instance;
        
    protected:
        XSingleton()
        {
        }
        ~XSingleton()
        {
        }
    public: 
        virtual void initialize()
        {
        } 
        
        static inline T *me()
        {
            if (instance == 0)
            {
                instance = new T();
                instance->initialize();
            }
            return instance;
        }
    };
    
    template <class T> T *Xengine::XSingleton<T>::instance = 0;
    
}
#endif // ___SINGLETON_H__