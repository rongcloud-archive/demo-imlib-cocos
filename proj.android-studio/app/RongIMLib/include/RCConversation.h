//
//  Conversation.hpp
//  RongIMLib
//
//  Created by lt on 15/11/12.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef RCConversation_hpp
#define RCConversation_hpp

#include <sys/types.h>
#include <string>
#include <vector>
#include "RCCommon.h"
#include <list>
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
#include "SerializableObject.h"
#endif

namespace RongIM {
    class Conversation
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
    : public SerializableObject
#endif
    {
    public:
        Conversation() {}
        Conversation(ConversationType conversationType, const std::string &targetId) : m_conversationType(conversationType), m_targetId(targetId) {}
        Conversation(const Conversation& C) { m_conversationType = C.m_conversationType; m_targetId = C.m_targetId; }
        
        ConversationType m_conversationType;
        std::string m_targetId;
        virtual ~Conversation() {}
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
    };
}
#endif /* RCConversation_hpp */
