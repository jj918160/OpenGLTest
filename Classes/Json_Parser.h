//
//  Json_Parser.h
//  SQLtest
//
//  Created by mac on 15-8-19.
//
//

#ifndef __SQLtest__Json_Parser__
#define __SQLtest__Json_Parser__

#include <stdio.h>
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "Json/writer.h"
#include "Json/reader.h"
#include "Json/document.h"
#include "Json/stringbuffer.h"
USING_NS_CC;
class Json_Parser{
public:
   
    //读取json
    void read_Json();
    //读取json工具
    void read_Jasoitoos(const char*filepath);
    //志记json
    void read_print(rapidjson::Document &doc,const char*keyname);
    void read_print(rapidjson::Value &va_p,const char*keyname);
    void read_print_for_array(rapidjson::Value &va,int i);
    
    //根据文json件生成ValueMap
    ValueMap read_Jaso_to_map(const char*filepath);
    ValueMap read_to_map(rapidjson::Document &doc,const char*keyname);
    void read_to_map(cocos2d::ValueMap &temp,rapidjson::Value &va_p,const char*keyname);
    void read_to_map_for_array(cocos2d::ValueVector &temp,rapidjson::Value &va,int i);
    
    //将ValueMap写入一个一个Json文件
   
    void write_a_map(cocos2d::ValueMap &temp,const char*filepath);
    void write_a_map(cocos2d::ValueMap &temp,rapidjson::Value &v2,rapidjson::Document::AllocatorType&all);
    void write_a_array(cocos2d::ValueVector &temp,rapidjson::Value &va,rapidjson::Document::AllocatorType&all);


};
#endif /* defined(__SQLtest__Json_Parser__) */
