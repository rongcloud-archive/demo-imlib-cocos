//
//  RCMediaMessageContent.hpp
//  RongIMLib
//
//  Created by litao on 15/11/12.
//  Copyright © 2015年 Rong Cloud. All rights reserved.
//

#ifndef MediaMessageContent_hpp
#define MediaMessageContent_hpp

#include <sys/types.h>
#include <string>
#include "RCMessageContent.h"

using namespace std;

namespace RongIM {
    class MessageModule;
    class StorageModule;
    class MediaMessageContent : public MessageContent {
        
    public:
        virtual MediaType getMediaType() const = 0;
        
        MediaMessageContent(const string &extra) : MessageContent(extra) { m_thumbnail = NULL; m_thumbnailSize = 0; }
        virtual ~MediaMessageContent(){
            if(m_thumbnail) {
                delete [] m_thumbnail;
                m_thumbnail = NULL;
            }
        }
        
        string getMediaUrl() const;
        string getThumbnailPath() const;
        
        void setMediaUrl(string mediaUrl) { m_mediaUrl = mediaUrl; }
        void setThumbnailPath(string thumbnailPath) { m_thumbnailPath = thumbnailPath; };
        
        bool isMedia() const { return true; }
        
        //do not use these two member.
        unsigned char* m_thumbnail;
        size_t m_thumbnailSize;
    protected:
        virtual unsigned char *generateThumbnail(const string &mediaPath, size_t *size) const { if (size) *size = 0; return NULL; }
        string m_mediaUrl;
        string m_thumbnailPath;
        friend class MessageModule;
    private:
        void generateThumbnail();
        void saveThumbnail();
        friend class StorageModule;
    };
}

#endif /* MediaMessageContent_hpp */
