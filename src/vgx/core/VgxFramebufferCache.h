//
//  VgxFramebufferCache.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef VgxFramebufferCache_h
#define VgxFramebufferCache_h

#include <stdio.h>
#include "VgxFramebuffer.h"
#include "VgxVec2f.h"
#include <pthread/pthread.h>
#include <map>
#include <iostream>
#include <list>

namespace vgx {

class VgxFramebufferCache {
    
public:
//    static pthread_mutex_t m_mutex;

    static VgxFramebufferCache* shareCache() {
//        pthread_mutex_lock(&m_mutex);
        static VgxFramebufferCache instance;
//        pthread_mutex_unlock(&m_mutex);
        return &instance;
    }
    
    void glInit();
    
    void glUnInit();
    
    void destroy();
    
    VgxFramebufferCache() {
//        pthread_mutex_init(&m_mutex, NULL);
    };
    ~VgxFramebufferCache() {
        
    };

private:

   
    
public:
    VgxFramebuffer *getFramebufferForSize(VgxVec2f size, bool onlyTexture);
    
    VgxFramebuffer *getFramebufferForSize(VgxVec2f size, CGTextureOptions textureOptions, bool onlyTexture);

    void recycleFramebufferToCache(VgxFramebuffer *framebuffer);
    
    void deleteAllUnassignedFramebuffers();
    
private:
  
    std::list<VgxFramebuffer *>mTargetList;

    std::map<std::string, std::list<VgxFramebuffer *>> mFramebufferCache;


};
}


#endif /* VgxFramebufferCache_h */
