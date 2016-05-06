//
//  RCCommon.h
//  RongIMLib
//
//  Created by litao on 15/11/12.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef MessageCommon_h
#define MessageCommon_h

#include <string>
#include <vector>
#include <list>

namespace RongIM {

    typedef enum _MessagePsersistent
    {

        MessagePersistent_NONE = 0,

        MessagePersistent_PERSIST = 1,

        MessagePersistent_PERSIST_COUNT = 3,
        
        MessagePersistent_STATUS = 16
    }MessagePsersistent;

    typedef enum _ConversationType
    {
        ConversationType_PRIVATE = 1,

        ConversationType_DISCUSSION,

        ConversationType_GROUP,

        ConversationType_CHATROOM,
     
        ConversationType_CUSTOMERSERVICE,

        ConversationType_SYSTEM,

        ConversationType_APPSERVICE,

        ConversationType_PUBLICSERVICE,

        ConversationType_PUSHSERVICE,
    }ConversationType;

    typedef enum _MessageStatus
    {

        ReceivedStatus_UNREAD = 0,

        ReceivedStatus_READ = 1,

        ReceivedStatus_LISTENED = 2,

        ReceivedStatus_DOWNLOADED = 4,

        SentStatus_SENDING = 10,

        SentStatus_FAILED = 20,
        
        SentStatus_SENT = 30,

        SentStatus_RECEIVED = 40,

        SentStatus_READ = 50,
     
        SentStatus_DESTROYED = 60,
    }MessageStatus;

    typedef enum _MessageDirection
    {

        MessageDirection_SEND = 1,

        MessageDirection_RECEIVE,
    }MessageDirection;

    typedef enum _MessageErrorCode
    {

        ERRORCODE_UNKNOWN = -1,

        ERRORCODE_TIMEOUT = 5004,

        REJECTED_BY_BLACKLIST = 405,

        NOT_IN_DISCUSSION = 21406,

        NOT_IN_GROUP = 22406,

        FORBIDDEN_IN_GROUP = 22408,

        NOT_IN_CHATROOM = 23406,

        MSG_ROAMING_SERVICE_UNAVAILABLE = 33007,
    }MessageErrorCode; 


    typedef enum _MediaType
    {

        MediaType_IMAGE = 1,

        MediaType_AUDIO,

        MediaType_VIDEO,

        MediaType_FILE = 100,
    }MediaType;
    
    typedef enum _ConnectionStatus{
        ConnectionStatus_Connected = 0,
        ConnectionStatus_NetworkUnavailable = 1,
        ConnectionStatus_KickedOff = 6,
        ConnectionStatus_ServerInvalid = 8,
        ConnectionStatus_ValidateFailure = 9,
        ConnectionStatus_Connecting = 10,
        ConnectionStatus_Unconnected = 11,
        ConnectionStatus_SignUp = 12,
        ConnectionStatus_TokenIncorrect = 31004,
        ConnectionStatus_DisconnExecption = 31011
    }ConnectionStatus;
    
    typedef enum {
        DL_DEBUG,
        DL_WARN,
        DL_ERROR,
        DL_NONE
    }DebugLevel;

    class ConnectionStatusListener
    {
    public:
        virtual void onConnectionStatusChange(ConnectionStatus connectionStatus) = 0;
    };
    class Message;
    class MessageListener
    {
    public:
        virtual void onSendProgress(const Message &sentMsg, int progress) = 0;
        virtual void onSendSuccess(const Message &sentMsg) = 0;
        virtual void onSendFailure(const Message &sentMsg, int code) = 0;
        
        virtual void onReceivedMessage(const Message &rcvdMsg, int nLeft) = 0;
        
        virtual ~MessageListener() {
        }
    };
    
    class GeneralCallback
    {
    public:
        virtual void onSuccess() {}
        virtual void onFailure(MessageErrorCode errorCod) {}
        virtual ~GeneralCallback() {
        }
    };
    
    class DownloadMediaFileCallback
    {
    public:
        virtual void onSuccess(std::string localMediaPath) = 0;
        virtual void onProgress(int progress) = 0;
        virtual void onFailure(MessageErrorCode errorCod) = 0;
        virtual ~DownloadMediaFileCallback() {
        }
    };
    
    class VoiceCaptureCallback
    {
    public:
        virtual ~VoiceCaptureCallback() {}
        virtual void onVoiceCaptureFinished(bool timeout, std::string voicePath, int duration) = 0;
        virtual void onVoiceVolume(float volume) = 0;
        virtual void onVoiceCaptureError(int errorCode) = 0;
    };
    
    class GetRemoteHistoryMessageCallback
    {
    public:
        virtual ~GetRemoteHistoryMessageCallback() {}
        virtual void onRemoteHistoryMessage(std::list<Message>) = 0;
    };
}
#endif /* MessageCommon_h */
