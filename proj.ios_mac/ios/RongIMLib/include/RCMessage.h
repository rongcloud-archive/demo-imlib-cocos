//
//  RCMessage.hpp
//  RongIMLib
//
//  Created by litao on 15/11/12.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef Message_hpp
#define Message_hpp

#include <sys/types.h>
#include <string>
#include <vector>
#include "RCMessageContent.h"
#include "RCCommon.h"
#include "RCConversation.h"
#include <list>
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
#include "SerializableObject.h"
#endif
using namespace std;

namespace RongIM {
    class Conversation;
    class Message
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
    : public SerializableObject
#endif
    {
    public:
        Conversation m_conversation;
        MessageDirection m_direction;
        string m_senderUserId;
        MessageStatus m_status;
        long long m_sentTime;
        MessageContent *m_content;
        long m_messageId;
        Message(const Message &C);
        Message();
        Message(const Conversation &conversation, MessageDirection direction, MessageContent *content);
        virtual ~Message();
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
    };
}

#endif /* Message_hpp */
