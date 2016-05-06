//
//  RongIMClient.hpp
//  RongIMLib
//
//  Created by litao on 16/2/2.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#ifndef RongIMClient_hpp
#define RongIMClient_hpp

#include <stdint.h>
#include <string>
#include <vector>
#include "RCMessageContent.h"
#include "RCMediaMessageContent.h"
#include "RCConversation.h"
#include <list>
using namespace std;

namespace RongIM {

    
    class ConnectivityModule;
    
    class RongIMClient
    {
    public:
        static const RongIMClient* getInstance() {
            static RongIMClient instance;
            return &instance;
        }
        
        /**
         * 设置JavaVM, 仅Android需要。
         *
         * @param jvm: JavaVM，Cocos2dx下可使用 setJVM(JniHelper::getJavaVM())设置。
         */
        void setJVM(void *jvm) const;
        
        /**
         * 线程同步函数, 在update里没帧调用，仅Android需要。
         */
        void runInMainLoop() const;
        
        /**
         * 设置SDK Log输出等级。
         *
         * @param dl: 输出等级
         */
        void setDebugLevel(DebugLevel dl) const;
        
        /**
         * 初始化 SDK。
         * 在整个应用程序全局，只需要调用一次 init 方法。传入您从开发者平台申请的 appKey
         *即可。
         *
         * @param appKey      从开发者平台申请的应用 appKey。
         */
        void init(const string &appKey) const;
        
        /**
         * 设置 DeviceToken，用于 APNS 的设备唯一标识。请在获取到Device
         * Token之后立即调用该方法。仅在iOS平台使用。
         * @param deviceToken 从苹果服务器获取的设备唯一标识
         */
        void setDeviceToken(const string &deviceToken) const;
        
        /**
         * 获取SDK版本号
         *
         * @return SDK版本号
         */
        string getSDKVersion() const;
        
        /**
         * 销毁 SDK。
         *
         */
        void destroy() const;
        
        
        void connect(const string &token, const string &userId) const;
        void registerConnectionStatusListener(ConnectionStatusListener *listener) const;
        void unregisterConnectionStatusListener(ConnectionStatusListener *listener) const;
        void disconnect(bool receivedPush) const;
        ConnectionStatus getConnectionStatus() const;
        
        void registerMessageListener(MessageListener *listener) const;
        void unregisterMessageListener(MessageListener *listener) const;
        
        void registerMessageContentFactory(const MessageContentFactory *contentFactory) const;
        
        Message sendMessage(const Conversation &conversation, MessageContent *messageContent, const string &pushContent = "", const string &pushData = "") const;
        
        void joinChatRoom(string chatroomId, int pullHistoryCount, GeneralCallback *callback) const;
        void quitChatRoom(string chatroomId, GeneralCallback *callback) const;
        
        void startRecordVoice(VoiceCaptureCallback *callback) const;
        void stopRecordVoice() const;
        
        void downloadMedia(const Conversation &conversation, MediaType mediaType, string mediaUrl, DownloadMediaFileCallback *callback) const;
        
        /**
         *  获取会话列表。
         *
         *  会话列表按照时间从前往后排列，如果有置顶会话，则置顶会话在前。
         *
         *  @param conversationTypeList 会话类型数组，存储对象为NSNumber类型 type类型为int
         *  @return 会话列表。
         */
        list<Conversation> getConversationList(const list<ConversationType> &conversationTypes) const;
        
        /**
         *  从会话列表中移除某一会话，但是不删除会话内的消息。
         *
         *  如果此会话中有新的消息，该会话将重新在会话列表中显示，并显示最近的历史消息。
         *
         *  @param conversation 会话。
         *
         *  @return 是否移除成功。
         */
        bool removeConversation(const Conversation &conversation) const;
        
        /**
         *  设置某一会话为置顶或者取消置顶。
         *
         *  @param conversation 会话。
         *  @param isTop            是否置顶。
         *
         *  @return 是否设置成功。
         */
        bool setConversationToTop(const Conversation &conversation, bool isTop) const;
        
