//
//  Renderer.h
//  XTech
//
//  Created by easy proger on 07.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __Renderer__
#define __Renderer__

#include <iostream>

#include "SceneGraph.h"
#include "XObject.h"
#include "XRenderTypes.h"




class Renderer:public XObject {
public:
    Renderer(Camera*camera);
    ~Renderer();
    
    void render();
    
    void setDefaultSceneGraph(SceneGraph* sceneGraph);
    void setDefaultBuffer(uint bufferID);
    
    void changeShadowRender(int type);
    
    void (Renderer::*action[MAX_RENDERER][MAX_TEHNICS])(XQuery* query);
private:
    FrameBuffer* depthFrameBuffer;
    ShaderParamsSetter* shaderParamsSetter;
    SceneGraph *defaultSceneGraph;
    uint mDefaultFrameBuffer; // default frame
    int viewport[4];
    
    
    void renderBackBufferFR(XQuery* query);
    void renderToShadowMap(XQuery* query);
    void nop(XQuery* query);
};

#endif 
