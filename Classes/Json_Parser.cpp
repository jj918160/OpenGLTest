//
//  Json_Parser.cpp
//  SQLtest
//
//  Created by mac on 15-8-19.
//
//

#include "Json_Parser.h"
USING_NS_CC;
void Json_Parser::read_Json(){
    rapidjson::Document doc;
    //std::string filepath=FileUtils::getInstance()->fullPathForFilename("test.json");
    // __String*str=__String::createWithContentsOfFile(filepath.c_str());
    std::string filepath="/Users/mac/Desktop/beifenwork/zuoye.json";
    
    __String*str=__String::createWithContentsOfFile(filepath.c_str());
    
   
    
    
    doc.Parse<rapidjson::kParseDefaultFlags>(str->getCString());
    //CCASSERT(!doc.HasParseError(), "parsefile");
    if (doc.HasParseError()) {
        CCLOG("error:%u",doc.GetParseError());
        return ;
    }
   // CC_ASSERT(doc.IsObject()&&doc.HasMember("flag"));
//    ValueMap row;
//    const rapidjson::Value &record=doc["record"];
//    CC_ASSERT(record.HasMember("ID"));
//    const rapidjson::Value &id_1=record["ID"];
//    CC_ASSERT(id_1.IsString());
//    row["ID"]=Value(id_1.GetString());
    
    
    rapidjson::Value va;
    if (doc.HasMember("flag")) {
        va=doc["flag"];
        if (va.IsBool()) {
            const bool flag=va.GetBool();
            CCLOG("name:%d",flag);
        }
    }
    
}
//打印系列
void Json_Parser::read_Jasoitoos(const char*filepath){
    //创建文件
    rapidjson::Document doc;
    //提取字符串
    __String*str=__String::createWithContentsOfFile(filepath);
    //解析字符串（一级）
    doc.Parse<rapidjson::kParseDefaultFlags>(str->getCString());
    if (doc.HasParseError()) {
        CCLOG("error:%u",doc.GetParseError());
        return ;
    }
    
    CCASSERT(doc.IsObject(),"json is error");
    auto it=doc.MemberBegin();
    for (;it!=doc.MemberEnd();it++) {
        read_print(doc,it->name.GetString());
    }
    
}
void Json_Parser::read_print(rapidjson::Document &doc,const char*keyname){
    rapidjson::Value va;
    if (doc.HasMember(keyname)) {
        va=doc[keyname];
        std::string name(keyname);
        if (va.IsBool()) {
            const bool flag=va.GetBool();
            name+=":%d";
            CCLOG(name.c_str(),flag);
        }
        else if (va.IsDouble()) {
            const double flag=va.GetDouble();
            name+=":%f";
            CCLOG(name.c_str(),flag);
        }
        else if (va.IsInt()) {
            const int flag=va.GetInt();
            name+=":%d";
            CCLOG(name.c_str(),flag);
        }
        else if (va.IsString()) {
            const std::string flag=va.GetString();
            name+=":%s";
            CCLOG(name.c_str(),flag.c_str());
        }
        else if (va.IsNull()) {
            name+=":Null";
            CCLOG(name.c_str());
        }
        else if(va.IsObject())
        {
            CCLOG("obj--------%s",keyname);
            
            auto it=va.MemberBegin();
            for (;it!=va.MemberEnd();it++) {
                if (va.HasMember(it->name)) {
                    read_print(va,it->name.GetString());
                    
                }
            }
            
        }
        else if(va.IsArray())
        {
            CCLOG("array--------%s",keyname);
            for (int i=0; i<va.Size();i++) {
                read_print_for_array(va[i],i);
            }
            
        }
        
    }
    
}
void Json_Parser::read_print(rapidjson::Value &va_p,const char*keyname){
    rapidjson::Value va;
    if (va_p.HasMember(keyname)) {
        va=va_p[keyname];
        std::string name(keyname);
        if (va.IsBool()) {
            const bool flag=va.GetBool();
            name+=":%d";
            CCLOG(name.c_str(),flag);
        }
        else if (va.IsDouble()) {
            const double flag=va.GetDouble();
            name+=":%f";
            CCLOG(name.c_str(),flag);
        }
        else if (va.IsInt()) {
            const int flag=va.GetInt();
            name+=":%d";
            CCLOG(name.c_str(),flag);
        }
        else if (va.IsString()) {
            const std::string flag=va.GetString();
            name+=":%s";
            CCLOG(name.c_str(),flag.c_str());
        }
        else if (va.IsNull()) {
            name+=":Null";
            CCLOG(name.c_str());
        }
        else if(va.IsObject())
        {
            
            CCLOG("obj--------%s",keyname);
            auto it=va.MemberBegin();
            for (;it!=va.MemberEnd();it++) {
                if (va.HasMember(it->name)) {
                    read_print(va,it->name.GetString());
                    
                }
            }
            
        }
        else if(va.IsArray())
        {
            
            CCLOG("array-------%s",keyname);
            for (int i=0; i<va.Size();i++) {
                
                read_print_for_array(va[i],i);
                
                
            }
        }
        
    }
}
void Json_Parser::read_print_for_array(rapidjson::Value &va,int i){
    
    if (va.IsBool()) {
        const bool flag=va.GetBool();
        
        CCLOG("%d:%d",i,flag);
    }
    else if (va.IsDouble()) {
        const double flag=va.GetDouble();
        CCLOG("%d:%f",i,flag);
    }
    else if (va.IsInt()) {
        const int flag=va.GetInt();
        CCLOG("%d:%d",i,flag);
    }
    else if (va.IsString()) {
        const std::string flag=va.GetString();
        CCLOG("%d:%s",i,flag.c_str());
    }
    else if (va.IsNull()) {
        
        CCLOG("%d:null",i);
    }
    else if(va.IsObject())
    {
        CCLOG("obj----------%d",i);
        auto it=va.MemberBegin();
        for (;it!=va.MemberEnd();it++) {
            if (va.HasMember(it->name)) {
                read_print(va,it->name.GetString());
                
            }
        }
        
    }
    else if(va.IsArray())
    {
        CCLOG("array-------%d",i);
        for (int i=0; i<va.Size();i++) {
            
            read_print_for_array(va[i],i);
            
            
        }
        
    }
    
}



