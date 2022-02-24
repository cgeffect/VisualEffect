//
//  VgxTextureOutput.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef VgxTextureOutput_h
#define VgxTextureOutput_h

#include <stdio.h>
#include "IVgxInput.h"

namespace vgx {
class VgxTextureOutput:public IVgxInput {
    
public:
    VgxTextureOutput() {
        
    }
    
    ~VgxTextureOutput() {
        
    }
    
    int getTexId() {
        return mFramebuffer->getTexture();
    }
    
    int getTexWidth() {
        return mFramebuffer->getFboSize().x;
    }

    int getTexHeight() {
        return mFramebuffer->getFboSize().y;
    }
    
public:
    void newFramebufferAvailable(VgxFramebuffer *inFramebuffer) override {
        mFramebuffer = inFramebuffer;
    };
private:
    VgxFramebuffer *mFramebuffer{nullptr};
};

}
#endif /* VgxTextureOutput_h */
