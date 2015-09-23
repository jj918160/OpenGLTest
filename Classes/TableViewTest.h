//
//  TableViewTest.h
//  OpenGLTest
//
//  Created by mac on 15-9-6.
//
//

#ifndef __OpenGLTest__TableViewTest__
#define __OpenGLTest__TableViewTest__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
using namespace cocos2d;
class Json_Parser;
class TableViewtest:public Layer,public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:

    CREATE_FUNC(TableViewtest);
    virtual bool init();
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    void initdisandprice();
    std::vector<std::string>price;
    std::vector<std::string>discription;
   // void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    Json_Parser*jp;
};

#endif /* defined(__OpenGLTest__TableViewTest__) */