//将Json写入一个map 读入map系列
ValueMap Json_Parser::read_Jaso_to_map(const char*filepath){
    ValueMap temp;
    //创建文件
    rapidjson::Document doc;
    //提取字符串
    
    __String*str=__String::createWithContentsOfFile(filepath);
    //解析字符串（一级）
    CCLOG("str:%s",str->getCString());
    doc.Parse<rapidjson::kParseDefaultFlags>(str->getCString());
   
    if (doc.HasParseError()) {
        CCLOG("error:%u",doc.GetParseError());
        return temp;
    }
   
    CCASSERT(doc.IsObject(),"json is error");
    auto it=doc.MemberBegin();
    for (;it!=doc.MemberEnd();it++) {
        CCLOG("obj:?%s",it->name.GetString());
        temp=read_to_map(doc,it->name.GetString());
    }
    return temp;
}
ValueMap Json_Parser::read_to_map(rapidjson::Document &doc,const char*keyname){
    rapidjson::Value va;
    ValueMap jmap;
    if (doc.HasMember(keyname)) {
        va=doc[keyname];
        
        if (va.IsBool()) {
            const bool flag=va.GetBool();
            jmap[keyname]=flag;
        }
        else if (va.IsDouble()) {
            const double flag=va.GetDouble();
           jmap[keyname]=flag;
        }
        else if (va.IsInt()) {
            const int flag=va.GetInt();
           jmap[keyname]=flag;
        }
        else if (va.IsString())
        {
            const std::string flag=va.GetString();
            jmap[keyname]=Value(flag);
        }
        else if (va.IsNull()) {
            jmap[keyname]=nullptr;
        }
        else if(va.IsObject())
        {
           
            cocos2d::ValueMap temp;
            auto it=va.MemberBegin();
            for (;it!=va.MemberEnd();it++) {
                if (va.HasMember(it->name)) {
                    read_to_map(temp,va,it->name.GetString());
                }
            }
            jmap[keyname]=Value(temp);
           // CCLOG("map1层:%lu",temp.size());
        }
        else if(va.IsArray())
        {
            
            cocos2d::ValueVector temp;
            for (int i=0; i<va.Size();i++) {
                read_to_map_for_array(temp,va[i],i);
            }
            
            CCLOG("==%s,size:%lu",keyname,temp.size());
             // CCLOG("ttt:%lu",ttt.size());
            CCLOG("jma:%lu",jmap.size());
            jmap[keyname]=Value(temp);
            //ttt[keyname]=Value(temp);
            CCLOG("==");
          //   CCLOG("vector1层:%lu",temp.size());
        }
       
    }
    
    return jmap;
}
void Json_Parser::read_to_map(cocos2d::ValueMap &temp,rapidjson::Value &va_p,const char*keyname){
     CCLOG("%s",keyname);
    rapidjson::Value va;
    if (va_p.HasMember(keyname)) {
        va=va_p[keyname];
       
        if (va.IsBool()) {
            const bool flag=va.GetBool();
             temp[keyname]=flag;
        }
        else if (va.IsDouble()) {
            const double flag=va.GetDouble();
            temp[keyname]=flag;
        }
        else if (va.IsInt()) {
            const int flag=va.GetInt();
            temp[keyname]=flag;
        }
        else if (va.IsString()) {
            const std::string flag=va.GetString();
            temp[keyname]=Value(flag);
        }
        else if (va.IsNull()) {
            
            temp[keyname]=nullptr;
        }
        else if(va.IsObject())
        {
        
            cocos2d::ValueMap temp2;
            auto it=va.MemberBegin();
            for (;it!=va.MemberEnd();it++) {
                if (va.HasMember(it->name)) {
                    read_to_map(temp2,va,it->name.GetString());
                }
            }
            temp[keyname]=Value(temp2);
           //  CCLOG("map2层:%lu",temp.size());
            
        }
        else if(va.IsArray())
        {
            cocos2d::ValueVector temp2;
            for (int i=0; i<va.Size();i++) {
                read_to_map_for_array(temp2,va[i],i);
            }
           
            temp[keyname]=Value(temp2);
           
          //   CCLOG("vector2层:%lu",temp2.size());
        }
        
    }
}
void Json_Parser::read_to_map_for_array(cocos2d::ValueVector &temp,rapidjson::Value &va,int i){
     CCLOG("dex:%d",i);
    if (va.IsBool()) {
        const bool flag=va.GetBool();
          temp.push_back(Value(flag));
    }
    else if (va.IsDouble()) {
        const double flag=va.GetDouble();
         temp.push_back(Value(flag));
    }
    else if (va.IsInt()) {
        const int flag=va.GetInt();
          temp.push_back(Value(flag));
    }
    else if (va.IsString()) {
        const std::string flag=va.GetString();
        temp.push_back(Value(flag));
       // CCLOG("++:%d",temp.size());
    }
    else if (va.IsNull()) {
      
           temp.push_back(Value(nullptr));
        
    }
    else if(va.IsObject())
    {
        cocos2d::ValueMap temp2;
        auto it=va.MemberBegin();
        for (;it!=va.MemberEnd();it++) {
            if (va.HasMember(it->name)) {
                read_to_map(temp2,va,it->name.GetString());
            }
        }
           temp.push_back(Value(temp2));
        // CCLOG("mapinvectro层:%lu",temp2.size());
    }
    else if(va.IsArray())
    {
        cocos2d::ValueVector temp2;
        for (int i=0; i<va.Size();i++) {
            read_to_map_for_array(temp2,va[i],i);
        }
         temp.push_back(Value(temp2));
        // CCLOG("vectorinvectro层:%lu",temp.size());
    }
    
}

