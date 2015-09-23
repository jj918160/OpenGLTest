//
//  Custom_shader_layer.cpp
//  OpenGLTest
//
//  Created by mac on 15-9-7.
//
//

#include "Custom_shader_layer.h"


bool Custom_shader_layer::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    rect=Rect(100,100,300,300);
    this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
    
    auto touchEvt=EventListenerTouchOneByOne::create();
    touchEvt->onTouchBegan=[&](Touch*ptouch,Event*pevet){
        Vec2 p=ptouch->getLocation();
        rect=Rect(p.x-150,p.y-150,300,300);
        return true;
    };
    
    //不可少，否则无效果
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt,this);
    return true;
}




void Custom_shader_layer::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{

    Layer::visit(renderer, parentTransform, parentFlags);

    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(Custom_shader_layer::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
}

void Custom_shader_layer::onDraw()
{
    //获得当前HelloWorld的shader
    auto glProgram = getGLProgram();
    //使用此shader
    glProgram->use();
    //设置该shader的一些内置uniform,主要是MVP，即model-view-project矩阵
    glProgram->setUniformsForBuiltins();
    
    auto size = Director::getInstance()->getWinSize();
    
    //指定将要绘制的三角形的三个顶点，分别位到屏幕左下角，右下角和正中间的顶端
    float vertercies[] = {
        0,0,
        size.width,0,
        rect.origin.x,rect.origin.y,
        rect.origin.x+rect.size.width,rect.origin.y,
        rect.origin.x,rect.origin.y+rect.size.height,
        rect.origin.x+rect.size.width,rect.origin.y+rect.size.height,
        0.0,size.height,
        size.width,size.height
    };
    //指定每一个顶点的颜色，颜色值是RGBA格式的，取值范围是0-1
    float color[] = {
        1,1,0,1,    //第一个点的颜色，绿色
        1,1,0,1,  //第二个点的颜色, 红色
        1,1,0,1,//第三个点的颜色， 蓝色
        1,1,0,1,
        1,1,0,1,
        1,1,0,1,
        1,1,0,1,
        1,1,0,1
    };
 //   float color2[] = {1,0,0,1};
    //float *p=(float*)malloc(24*8*sizeof(float));
    
    
    //激活名字为position和color的vertex attribute
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION );//| GL::VERTEX_ATTRIB_FLAG_COLOR);

    //分别给position和color指定数据源
    //数组结构
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
    
    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR,0,0,0,0.2);
    //glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
    
    //绘制三角形，所谓的draw call就是指这个函数调用
    GLuint _indices[]={
        0,1,2,2,1,3,3,1,5,5,1,7,7,5,6,4,5,6,6,4,0,4,2,0
    };
    
    glDrawElements(GL_TRIANGLES,24,GL_UNSIGNED_INT, _indices);

  
    
    //通知cocos2d-x 的renderer，让它在合适的时候调用这些OpenGL命令
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,24);
    //如果出错了，可以使用这个函数来获取出错信息
    CHECK_GL_ERROR_DEBUG();
  //  DrawPrimitives
}

void Custom_shader_layer::set_rect(Rect temprect){
    rect=temprect;
}

//glBindVertexArrayOES(<#GLuint array#>)
//glDrawArrays(GL_TRIANGLES, 0, 3);


//glGenBuffers (GLsizei n, GLuint* buffers);//分配缓冲对象，(缓冲对象的个数，缓冲对象的名字(数字))。
//glBindBuffer(<#GLenum target#>, <#GLuint buffer#>);//创建一个缓冲对象（类型(数组或者数组索引,可选值为以下两个)，尺寸(初始为0)）
    //ex:glBindBuffer(GL_ARRAY_BUFFER, 0);
    //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//glBufferData(<#GLenum target#>, <#GLsizeiptr size#>, <#const GLvoid *data#>, <#GLenum usage#>)//创建，初始化缓冲对象
//glBufferSubData(<#GLenum target#>, <#GLintptr offset#>, <#GLsizeiptr size#>, <#const GLvoid *data#>)//修改顶点缓冲对象的一部分数据


//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
 //void glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);//类型，索引顶点数量，数据类型，偏移数组
//glGenVertexArraysOES(<#GLsizei n#>, <#GLuint *arrays#>)：声明一个顶点数组对象被使用：分配n个顶点数组对象，每个顶点数组对象的名字分别存储在arrays数组中。
//glBindVertexArrayOES(<#GLuint array#>)//创建一个顶点数组对象