//
//  VgxFilter.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef VgxFilter_h
#define VgxFilter_h

#include <stdio.h>
#include "VgxInput.h"
#include "VgxOutput.h"
#include "VgxProgram.h"
#include "IVgxFilter.h"

namespace vgx {
class VgxFilter:public VgxInput, public VgxOutput  {
    
public:
    VgxFilter();
    virtual ~VgxFilter();
    
public: //VgxInput
    void setInputVertexShader(unsigned char *vShader, unsigned char *fShader);
    
    void newFramebufferAvailable(VgxFramebuffer *inFramebuffer) override;

public:
    
    void renderToTextureWithVertices(const float *vertices, const float *textureCoordinates);
    
    void notifyNextTargetsAboutNewFrame();

private:
    GLint mPosition;
    GLint mTexCoord;
    GLint uTexture;
    VgxFramebuffer *mInputFramebuffer;
    VgxProgram *mShaderProgram;
};
}
#endif /* VgxFilter_h */
