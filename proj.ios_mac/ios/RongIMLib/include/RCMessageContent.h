//
//  RCMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/11.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef MessageContent_hpp
#define MessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCCommon.h"
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
#include "SerializableObject.h"
#endif

using namespace std;

namespace RongIM {
    extern const string rcTextMsgObjName;
    extern const string rcImageMsgObjName;
    extern const string rcLocMsgObjName;
    extern const string rcAudioMsgObjName;
    extern const string rcNotificationMsgObjName;
    extern const string rcCommandMsgObjName;
    extern const string rcFileMsgObjName;
    extern const string rcVedioMsgObjName;
    
    extern const string rcCustomMsgObjName;
    extern const string rcStatusMsgObjName;
    
    class MessageContent;
    class Message;
    class Conversation;
    class MessageContentFactory {
    public:
        virtual const string getObjectName() const = 0;
        virtual MessagePsersistent getPersistentFlag() const = 0;
        virtual MessageContent* createEmptyContent() const = 0;
    };
    
    class MessageContent
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
    : public SerializableObject
#endif
    {
    public:
        virtual string encode() const = 0;
        virtual void decode(const string &rawData) = 0;
        virtual const MessageContentFactory* getFactory() const = 0;
        virtual MessageContent* copy() const = 0;
        
        virtual const string getObjectName() const {
            return getFactory()->getObjectName();
        }
        
        MessageContent(const string &extra) : m_extra(extra){}
        virtual ~MessageContent(){};
        
        bool isText() const { return getObjectName() == rcTextMsgObjName; } 
        bool isImage() const { return getObjectName() == rcImageMsgObjName; }
        bool isLocation() const { return getObjectName() == rcLocMsgObjName; }
        bool isAudio() const { return getObjectName() == rcAudioMsgObjName; }
        bool isCommand() const { return getObjectName() == rcCommandMsgObjName; }
        bool isNotification() const { return getObjectName() == rcNotificationMsgObjName; }
        virtual bool isMedia() const { return false; }
        
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
        string m_extra;
    protected:

        friend class Message;
        friend class Conversation;
    };
}
#endif /* MessageContent_hpp */
