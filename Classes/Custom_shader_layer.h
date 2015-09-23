//
//  Custom_shader_layer.h
//  OpenGLTest
//
//  Created by mac on 15-9-7.
//
//

#ifndef __OpenGLTest__Custom_shader_layer__
#define __OpenGLTest__Custom_shader_layer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class Custom_shader_layer:public Layer{
public:
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(Custom_shader_layer);
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
    virtual void onDraw();
    void set_rect(Rect temprect);
private:
    CustomCommand _command;
    Rect rect;
    //GLProgramState
};
#endif /* defined(__OpenGLTest__Custom_shader_layer__) */


