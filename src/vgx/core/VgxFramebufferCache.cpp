//
//  VgxFramebufferCache.cpp
//  Vgx
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

VgxFramebuffer * VgxFramebufferCache::getFramebufferForSize(VgxVec2f size, bool onlyTexture) {
    VgxFramebuffer *buffer = VgxFramebufferCache::getFramebufferForSize(size, VgxFramebuffer::defaultTextureOption(), onlyTexture);
    return buffer;
}

VgxFramebuffer * VgxFramebufferCache::getFramebufferForSize(vgx::VgxVec2f size, CGTextureOptions textureOptions, bool onlyTexture) {
    VgxFramebuffer *buffer = new VgxFramebuffer();
    buffer->genWithSize(size, textureOptions, onlyTexture);
    return buffer;
}

void VgxFramebufferCache::recycleFramebufferToCache(vgx::VgxFramebuffer *framebuffer) {
    map<string, list<VgxFramebuffer *>>::iterator itor = mFramebufferCache.find(framebuffer->getHashKey());
    if (itor != mFramebufferCache.end()) {
        pair<string, list<VgxFramebuffer *>> fbCache = *itor;
        list<VgxFramebuffer *> fbList = fbCache.second;
        fbList.push_back(framebuffer);
        framebuffer->setActivity(true);
    }
    
}

void VgxFramebufferCache::deleteAllUnassignedFramebuffers() {
    mFramebufferCache.clear();
}


