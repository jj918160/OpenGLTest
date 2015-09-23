//
//  TableViewTest.cpp
//  OpenGLTest
//
//  Created by mac on 15-9-6.
//
//

#include "TableViewTest.h"
#include "extensions/cocos-ext.h"
#include "Json_Parser.h"

USING_NS_CC_EXT;
bool TableViewtest::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
//    TableView* tableView = TableView::create(this, Size(250, 60));
//    
//    tableView->setDirection(ScrollView::Direction::HORIZONTAL);
//    tableView->setPosition(Vec2(20,winSize.height/2-30));
//    tableView->setDelegate(this);
//    this->addChild(tableView);
//    tableView->reloadData();

    initdisandprice();
   
    
    TableView*tableView = TableView::create(this, Size(600, 400));
    tableView->setDirection(ScrollView::Direction::VERTICAL);
    tableView->setPosition(Vec2(winSize.width/2-400,winSize.height/2-200));
    tableView->setDelegate(this);
    tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    this->addChild(tableView);
    tableView->reloadData();
    
    return true;
}
void TableViewtest::initdisandprice(){
    ValueMap map=jp->read_Jaso_to_map("zuoye1.json");
    for (int i=0; i<10; i++) {
    std::string p=map.at("obj").asValueVector().at(i).asValueMap().at("price").asString();
    price.push_back(p);
        
         std::string d=map.at("obj").asValueVector().at(i).asValueMap().at("skill").asString();
        discription.push_back(d);
    }
   }
void TableViewtest::tableCellTouched(TableView* table, TableViewCell* cell)
{
    std::string str1=price.at(cell->getIdx());
    std::string str2=discription.at(cell->getIdx());
    CCLOG("cell touched at index: %ld,价格:%s,描述:%s", cell->getIdx(),str1.c_str(),str2.c_str());
}

Size TableViewtest::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return Size(60,100);
}

TableViewCell* TableViewtest::tableCellAtIndex(TableView *table, ssize_t idx)
{
    auto string = String::createWithFormat("%ld", 2*idx);
    auto str2=String::create(price.at(2*idx));
    auto str3=discription.at(2*idx);
    auto str4 = String::createWithFormat("%ld", (2*idx+1));
    auto str5=String::create(price.at(2*idx+1));
    auto str6=discription.at(2*idx+1);
    
    TableViewCell *cell = table->dequeueCell();
  
    if (!cell) {
               cell = new (std::nothrow) TableViewCell();
        cell->autorelease();
        auto sprite = Sprite::create("addatk.png");
        sprite->setAnchorPoint(Vec2::ZERO);
        sprite->setPosition(Vec2(0, 0));
        cell->addChild(sprite);
        
        auto label = Label::createWithSystemFont(string->getCString(), "Helvetica", 20.0);
        label->setPosition(Vec2::ZERO);
        label->setAnchorPoint(Vec2::ZERO);
        label->setTag(123);
        cell->addChild(label);
        
        
        auto label2 = Label::createWithSystemFont(str2->getCString(), "Helvetica", 20.0);
        label2->setPosition(150,50);
        label2->setAnchorPoint(Vec2(0.5,0.5));
        label2->setTag(124);
        cell->addChild(label2);
//       
        auto label3 = Label::createWithSystemFont(str3.c_str(), "Helvetica", 20.0);
        label3->setPosition(250,50);
        label3->setAnchorPoint(Vec2(0.5,0.5));
        label3->setTag(125);
        cell->addChild(label3);
        
        auto sprite2 = Sprite::create("addhp.png");
        sprite2->setAnchorPoint(Vec2::ZERO);
        sprite2->setPosition(Vec2(300, 0));
        cell->addChild(sprite2);
        
        auto label4 = Label::createWithSystemFont(str4->getCString(), "Helvetica", 20.0);
        label4->setPosition(300,0);
        label4->setAnchorPoint(Vec2::ZERO);
        label4->setTag(126);
        cell->addChild(label4);
  
        auto label5 = Label::createWithSystemFont(str5->getCString(), "Helvetica", 20.0);
        label5->setPosition(450,50);
        label5->setAnchorPoint(Vec2(0.5,0.5));
        label5->setTag(127);
        cell->addChild(label5);
        //
        //
        auto label6 = Label::createWithSystemFont(str6.c_str(), "Helvetica", 20.0);
        label6->setPosition(550,50);
        label6->setAnchorPoint(Vec2(0.5,0.5));
        label6->setTag(128);
        cell->addChild(label6);
    }
    else
    {
        
        auto label = (Label*)cell->getChildByTag(123);
        label->setString(string->getCString());
        auto label2 = (Label*)cell->getChildByTag(124);
        label2->setString(str2->getCString());
        auto label3 = (Label*)cell->getChildByTag(125);
        label3->setString(str3.c_str());
        
        auto label4 = (Label*)cell->getChildByTag(126);
        label4->setString(str4->getCString());
        auto label5 = (Label*)cell->getChildByTag(127);
        label5->setString(str5->getCString());
        auto label6 = (Label*)cell->getChildByTag(128);
        label6->setString(str6.c_str());
    }
    return cell;
}



ssize_t TableViewtest::numberOfCellsInTableView(TableView *table)
{
    return 5;
}
