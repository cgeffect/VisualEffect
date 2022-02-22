//
//  VgxFilter.cpp
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#include "VgxFilter.h"
#include "VgxShader.h"
#include "VgxProgram.h"
#include "VgxShaderUtil.h"
#include "VgxGL.h"
#include "VgxFramebufferCache.h"
#include "VgxInterface.h"

using namespace vgx;

static const GLfloat imageVertices[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    -1.0f,  1.0f,
    1.0f,  1.0f,
};

static const GLfloat textureCoordinates[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
};

VgxFilter::VgxFilter() {
//    const std::string &_progName = kCGDrawVertexShaderString;
    unsigned char *vShader = (unsigned char *)kCGDrawVertexShaderString;
    unsigned char *fShader = (unsigned char *)kCGDrawFragmentShaderString;
    VgxFilter::setInputVertexShader(vShader, fShader);
}

VgxFilter::~VgxFilter() {
    
}

void VgxFilter::setInputVertexShader(unsigned char *vShader, unsigned char *fShader) {
    VgxProgram *program = new VgxProgram();
    program->setWithVertexShader(vShader, fShader);
    VgxShaderUtil::glCheckError("CGDrawFilter1");
    
    if (program && program->link()) {
        mPosition = program->getAttribLocation((unsigned char *)ATTR_POSITION);
        mTexCoord = program->getAttribLocation((unsigned char *)ATTR_TEXCOORD);
        uTexture = program->getUniformLocation((unsigned char *)UNIF_TEXTURE);
        glesEnableVertexAttribArray(mPosition);
        glesEnableVertexAttribArray(mTexCoord);
    }
    
    VgxShaderUtil::glCheckError("CGDrawFilter2");
    mShaderProgram = program;
}

void VgxFilter::newFramebufferAvailable(VgxFramebuffer *inFramebuffer) {
    mInputFramebuffer = inFramebuffer;
    //1.处理自己的滤镜
    renderToTextureWithVertices(imageVertices, textureCoordinates);
    //2.通知自己的下一个节点处理滤镜
    notifyNextTargetsAboutNewFrame();
}

void VgxFilter::renderToTextureWithVertices(const GLfloat *vertices, const GLfloat *textureCoordinates) {
    bool valid = mShaderProgram->validate();
    if (valid == false) {
        printf("验证失败\n");
    }
    mOutputFramebuffer = VgxFramebufferCache::shareCache()->getFramebufferForSize(mInputFramebuffer->getFboSize(), false);
    
    mShaderProgram->use();
    mOutputFramebuffer->bindFramebuffer();
    glViewport(0, 0, mInputFramebuffer->getFboSize().x, mInputFramebuffer->getFboSize().y);
    glClearColor(1.f, 1.f, 1.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mInputFramebuffer->getTexture());
    glUniform1i(uTexture, VGX_TEXTURE0); //这个是0, 不是GL_TEXTURE0
    
    glEnableVertexAttribArray(mPosition);
    glVertexAttribPointer(mPosition, 2, GL_FLOAT, 0, 0, vertices);
    glEnableVertexAttribArray(mTexCoord);
    glVertexAttribPointer(mTexCoord, 2, GL_FLOAT, 0, 0, textureCoordinates);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(mPosition);
    glDisableVertexAttribArray(mTexCoord);
    
    mOutputFramebuffer->unbindFramebuffer();
    mShaderProgram->unuse();
    
    if (mInputFramebuffer->getOnlyGenTexture() == false) {
        mInputFramebuffer->recycle();
    }
}

void VgxFilter::notifyNextTargetsAboutNewFrame() {
    std::list<VgxInput *>::iterator iter;
    for(iter = mTargetList.begin(); iter != mTargetList.end() ;iter++) {
        VgxInput *target = *iter;
        target->newFramebufferAvailable(mOutputFramebuffer);
    }
}
