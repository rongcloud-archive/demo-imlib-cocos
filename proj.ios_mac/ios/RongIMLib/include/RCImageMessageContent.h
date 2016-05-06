//
//  RCImageMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/17.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef ImageMessageContent_hpp
#define ImageMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCCommon.h"
#include "RCMediaMessageContent.h"

using namespace std;

namespace RongIM {
    class ImageMessageContent : public MediaMessageContent {
    public:
        virtual string encode() const;
        virtual void decode(const string &rawData);
        virtual const MessageContentFactory* getFactory() const {
            return ImageMessageContent::getStaticFactory();
        }
        MessageContent* copy() const;
        MediaType getMediaType() const { return MediaType_IMAGE; }
        
        
        static ImageMessageContent* createContent(const string &localPath, const string &extra = "") {
            return new ImageMessageContent(localPath, extra);
        }
        
        static ImageMessageContent* createContent(const string &remoteUrl, unsigned char *thumbnailData, size_t thumbnailSize, const string &extra = "") {
            return new ImageMessageContent(remoteUrl, thumbnailData, thumbnailSize, extra);
        }
        
        static const MessageContentFactory *getStaticFactory();
        virtual ~ImageMessageContent(){ }
        
#ifdef RONG_IM_LIB_SUPPORT_OBJECT_SERIALIZABLE
        virtual std::string serialize();
        virtual void unserialize(const std::string &serializedData);
#endif
        
    protected:
        unsigned char *generateThumbnail(const string &mediaPath, size_t *size) const;
    private:
        ImageMessageContent(const string &localPath, const string &extra) : MediaMessageContent(extra) {
            m_mediaUrl = localPath;
        }
        
        ImageMessageContent(const string &remoteUrl, unsigned char *thumbnailData, size_t thumbnailSize, const string &extra) : MediaMessageContent(extra) {
            m_mediaUrl = remoteUrl;
            m_thumbnail = thumbnailData;
            m_thumbnailSize = thumbnailSize;
        }
    };
}


#endif /* ImageMessageContent_hpp */
