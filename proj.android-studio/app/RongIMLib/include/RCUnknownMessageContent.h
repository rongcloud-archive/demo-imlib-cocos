//
//  RCUnknownMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/12.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef UnknownMessageContent_hpp
#define UnknownMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCMessageContent.h"

using namespace std;

namespace RongIM {
    
    class UnknownMessageContent : public MessageContent {
    public:
        virtual string encode() const;
        virtual void decode(const string &rawData);
        virtual MessageContentFactory* getFactory() const {
            return NULL;
        }
        virtual const string getObjectName() const { return m_objName; }
        MessageContent* copy() const;
        
        virtual ~UnknownMessageContent() {
            
        }
        static UnknownMessageContent* createMessageContent(const string &objName, const string &rawData) {
            return new UnknownMessageContent(objName, rawData);
        }

        UnknownMessageContent(const string &objName, const string &rawData) : MessageContent(""), m_objName(objName) {
            m_rawJSONString = rawData;
        }
        
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
        
        string m_objName;
        string m_rawJSONString;
    };
}
#endif /* UnknownMessageContent_hpp */
