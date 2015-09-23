//
//  Gl_testlayer.cpp
//  OpenGLTest
//
//  Created by mac on 15-9-18.
//
//

#include "Gl_testlayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


Scene* Gl_testlayer::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Gl_testlayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Gl_testlayer::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
//    auto rootNode = CSLoader::createNode("MainScene.csb");
//    addChild(rootNode);
    
 rect=Rect(100,100,300,300);
    
    //create my own program
    auto program = new GLProgram; //新建自己的程序
    program->initWithFilenames("myVertextShader.vert", "myFragmentShader.frag");//载入两个着色器
    program->link();             //链接
    //set uniform locations
    program->updateUniforms();   //更新规格
    this->setGLProgram(program);  //将自定义的着色程序用在这个类上面，用来着色
    //glGenVertexArraysOES(<#GLsizei n#>, <#GLuint *arrays#>)
    //创建和绑定vao
    glGenVertexArrays(1, &vao);//创建顶点数组
    glBindVertexArray(vao);   //绑定顶点数组
    auto size = Director::getInstance()->getVisibleSize();
//    float vertercies[] = { 0,0,   //第一个点的坐标
//        size.width, 0,   //第二个点的坐标
//        size.width / 2, size.height};  //第三个点的坐标
    
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

    
   // float color[] = { 0, 1,0, 1,  1,0,0, 1, 0, 0, 1, 1};

    
    
    //创建和绑定vbo
    glGenBuffers(2, &vertexVBO);//创建缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);//绑定缓冲区对象
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertercies), vertercies, GL_STATIC_DRAW);//将所有顶点属性数据存储在GL服务端缓冲对象中
    //获取vertex attribute "a_position"的入口点
    GLuint positionLocation = glGetAttribLocation(program->getProgram(), "a_position");//查询绑定结果
    //打开入a_position入口点
    glEnableVertexAttribArray(positionLocation);     //激活数组
    //传递顶点数据给a_position，注意最后一个参数是数组的偏移了。
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);//给顶点赋值
    
    //set for color 同上
//    glGenBuffers(1, &colorVBO);
//    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
   // glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);//创建和初始化缓冲对象。
    
   // GLuint colorLocation = glGetAttribLocation(program->getProgram(), "a_color");
   // glEnableVertexAttribArray(colorLocation);
    //glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glVertexAttrib4f(GLProgram::VERTEX_ATTRIB_COLOR,1,0,0,0.2);
   
    
 
   // VERTEX_ATTRIB_ARRAY_ENABLED
    //for safty
    glBindVertexArray(0);                 //绑定VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);     //绑定缓冲区对象
    //执行一个切回保留缓冲对象，相当于删除，为了后续安全
    
    
    
   
    
    
    
    return true;
}

void Gl_testlayer::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    
    Layer::visit(renderer, parentTransform, parentFlags);
    
    _command.init(_globalZOrder);
    _command.func = CC_CALLBACK_0(Gl_testlayer::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_command);
}

void Gl_testlayer::onDraw()
{
    
    
    //获得当前类的shader
    auto glProgram = getGLProgram();
    //使用此shader
    glProgram->use();
    //设置该shader的一些内置uniform,主要是MVP，即model-view-project矩阵
    glProgram->setUniformsForBuiltins();
    
    auto size = Director::getInstance()->getWinSize();
    
    //use vao，因为vao记录了每一个顶点属性和缓冲区的状态，所以只需要绑定就可以使用了
    glBindVertexArray(vao);

    GLuint _indices[]={
        0,1,2,2,1,3,3,1,5,5,1,7,7,5,6,4,5,6,6,4,0,4,2,0
    };
    
    glDrawElements(GL_TRIANGLES,24,GL_UNSIGNED_INT, _indices);

    
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 24);
    CHECK_GL_ERROR_DEBUG();
   }



