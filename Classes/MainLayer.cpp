#include "MainLayer.h"

USING_NS_CC;

bool MainLayer::init()
{
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    MenuItemFont::setFontSize(30);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _log = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    _log->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - _log->getContentSize().height));
    addChild(_log);
    
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(sprite);
    
    auto btnSendText = MenuItemFont::create("Send Text", CC_CALLBACK_1(MainLayer::onBtnSendTextClicked, this));
    btnSendText->setPosition(Vec2(200, 350));
    
    auto btnSendImage = MenuItemFont::create("Send Image", CC_CALLBACK_1(MainLayer::onBtnSendImageClicked, this));
    btnSendImage->setPosition(Vec2(200, 150));
    
    auto btnStartRec = MenuItemFont::create("Start Record", CC_CALLBACK_1(MainLayer::onBtnStartRecClicked, this));
    btnStartRec->setPosition(Vec2(700, 350));
    
    auto btnStopRec = MenuItemFont::create("Stop Record & Send", CC_CALLBACK_1(MainLayer::onBtnStopRecClicked, this));
    btnStopRec->setPosition(Vec2(700, 150));
    
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
                                           CC_CALLBACK_1(MainLayer::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(btnSendText, btnSendImage, btnStartRec, btnStopRec, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);
    
    scheduleUpdate(); // 注册更新事件
    initRongIM(); // 初始化RongIM
    return true;
}

void MainLayer::update(float dt)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    RongApi->runInMainLoop(); // 主线程驱动
#endif
}

void MainLayer::initRongIM()
{
    RongApi->setDebugLevel(DL_DEBUG); // 设置Debug log输出等级
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    RongApi->setJVM(JniHelper::getJavaVM()); // 设置JavaVM, 只有Android平台需要调用
#endif
    
    // 初始化SDK，传入从开发者平台申请的应用AppKey
    const char *appKey = "p5tvi9dst19k4";
    RongApi->init(appKey);
    
    // 注册连接状态监听和消息事件监听，需在connect之前完成
    RongApi->registerConnectionStatusListener(this);
    RongApi->registerMessageListener(this);
    
    // 以"UserA"的身份连接融云服务器，token是userId对应的身份标识，可通过融云服务器提供的RestAPI获取到
//    const char *token = "OBP6jghYYvQAmUi49wYbjS+XAKNTbHuH4vqlPeV7sUjc1p9lfcrXGw7EkVRGdfrHtF5Kji11dvbWS9GWr3YveA==";
//    const char *userId = "UserA";
//    _targetId = "UserB";

    // 两部手机测试互发，一部使用UserA，一部使用UserB。
    const char *token = "sAAV+ktv7s9U4pg5T60+OICufGyHvRjTNDe7UA9didMEWiac+qAZAw2AxhtbeGEIaE61zP9OWE5JhThKd8FlOA==";
    const char *userId = "UserB";
    _targetId = "UserA";
    RongApi->connect(token, userId);
}

void MainLayer::onBtnSendTextClicked(Ref* pSender)
{
    CCLOG("onBtnSendTextClicked");
    // 向对方发送一条文本消息
    Conversation conversation(ConversationType_PRIVATE, _targetId);
    MessageContent *textContent = TextMessageContent::createContent("Hello world");
    RongApi->sendMessage(conversation, textContent);
}

void MainLayer::onBtnSendImageClicked(Ref* pSender)
{
    CCLOG("onBtnSendImageClicked");
    // 向对方发送一条图片消息
    Conversation conversation(ConversationType_PRIVATE, _targetId);
    string path = FileUtils::getInstance()->fullPathForFilename("HelloWorld.png");
    MessageContent *imageContent = ImageMessageContent::createContent(path);
    RongApi->sendMessage(conversation, imageContent);
}

void MainLayer::onBtnStartRecClicked(Ref* pSender)
{
    CCLOG("onBtnStartRecClicked");
    RongApi->startRecordVoice(this);
}

