#pragma once

#include "cocos2d.h"
#include "RongIM.h"

USING_NS_RongIM;

class MainLayer : public cocos2d::Layer,
    public ConnectionStatusListener, // RongSDK 连接状态监听
    public MessageListener, // RongSDK 消息状态监听
    public VoiceCaptureCallback, // RongSDK 录音事件监听
    public DownloadMediaFileCallback // RongSDK 媒体消息下载监听
{
public:
    CREATE_FUNC(MainLayer);
    virtual bool init();
    
private:
    void update(float dt);
    void initRongIM();
    
    // button event callback.
    void onBtnSendTextClicked(cocos2d::Ref* pSender);
    void onBtnSendImageClicked(cocos2d::Ref* pSender);
    void onBtnStartRecClicked(cocos2d::Ref* pSender);
    void onBtnStopRecClicked(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    
protected:
    // ConnectionStatusListener
    // 连接状态回调
    void onConnectionStatusChange(ConnectionStatus connectionStatus);
    
    // MessageListener
    // 发送进度回调
    void onSendProgress(const Message &sentMsg, int progress);
    // 发送成功
    void onSendSuccess(const Message &sentMsg);
    // 发送失败
    void onSendFailure(const Message &sentMsg, int code);
    // 接收消息回调
    void onReceivedMessage(const Message &rcvdMsg, int nLeft);
    
    // VoiceCaptureCallback
    void onVoiceCaptureFinished(bool timeout, string voicePath, int duration);
    void onVoiceVolume(float volume);
    void onVoiceCaptureError(int errorCode);
    
    // DownloadMediaFileCallback
    void onSuccess(std::string localMediaPath);
    void onProgress(int progress);
    void onFailure(MessageErrorCode errorCod);
    
private:
    cocos2d::Label *_log;
    string _targetId;
};