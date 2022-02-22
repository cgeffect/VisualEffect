//
//  CGDrawDataInput.h
//  CGDraw
//
//  Created by Jason on 2021/6/11.
//

#ifndef CGDrawDataInput_h
#define CGDrawDataInput_h

#include "CGDrawOutput.h"
namespace vgx {

class VgxDataInput:public CGDrawOutput {
    
public:
    void setInputData(const unsigned char *data, int width, int height) {
        VgxVec2f _size = VgxVec2f(width, height);
        framebuffer.genWithSize(_size, true);
        framebuffer.bindTexture();
        framebuffer.upload(data, _size, GL_RGBA, GL_RGBA, false);
        framebuffer.unbindTexture();
        mOutputFramebuffer = &framebuffer;
    }
    void requestRender() override {
        std::list<VgxInput *>::iterator iter;
        for(iter = mTargetList.begin(); iter != mTargetList.end(); iter++) {
            VgxInput *target = *iter;
            target->newFramebufferAvailable(mOutputFramebuffer);
        }
    }
private:
    CGDrawFramebuffer framebuffer;
};

}

#endif /* CGDrawDataInput_h */