void MainLayer::onBtnStopRecClicked(Ref* pSender)
{
    CCLOG("onBtnStartRecClicked");
    RongApi->stopRecordVoice();
}

void MainLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    RongApi->disconnect(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainLayer::onConnectionStatusChange(ConnectionStatus connectionStatus)
{
    CCLOG("onConnectionStatusChange() connectionStatus = %d", connectionStatus);
    switch (connectionStatus)
    {
        case ConnectionStatus_Connected:
            _log->setString("connectionStatus = Connected");
            break;
        case ConnectionStatus_Connecting:
            _log->setString("connectionStatus = Connectting");
            break;
        case ConnectionStatus_Unconnected:
            _log->setString("connectionStatus = Unconnected");
            break;
        case ConnectionStatus_TokenIncorrect:
            _log->setString("connectionStatus = Token incorrect");
            break;
        default:
            break;
    }
}

void MainLayer::onSendProgress(const Message &sentMsg, int progress)
{
    CCLOG("onSendProgress()");
}

void MainLayer::onSendSuccess(const Message &sentMsg)
{
    CCLOG("onSendSuccess()");
    _log->setString("Send success");
}

void MainLayer::onSendFailure(const Message &sentMsg, int code)
{
    CCLOG("onSendFailure()");
}

void MainLayer::onReceivedMessage(const Message &rcvdMsg, int nLeft)
{
    CCLOG("onReceivedMessage()");
    Message* msg = new Message(rcvdMsg);
    if (msg->m_content->isText()) {
        TextMessageContent *con = (TextMessageContent *) (msg->m_content);
        CCLOG("TextMessageContent con->m_content = %s", con->m_content.c_str());
       
        _log->setString("Received TextMessage = " + con->m_content);
    } else if (msg->m_content->isImage()) {
        ImageMessageContent *con = (ImageMessageContent *) (msg->m_content);
        CCLOG("ImageMessageContent con->getMediaUrl = %s", con->getMediaUrl().c_str());
        CCLOG("ImageMessageContent con->getThumbnailPath = %s", con->getThumbnailPath().c_str());
        RongApi->downloadMedia(msg->m_conversation, ((MediaMessageContent *) (msg->m_content))->getMediaType(),
                               ((MediaMessageContent *) (msg->m_content))->getMediaUrl(), this);
    } else if (msg->m_content->isAudio()) {
        AudioMessageContent *con = (AudioMessageContent *) (msg->m_content);
        CCLOG("AudioMessageContent con->m_mediaUrl = %s", con->getMediaUrl().c_str());
        RongApi->downloadMedia(msg->m_conversation, ((MediaMessageContent *) (msg->m_content))->getMediaType(),
                               ((MediaMessageContent *) (msg->m_content))->getMediaUrl(), this);
    }
}

void MainLayer::onVoiceCaptureFinished(bool timeout, string voicePath, int duration)
{
    CCLOG("onVoiceCaptureFinished()");
    _log->setString("Record finished");
    Conversation conversation(ConversationType_PRIVATE, _targetId);
    MediaMessageContent *voiceContent = AudioMessageContent::createContent(voicePath, duration);
    RongApi->sendMessage(conversation, voiceContent);
}

void MainLayer::onVoiceVolume(float volume)
{
    CCLOG("onVoiceVolume volume = %f", volume);
    char str[255];
    sprintf(str, "Record volume = %f", volume);
    _log->setString(str);
}

void MainLayer::onVoiceCaptureError(int errorCode)
{
}

void MainLayer::onSuccess(std::string localMediaPath)
{
    CCLOG("Download localMediaPath = %s", localMediaPath.c_str());
    _log->setString("localMediaPath = " + localMediaPath);
}

void MainLayer::onProgress(int progress)
{
    
}

void MainLayer::onFailure(MessageErrorCode errorCod)
{
    
}
