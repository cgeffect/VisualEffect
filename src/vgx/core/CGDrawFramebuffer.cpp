//
//  CGDrawFramebuffer.cpp
//  CGDraw
//
//  Created by Jason on 2021/6/11.
//

#include "CGDrawFramebuffer.h"
#include "CGShaderUtil.h"
#include "CGDrawTexture.h"
#include "CGDrawFramebufferCache.h"
using namespace vgx;

#pragma mark - life cycle
void CGDrawFramebuffer::glInit() {
    
}

void CGDrawFramebuffer::glUnInit() {
    
}

void CGDrawFramebuffer::recycle() {
    CGDrawFramebufferCache().shareCache()->recycleFramebufferToCache(this);
}

void CGDrawFramebuffer::destroy() {
    if (mFramebuffer) {
        glDeleteFramebuffers(1, &mFramebuffer);
        mFramebuffer = GL_NONE;
    }
    
    if (mOnlyGenTexture) {
        if (mTexture) {
            glDeleteTextures(1, &mTexture);
            mTexture = GL_NONE;
        }
    } else {
        if (mTexture) {
            glDeleteTextures(1, &mTexture);
            mTexture = GL_NONE;
        }
    }
    printf("CGDrawFramebuffer destroy\n");
}

#pragma mark - param
void CGDrawFramebuffer::genWithSize(CGVec2f fboSize, bool onlyTexture) {
    mTextureOptions = CGDrawFramebuffer::defaultTextureOption();
    genWithSize(fboSize, mTextureOptions, onlyTexture);
}

void CGDrawFramebuffer::genWithSize(CGVec2f fboSize, CGTextureOptions textureOptions, bool onlyTexture) {
    mFboSize = fboSize;
    mOnlyGenTexture = onlyTexture;
    mTextureOptions = textureOptions;
    if (onlyTexture) {
        generateTexture();
    } else {
        generateFramebuffer();
    }
}

void CGDrawFramebuffer::genWithSize(CGVec2f fboSize, GLuint texture) {
    mTexture = texture;
    mFboSize = fboSize;
}

void CGDrawFramebuffer::upload(const unsigned char *data, CGVec2f size, GLenum internalformat, GLenum format, bool isOverride) {
    if (isOverride) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.x, size.y, format, GL_UNSIGNED_BYTE, data);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);
    }
}

#pragma mark - private gl 私有函数为什么会提示删除
void CGDrawFramebuffer::generateTexture() {
    //静态函数
//    CGDrawTexture::genTexture()
    glesGenTextures(1, &mTexture);
    glesBindTexture(GL_TEXTURE_2D, mTexture);
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mTextureOptions.minFilter);
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mTextureOptions.magFilter);
    // This is necessary for non-power-of-two textures
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mTextureOptions.wrapS);
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mTextureOptions.wrapT);
}

void CGDrawFramebuffer::generateFramebuffer() {
    glesGenFramebuffers(1, &mFramebuffer);
    glesBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    generateTexture();
    glesBindTexture(GL_TEXTURE_2D, mTexture);
    glesTexImage2D(GL_TEXTURE_2D, 0, mTextureOptions.internalFormat, (int)mFboSize.x, (int)mFboSize.y, 0, mTextureOptions.format, mTextureOptions.type, 0);
    glesFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);
    glesBindTexture(GL_TEXTURE_2D, 0);
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//    Assert(status == GL_FRAMEBUFFER_COMPLETE, @"Incomplete filter FBO: %d", status);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("Incomplete filter FBO: %d\n", status);
    }

}
