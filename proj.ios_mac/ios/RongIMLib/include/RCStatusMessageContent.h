//
//  RCStatusMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 16/1/25.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#ifndef RCStatusMessageContent_hpp
#define RCStatusMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCCommon.h"
#include "RCMessageContent.h"

using namespace std;

namespace RongIM {
    
    
    class StatusMessageContent : public MessageContent {
    public:
        virtual string encode() const;
        virtual void decode(const string &rawData);
        virtual const MessageContentFactory* getFactory() const {
            return StatusMessageContent::getStaticFactory();
        }
        MessageContent* copy() const;
        
        virtual ~StatusMessageContent(){};
        
        static MessageContent* createContent(const string &type, const string &content, const string &extra = "") {
            return new StatusMessageContent(type, content, extra);
        }
        static const MessageContentFactory *getStaticFactory();
        
        StatusMessageContent(const string &type, const string &content, const string &extra) : MessageContent(extra), m_content(content), m_type(type) {
        }
        
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
        string m_type;
        string m_content;
    };
}
#endif /* RCStatusMessageContent_hpp */
