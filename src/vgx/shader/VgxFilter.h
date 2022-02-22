//
//  VgxFilter.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef CGDrawFilter_h
#define CGDrawFilter_h

#include <stdio.h>
#include "VgxInput.h"
#include "VgxOutput.h"
#include "VgxProgram.h"

namespace vgx {
class VgxFilter:public VgxInput, public VgxOutput  {
    
public:
    VgxFilter();
    virtual ~VgxFilter();
    
    void setInputVertexShader(unsigned char *vShader, unsigned char *fShader);
    
public:
    void renderToTextureWithVertices(const float *vertices, const float *textureCoordinates);
    void notifyNextTargetsAboutNewFrame();

    void newFramebufferAvailable(VgxFramebuffer *inFramebuffer) override;
private:
    GLint mPosition;
    GLint mTexCoord;
    GLint uTexture;
    VgxFramebuffer *mInputFramebuffer;
    VgxProgram *mShaderProgram;
};
}
#endif /* CGDrawFilter_h */
