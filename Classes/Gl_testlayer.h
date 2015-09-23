//
//  Gl_testlayer.h
//  OpenGLTest
//
//  Created by mac on 15-9-18.
//
//

#ifndef __OpenGLTest__Gl_testlayer__
#define __OpenGLTest__Gl_testlayer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Gl_testlayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(Gl_testlayer);
    
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
    virtual void onDraw();
    //void set_rect(Rect temprect);
    
     CustomCommand _command;
     Rect rect;
    
    GLuint vao;
    GLuint vertexVBO;
    GLuint colorVBO;
  
};

#endif /* defined(__OpenGLTest__Gl_testlayer__) */
