//
//  RCAudioMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/17.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef AudioMessageContent_hpp
#define AudioMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCCommon.h"
#include "RCMediaMessageContent.h"

using namespace std;

namespace RongIM {
    class AudioMessageContent : public MediaMessageContent {
    public:
        virtual string encode() const;
        virtual void decode(const string &rawData);
        virtual const MessageContentFactory* getFactory() const {
            return AudioMessageContent::getStaticFactory();
        }
        MessageContent* copy() const;
        MediaType getMediaType() const { return MediaType_AUDIO; }

        
        static AudioMessageContent* createContent(const string &mediaUrl, long duration,  const string &extra = "") {
            return new AudioMessageContent(mediaUrl, duration,  extra);
        }
        
        static const MessageContentFactory *getStaticFactory();
        virtual ~AudioMessageContent(){ }
        
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
        long m_duration;
        
    private:
        AudioMessageContent(const string &mediaUrl, long duration, const string &extra) : MediaMessageContent(extra) {
            setMediaUrl(mediaUrl);
            m_duration = duration;
        }
    };
}


#endif /* AudioMessageContent_hpp */
