//
//  CGDrawOutput.h
//  CGDraw
//
//  Created by Jason on 2021/6/11.
//

#ifndef CGDrawOutput_h
#define CGDrawOutput_h

#include <stdio.h>
#include <list>
#include "VgxInput.h"
#include "CGDrawFramebuffer.h"

namespace vgx {
class CGDrawOutput {
            
//    virtual ~CGDrawOutput() {
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
    CGDrawFramebuffer *mOutputFramebuffer{nullptr};
    std::list<VgxInput *>mTargetList;
};

}

#endif /* CGDrawOutput_h */

