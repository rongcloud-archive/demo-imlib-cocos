//
//  RCTextMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/11.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef TextMessageContent_hpp
#define TextMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCCommon.h"
#include "RCMessageContent.h"

using namespace std;

namespace RongIM {

    
    class TextMessageContent : public MessageContent {
    public:
        virtual string encode() const;
        virtual void decode(const string &rawData);
        virtual const MessageContentFactory* getFactory() const {
            return TextMessageContent::getStaticFactory();
        }
        MessageContent* copy() const;
        
        virtual ~TextMessageContent(){};
        
        static MessageContent* createContent(const string &content, const string &extra = "") {
            return new TextMessageContent(content, extra);
        }
        static const MessageContentFactory *getStaticFactory();
        TextMessageContent(const string &content, const string &extra) : MessageContent(extra), m_content(content) {
        }

        string m_content;
    };
}
#endif /* TextMessageContent_hpp */
