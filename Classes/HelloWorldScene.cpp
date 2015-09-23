#include "HelloWorldScene.h"
#include "TableViewTest.h"
#include "Custom_shader_layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
//USING_NS_CC;
//using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
   
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
   
    Custom_shader_layer*csl=Custom_shader_layer::create();
    this->addChild(csl);


    
    
    return true;
}



////创建和绑定顶点缓冲区对象(VBO);
//void InitVertexBufferObjects(float* vertexBuffer,GLushort* indices,GLuint numVertices,GLuint numIndices,GLuint* vboIds) {
//    glGenBuffers(2,vboIds);//申请两块缓冲区,一个用于保存实际顶点数据，一个用于保存组成图元的元素索引;
//    glBindBuffer(GL_ARRAY_BUFFER,vboIds[0]); //指定当前缓冲区对象;
//    glBufferData(GL_ARRAY_BUFFER,numVertices*sizeof(float),vertexBuffer,GL_STATIC_DRAW);//创建和初始化数据存储;
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vboIds[1]); glBufferData(GL_ELEMENT_ARRAY_BUFFER,numIndices*sizeof(float),indices,GL_STATIC_DRAW);
//}