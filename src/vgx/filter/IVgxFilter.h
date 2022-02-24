//
//  IVgxFilter.h
//  VisualEffect
//
//  Created by Jason on 2022/2/24.
//

#ifndef IVgxFilter_h
#define IVgxFilter_h

namespace vgx {
class IVgxFilter {

public:
    
    virtual void setInputVertexShader(unsigned char *vShader, unsigned char *fShader) = 0;
    
    virtual void renderToTextureWithVertices(const float *vertices, const float *textureCoordinates) = 0;
    
    virtual void notifyNextTargetsAboutNewFrame() = 0;

};
}

#endif /* IVgxFilter_h */
