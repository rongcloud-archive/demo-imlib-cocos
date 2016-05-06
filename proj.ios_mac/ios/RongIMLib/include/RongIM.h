//
//  RongIM.h
//  RongIMLib
//
//  Created by litao on 16/1/26.
//  Copyright © 2016年 Rong Cloud. All rights reserved.
//

#ifndef RongIM_h
#define RongIM_h

#ifdef __cplusplus
#define USING_NS_RongIM                     using namespace RongIM
#else
#define USING_NS_RongIM
#endif

#include "RCCommon.h"

#include "RongIMClient.h"

#include "RCConversation.h"

#include "RCMessage.h"

#include "RCMessageContent.h"
#include "RCTextMessageContent.h"
#include "RCImageMessageContent.h"
#include "RCAudioMessageContent.h"
#include "RCMediaMessageContent.h"

#include "RCNotificationMessageContent.h"
#include "RCCommandMessageContent.h"
#include "RCCustomMessageContent.h"
#include "RCStatusMessageContent.h"

#include "RCUnknownMessageContent.h"

#define RongApi    RongIM::RongIMClient::getInstance()
#endif /* RongIM_h */
