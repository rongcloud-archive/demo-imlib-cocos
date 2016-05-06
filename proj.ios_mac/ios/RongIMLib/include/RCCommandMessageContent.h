//
//  RCCommandMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/30.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef RCCommandMessageContent_hpp
#define RCCommandMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCCommon.h"
#include "RCMessageContent.h"

using namespace std;

namespace RongIM {
    
    
    class CommandMessageContent : public MessageContent {
    public:
        virtual string encode() const;
        virtual void decode(const string &rawData);
        virtual const MessageContentFactory* getFactory() const {
            return CommandMessageContent::getStaticFactory();
        }
        MessageContent* copy() const;
        
        static MessageContent* createContent(string type, const string &content, const string &extra = "") {
            return new CommandMessageContent(type, content, extra);
        }
        
        static const MessageContentFactory *getStaticFactory();
        virtual ~CommandMessageContent(){};
 
        
        string getContent() const { return m_content; }
        CommandMessageContent(string type, const string &content, const string &extra) : MessageContent(extra), m_type(type), m_content(content) {
        }
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
        string m_type;
        string m_content;
    };
}


#endif /* RCCommandMessageContent_hpp */
