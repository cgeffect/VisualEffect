//
//  VgxTextureInput.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef VgxTextureInput_h
#define VgxTextureInput_h

#include <stdio.h>
#include "VgxOutput.h"
#include "CGDrawInput.h"

namespace vgx {

class VgxTextureInput:public VgxOutput {
    
public:
    VgxTextureInput() {
        
    }
    ~VgxTextureInput() {
        
    }
    void requestRender() override {
        std::list<CGDrawInput *>::iterator iter;
        for(iter = mTargetList.begin(); iter != mTargetList.end() ;iter++) {
            CGDrawInput *target = *iter;
            target->newFramebufferAvailable(mOutputFramebuffer);
        }
    };
};

}
#endif /* VgxTextureInput_h */
