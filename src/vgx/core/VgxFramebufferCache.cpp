//
//  CGDrawFramebufferCache.cpp
//  CGDraw
//
//  Created by Jason on 2021/6/11.
//

#include "VgxFramebufferCache.h"

using namespace vgx;
using namespace std;
void VgxFramebufferCache::glInit() {
    
}

void VgxFramebufferCache::glUnInit() {
    
}

void VgxFramebufferCache::destroy() {
    
}

CGDrawFramebuffer * VgxFramebufferCache::getFramebufferForSize(VgxVec2f size, bool onlyTexture) {
    CGDrawFramebuffer *buffer = VgxFramebufferCache::getFramebufferForSize(size, CGDrawFramebuffer::defaultTextureOption(), onlyTexture);
    return buffer;
}

CGDrawFramebuffer * VgxFramebufferCache::getFramebufferForSize(vgx::VgxVec2f size, CGTextureOptions textureOptions, bool onlyTexture) {
    CGDrawFramebuffer *buffer = new CGDrawFramebuffer();
    buffer->genWithSize(size, textureOptions, onlyTexture);
    return buffer;
}

void VgxFramebufferCache::recycleFramebufferToCache(vgx::CGDrawFramebuffer *framebuffer) {
    map<string, list<CGDrawFramebuffer *>>::iterator itor = mFramebufferCache.find(framebuffer->getHashKey());
    if (itor != mFramebufferCache.end()) {
        pair<string, list<CGDrawFramebuffer *>> fbCache = *itor;
        list<CGDrawFramebuffer *> fbList = fbCache.second;
        fbList.push_back(framebuffer);
        framebuffer->setActivity(true);
    }
    
}

void VgxFramebufferCache::deleteAllUnassignedFramebuffers() {
    mFramebufferCache.clear();
}


