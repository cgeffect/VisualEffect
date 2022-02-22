//
//  VgxBridge.h
//  Vgx
//
//  Created by UFOTO on 2021/7/9.
//

#ifndef VgxBridge_h
#define VgxBridge_h

#ifdef __APPLE__

typedef unsigned char *(*getTexture)(void *bridge, long tmp);
typedef struct Bridge_IOS {
    void *bridge;
    getTexture getTexture;
} CallbackCpp;

#endif

#endif /* VgxBridge_h */