        /**
         *  获取来自某用户（某会话）的未读消息数。
         *
         *  @param conversation 会话。
         *
         *  @return 未读消息数。
         */
        int getUnreadCount(const Conversation &conversation) const;
        
        /**
         *  获取某会话类型的未读消息数.
         *
         *  @param conversationTypes 会话类型, 存储对象为NSNumber type类型为int
         *
         *  @return 未读消息数。
         */
        int getUnreadCount(const list<ConversationType> &conversationTypes) const;
        
        /**
         *  获取最新消息记录。
         *
         *  @param conversation 会话。
         *  @param count            要获取的消息数量。
         *
         *  @return 最新消息记录，按照时间顺序从新到旧排列。
         */
        list<Message> getLatestedMessages(const Conversation &conversation, unsigned int count) const;
        
        /**
         *  获取历史消息记录。
         *
         *  @param conversation 会话。
         *  @param oldestMessageId  最后一条消息的 Id，获取此消息之前的 count 条消息。
         *  @param count            要获取的消息数量。
         *
         *  @return 历史消息记录，按照时间顺序新到旧排列。
         */
        list<Message> getHistoryMessages(const Conversation &conversation, long oldestMessageId, unsigned int count) const;
        
        /**
         * 从服务器端获取之前的历史消息
         *
         * @param conversationType    会话类型
         * @param targetId            目标会话ID
         * @param recordTime          记录时间，返回这个时间之前的最近count条消息
         * @param count               需要获取的消息数量， 0< count <= 20
         * @param callback            获取成功的回调
         *
         * @discussion 此方法从服务器端获取之前的历史消息，但是必须先开通历史消息云存储功能。
         */
        void getRemoteHistoryMessages(const Conversation &conversation, long recordTime, unsigned int count, GetRemoteHistoryMessageCallback *callback) const;
        
        /**
         *  插入一条消息。
         *
         *  @param conversation 会话。不支持聊天室会话。
         *  @param senderUserId     消息的发送者，如果为空则为当前用户。
         *  @param sendStatus       要插入的消息状态。
         *  @param content          消息内容
         *
         *  @return 插入的消息实体。
         */
        Message insertMessage(const Conversation &conversation, const string &sendUserId, MessageStatus sendStatus, MessageContent *content) const;
        
        /**
         *  删除指定的一条或者一组消息。
         *
         *  @param messageIds 要删除的消息 Id 列表, 存储对象为NSNumber
         *messageId，类型为long。
         *
         *  @return 是否删除成功。
         */
        bool deleteMessages(const list<long> &msgIds) const;
        
        /**
         *  清空某一会话的所有聊天消息记录。
         *
         *  @param conversation 会话。不支持聊天室会话。
         *
         *  @return 是否清空成功。
         */
        bool clearMessages(const Conversation &conversation) const;
        
        /**
         *  清除消息未读状态。
         *
         *  @param conversation 会话。不支持聊天室会话。
         *
         *  @return 是否清空成功。
         */
        bool clearMessagesUnreadStatus(const Conversation &conversation) const;
        
        /**
         *  清空会话列表
         *
         *  @param conversationTypeList 会话类型列表，存储对象为NSNumber, type类型为int
         *
         *  @return 操作结果
         */
        bool clearConversations(const list<ConversationType> &conversationTypes) const;
        
        /**
         *  设置接收到的消息状态。
         *
         *  @param messageId      消息 Id。
         *  @param receivedStatus 接收到的消息状态。
         */
        bool setMessageReceivedStatus(long messageId, MessageStatus receivedStatus) const;
        
        
        /**
         *  设置消息发送状态。
         *
         *  @param messageId      消息 Id。
         *  @param sentStatus 接收到的消息状态。
         */
        bool setMessageSentStatus(long messageId, MessageStatus sentStatus) const;
        
    private:
        RongIMClient() {};
    };
}
#endif /* RongIMClient_hpp */