//写入文件系列
//将ValueMap写入一个一个Json文件
void Json_Parser::write_a_map(cocos2d::ValueMap &map_temp,const char*filepath){
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType&allocator=doc.GetAllocator();
    
    rapidjson::Value object(rapidjson::kObjectType);
    rapidjson::Value array(rapidjson::kArrayType);
    
    auto it=map_temp.begin();
    for (;it!=map_temp.end();it++) {
        rapidjson::Value v;
        rapidjson::Value v2;
        v.SetString(it->first.c_str(),allocator);
        
        if(it->second.getType()==Value::Type::DOUBLE){
        v2.SetDouble(it->second.asDouble());
        object.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::STRING){
            v2.SetString(it->second.asString().c_str(),allocator);
            object.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::BOOLEAN){
            v2.SetBool(it->second.asBool());
            object.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::INTEGER){
            v2.SetInt(it->second.asInt());
            object.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::NONE){
            v2.SetNull();
            object.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::MAP){
            ValueMap chmap=it->second.asValueMap();
            v2.SetObject();
                write_a_map(chmap,v2,allocator);

            object.AddMember(v,v2,allocator);
                    }
        else if(it->second.getType()==Value::Type::VECTOR){
            ValueVector chvec=it->second.asValueVector();
            v2.SetArray();
                write_a_array(chvec, v2, allocator);
            object.AddMember(v,v2,allocator);
        }

    }
    array.PushBack(object,allocator);
    
    
   
   
    doc.AddMember("record",array,allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson:: Writer<rapidjson::StringBuffer> writer(buffer);
    
    doc.Accept(writer);
    auto out=buffer.GetString();
    log("out:%s",out);
    FILE*file=fopen(filepath, "wb");
    if (file) {
        fputs(buffer.GetString(),file);
        fclose(file);
    }
  
    
}
void Json_Parser::write_a_map(cocos2d::ValueMap &temp,rapidjson::Value &val2,rapidjson::Document::AllocatorType&allocator){
    
    rapidjson::Value object2(rapidjson::kObjectType);
    
    auto it=temp.begin();
    for (;it!=temp.end();it++) {
        rapidjson::Value v;
        rapidjson::Value v2;
        v.SetString(it->first.c_str(),allocator);
        
        if(it->second.getType()==Value::Type::DOUBLE){
            v2.SetDouble(it->second.asDouble());
            val2.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::STRING){
            v2.SetString(it->second.asString().c_str(),allocator);
            val2.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::BOOLEAN){
            v2.SetBool(it->second.asBool());
            val2.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::INTEGER){
            v2.SetInt(it->second.asInt());
            val2.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::NONE){
            v2.SetNull();
            val2.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::MAP){
            ValueMap chmap=it->second.asValueMap();
            v2.SetObject();
                write_a_map(chmap,v2,allocator);
            val2.AddMember(v,v2,allocator);
        }
        else if(it->second.getType()==Value::Type::VECTOR){
            
            ValueVector chvec=it->second.asValueVector();
            v2.SetArray();
                write_a_array(chvec, v2, allocator);
            val2.AddMember(v,v2,allocator);

        }
    }
    
}
void Json_Parser::write_a_array(cocos2d::ValueVector &temp,rapidjson::Value &val2,rapidjson::Document::AllocatorType&allocator){
     rapidjson::Value array2(rapidjson::kArrayType);
    for (int i=0; i<temp.size(); i++) {
        rapidjson::Value v;
        if(temp.at(i).getType()==Value::Type::DOUBLE){
            v.SetDouble(temp.at(i).asDouble());
            val2.PushBack(v,allocator);
        }
        else if(temp.at(i).getType()==Value::Type::STRING){
            v.SetString(temp.at(i).asString().c_str(),allocator);
            val2.PushBack(v,allocator);
        }
        else if(temp.at(i).getType()==Value::Type::BOOLEAN){
            v.SetBool(temp.at(i).asBool());
            val2.PushBack(v,allocator);
        }
        else if(temp.at(i).getType()==Value::Type::INTEGER){
            v.SetInt(temp.at(i).asInt());
           val2.PushBack(v,allocator);
        }
        else if(temp.at(i).getType()==Value::Type::NONE){
            v.SetNull();
           val2.PushBack(v,allocator);
        }
        else if(temp.at(i).getType()==Value::Type::MAP){
            ValueMap chmap=temp.at(i).asValueMap();
            v.SetObject();
                write_a_map(chmap,v,allocator);
             val2.PushBack(v,allocator);
        }
        else if(temp.at(i).getType()==Value::Type::VECTOR){
            
            ValueVector chvec=temp.at(i).asValueVector();
            v.SetArray();
                write_a_array(chvec, v, allocator);
            val2.PushBack(v, allocator);
        }

    }
    
}
