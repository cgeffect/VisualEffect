//
//  VgxProgram.h
//  Vgx
//
//  Created by Jason on 2021/6/11.
//

#ifndef VgxProgram_h
#define VgxProgram_h

#include <stdio.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

namespace vgx {

class VgxProgram {
    
public:
    VgxProgram();
    ~VgxProgram();
    
    bool setWithVertexShader(unsigned char *vShaderString, unsigned char *fShaderString);

    void use();

    void unuse();

    bool link();

    bool validate();

    #pragma mark -
    GLint getUniformLocation(unsigned char *name);
    GLint getAttribLocation(unsigned char *name);
    void setUniform1f(GLint location, GLfloat value);
    
protected:
    GLuint          program;
    GLuint          vertShader;
    GLuint          fragShader;
private:
    bool compileShader(GLuint *shader, GLenum type, unsigned char *shaderString);

};

};
#endif /* VgxProgram_h */
