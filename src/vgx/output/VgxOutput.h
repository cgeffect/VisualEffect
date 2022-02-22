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
#include "VgxInput.h"
#include "VgxFramebuffer.h"

namespace vgx {
class VgxOutput {
            
//    virtual ~VgxOutput() {
//        
//    };
public:
    virtual void addTarget(VgxInput *newtarget) {
        mTargetList.push_back(newtarget);
    };
    virtual void removeTarget(VgxInput *targetToRemove) {
        mTargetList.remove(targetToRemove);
    };
    virtual void removeAllTargets() {
        mTargetList.clear();
    };
    virtual std::list<VgxInput *>targets() {
        return mTargetList;
    };
    virtual void requestRender() {
        
    };
    
protected:
    VgxFramebuffer *mOutputFramebuffer{nullptr};
    std::list<VgxInput *>mTargetList;
};

}

#endif /* VgxOutput_h */

