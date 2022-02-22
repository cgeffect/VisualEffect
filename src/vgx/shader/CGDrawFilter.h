//
//  CGDrawFilter.h
//  CGDraw
//
//  Created by Jason on 2021/6/11.
//

#ifndef CGDrawFilter_h
#define CGDrawFilter_h

#include <stdio.h>
#include "VgxInput.h"
#include "CGDrawOutput.h"
#include "CGDrawProgram.h"

namespace vgx {
class CGDrawFilter:public VgxInput, public CGDrawOutput  {
    
public:
    CGDrawFilter();
    virtual ~CGDrawFilter();
    
    virtual void setInputVertexShader(unsigned char *vShader, unsigned char *fShader);
    
public:
    void renderToTextureWithVertices(const float *vertices, const float *textureCoordinates);
    void notifyNextTargetsAboutNewFrame();

    void newFramebufferAvailable(CGDrawFramebuffer *inFramebuffer) override;
private:
    GLint mPosition;
    GLint mTexCoord;
    GLint uTexture;
    CGDrawFramebuffer *mInputFramebuffer;
    CGDrawProgram *mShaderProgram;
};
}
#endif /* CGDrawFilter_h */
