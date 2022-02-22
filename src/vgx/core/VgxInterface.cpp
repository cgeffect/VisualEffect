//
//  VgxInterface.cpp
//  VisualEffect
//
//  Created by Jason on 2022/2/18.
//

#include "VgxInterface.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

GL_API void GL_APIENTRY glesEnableVertexAttribArray(GLuint index) {
    glEnableVertexAttribArray(index);
}

GL_API void GL_APIENTRY glesGenTextures (GLsizei n, GLuint* textures) {
    glGenTextures(n, textures);
}

GL_API void GL_APIENTRY glesBindTexture (GLenum target, GLuint texture) {
    glBindTexture (target, texture);
}

GL_API void GL_APIENTRY glesTexParameteri (GLenum target, GLenum pname, GLint param) {
    glTexParameteri(target, pname, param);
}

GL_API void GL_APIENTRY glesTexParameterf (GLenum target, GLenum pname, GLint param) {
    glTexParameterf(target, pname, param);
}

GL_API void GL_APIENTRY glesGenFramebuffers (GLsizei n, GLuint* framebuffers) {
    glGenFramebuffers (n, framebuffers);
}
GL_API void GL_APIENTRY glesGenRenderbuffers (GLsizei n, GLuint* renderbuffers) {
    glGenRenderbuffers ( n, renderbuffers);
}

GL_API void GL_APIENTRY glesBindFramebuffer (GLenum target, GLuint framebuffer) {
    glBindFramebuffer(target, framebuffer);
}
GL_API void GL_APIENTRY glesBindRenderbuffer (GLenum target, GLuint renderbuffer) {
    glBindRenderbuffer ( target, renderbuffer);
}

GL_API void GL_APIENTRY glesFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glFramebufferTexture2D (target, attachment, textarget, texture, level);
}

GL_API void GL_APIENTRY glesTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) {
    glTexImage2D (target, level, internalformat, width, height, border, format, type, pixels);
}

GL_API void GL_APIENTRY glesDeleteFramebuffers (GLsizei n, const GLuint* framebuffers) {
    glDeleteFramebuffers (n, framebuffers);
}
GL_API void GL_APIENTRY glesDeleteProgram (GLuint program) {
    glDeleteProgram (program);
}
GL_API void GL_APIENTRY glesDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers) {
    glDeleteRenderbuffers (n, renderbuffers);
}

GL_API void GL_APIENTRY glesViewport (GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
}

GL_API void GL_APIENTRY glesVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr) {
    glVertexAttribPointer (indx, size, type, normalized, stride, ptr);
}

GL_API void GL_APIENTRY glesUniform1i (GLint location, GLint x) {
    glUniform1i ( location,  x);
}

GL_API void GL_APIENTRY glesDisableVertexAttribArray (GLuint index) {
    glDisableVertexAttribArray ( index);
}
GL_API void GL_APIENTRY glesDrawArrays (GLenum mode, GLint first, GLsizei count) {
    glDrawArrays ( mode, first, count);
}
GL_API void GL_APIENTRY glesDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices) {
    glDrawElements(mode, count, type, indices);
}

GL_API void GL_APIENTRY glesActiveTexture (GLenum texture) {
    glActiveTexture (texture);
}
GL_API void GL_APIENTRY glesAttachShader (GLuint program, GLuint shader) {
    glAttachShader ( program,  shader);
}

GL_API GLenum GL_APIENTRY glesCheckFramebufferStatus (GLenum target) {
    return glCheckFramebufferStatus ( target);
}

GL_API void GL_APIENTRY glesClear (GLbitfield mask) {
    glClear ( mask);
}
GL_API void GL_APIENTRY glesClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glClearColor ( red, green, blue, alpha);
}

GL_API GLuint GL_APIENTRY glesCreateProgram (void) {
    return glCreateProgram();
}
GL_API GLuint GL_APIENTRY glesCreateShader (GLenum type) {
    return glCreateShader(type);
}

GL_API void GL_APIENTRY glesLinkProgram (GLuint program) {
    glLinkProgram(program);
}

GL_API void GL_APIENTRY glesDeleteShader (GLuint shader) {
    glDeleteShader(shader);
}

GL_API GLenum GL_APIENTRY glesGetError (void) {
    return glGetError();
}

GL_API void GL_APIENTRY glesGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog) {
    glGetProgramInfoLog ( program,  bufsize,  length,  infolog) ;
}

GL_API void GL_APIENTRY glesGetProgramiv (GLuint program, GLenum pname, GLint* params) {
    glGetProgramiv ( program, pname, params);
}
#pragma clang diagnostic pop
