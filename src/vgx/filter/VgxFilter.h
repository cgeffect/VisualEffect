//
//  VgxFilter.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef VgxFilter_h
#define VgxFilter_h

#include <stdio.h>
#include "IVgxInput.h"
#include "VgxOutput.h"
#include "VgxProgram.h"
#include "IVgxFilter.h"

namespace vgx {
class VgxFilter:public IVgxInput, public IVgxFilter, public VgxOutput {
    
public:
    VgxFilter();
    virtual ~VgxFilter();
    
public: //VgxInput
    
    virtual void newFramebufferAvailable(VgxFramebuffer *inFramebuffer) override;

public: //IVgxFilter
    
    virtual void setInputVertexShader(unsigned char *vShader, unsigned char *fShader) override;
    
    virtual void renderToTextureWithVertices(const float *vertices, const float *textureCoordinates) override;
    
    virtual void notifyNextTargetsAboutNewFrame() override;

private:
    GLint mPosition;
    GLint mTexCoord;
    GLint uTexture;
    VgxFramebuffer *mInputFramebuffer;
    VgxProgram *mShaderProgram;
};
}
#endif /* VgxFilter_h */
