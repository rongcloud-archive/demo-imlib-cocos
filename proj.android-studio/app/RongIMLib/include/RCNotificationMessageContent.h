//
//  RCNotificationMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/30.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef RCNotificationMessageContent_hpp
#define RCNotificationMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCCommon.h"
#include "RCMessageContent.h"

using namespace std;

namespace RongIM {
    
    
    class NotificationMessageContent : public MessageContent {
    public:
        virtual string encode() const;
        virtual void decode(const string &rawData);
        MessageContent* copy() const;
        virtual const MessageContentFactory* getFactory() const {
            return NotificationMessageContent::getStaticFactory();
        }
        
        static MessageContent* createContent(string type, const string &content, const string &extra = 0) {
            return new NotificationMessageContent(type, content, extra);
        }
        
        static const MessageContentFactory *getStaticFactory();
        virtual ~NotificationMessageContent(){};
        NotificationMessageContent(string type, const string &content, const string &extra) : MessageContent(extra), m_type(type), m_content(content) {
        }
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
        string m_type;
        string m_content;
    };
}

#endif /* RCNotificationMessageContent_hpp */
