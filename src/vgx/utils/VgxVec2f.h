//
//  VgxVec.h
//  Vgx
//
//  Created by Jason on 2021/6/23.
//

#ifndef CGDrawVec_h
#define CGDrawVec_h

#include <math.h>

namespace vgx {

struct VgxVec2f {

    float x{0.f};
    float y{0.f};

    VgxVec2f() : x(0.f), y(0.f) {
        
    }

    VgxVec2f(float _x, float _y) :
        x(_x), y(_y) {
    }

    VgxVec2f(const VgxVec2f &_v) :
        x(_v.x), y(_v.y) {
    }

    ~VgxVec2f() {
    }

    inline void set(float _x, float _y) {
        x = _x;
        y = _y;
    }

    inline void set(const VgxVec2f &_v) {
        x = _v.x;
        y = _v.y;
    }

    inline bool isZero() {
        return x == 0.f && y == 0.f;
    }

};

}
#endif /* CGDrawVec_h */
