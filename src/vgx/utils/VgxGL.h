//
//  VgxGL.h
//  Vgx
//
//  Created by Jason on 2021/6/23.
//

#ifndef VgxGL_h
#define VgxGL_h

#ifdef __ANDROID__
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        #include <OpenGLES/ES2/gl.h>
        #include <OpenGLES/ES2/glext.h>
    #elif TARGET_OS_MAC
        #include <OpenGL/gl.h>
        #include <OpenGL/glext.h>
        #include <OpenGL/gl3.h>
    #else
        #error "Unsupported Apple Device"
    #endif
#endif



//Texture
#define TEXTURE_NULL    (-1)
#define VGX_TEXTURE0     0x0
#define VGX_TEXTURE1     0x1
#define VGX_TEXTURE2     0x2
#define VGX_TEXTURE3     0x3
#define VGX_TEXTURE4     0x4
#define VGX_TEXTURE5     0x5
#define VGX_TEXTURE6     0x6
#define VGX_TEXTURE7     0x7
#define VGX_TEXTURE8     0x8
#define VGX_TEXTURE9     0x9
#define VGX_TEXTURE10    0xA
#define VGX_TEXTURE11    0xB
#define VGX_TEXTURE12    0xC
#define VGX_TEXTURE13    0xD
#define VGX_TEXTURE14    0xE
#define VGX_TEXTURE15    0xF
#define VGX_TEXTURE16    0xD0
#define VGX_TEXTURE17    0xD1
#define VGX_TEXTURE18    0xD2
#define VGX_TEXTURE19    0xD3
#define VGX_TEXTURE20    0xD4
#define VGX_TEXTURE21    0xD5
#define VGX_TEXTURE22    0xD6
#define VGX_TEXTURE23    0xD7
#define VGX_TEXTURE24    0xD8
#define VGX_TEXTURE25    0xD9
#define VGX_TEXTURE26    0xDA
#define VGX_TEXTURE27    0xDB
#define VGX_TEXTURE28    0xDC
#define VGX_TEXTURE29    0xDD
#define VGX_TEXTURE30    0xDE
#define VGX_TEXTURE31    0xDF

#define _SHADER_SRC(...) #__VA_ARGS__
#define VGX_SHADER_SRC(...) _SHADER_SRC(__VA_ARGS__)

//GLSL
#define ATTR_POSITION "position"
#define ATTR_TEXCOORD "aTexCoord"
#define UNIF_TEXTURE  "uTexture"

#define GLTex GLuint

#endif /* VgxGL_h */
