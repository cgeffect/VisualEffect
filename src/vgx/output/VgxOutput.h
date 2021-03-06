//
//  VgxOutput.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef VgxOutput_h
#define VgxOutput_h

#include <stdio.h>
#include <list>
#include "IVgxInput.h"
#include "VgxFramebuffer.h"

namespace vgx {
class VgxOutput {
            
public:
    
    VgxOutput() {
        
    }
    
    virtual ~VgxOutput() {
        
    };

    //这几个方法子类不需要重写, 不需要加virtual
    void addTarget(IVgxInput *newtarget) {
        mTargetList.push_back(newtarget);
    };
    void removeTarget(IVgxInput *targetToRemove) {
        mTargetList.remove(targetToRemove);
    };
    void removeAllTargets() {
        mTargetList.clear();
    };
    std::list<IVgxInput *>targets() {
        return mTargetList;
    };
    
    //这个方法子类不需要重写, 不需要加virtual
    virtual void requestRender() {
        
    };
    
protected:
    VgxFramebuffer *mOutputFramebuffer{nullptr};
    std::list<IVgxInput *>mTargetList;
};

}

#endif /* VgxOutput_h */

