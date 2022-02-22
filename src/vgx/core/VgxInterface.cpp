//
//  VgxInterface.cpp
//  VisualEffect
//
//  Created by Jason on 2022/2/18.
//

#include "VgxInterface.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void glesEnableVertexAttribArray(GLuint index) {
    glEnableVertexAttribArray(index);
}

void glesGenTextures (GLsizei n, GLuint* textures) {
    glGenTextures(n, textures);
}

void glesBindTexture (GLenum target, GLuint texture) {
    glBindTexture (target, texture);
}

void glesTexParameteri (GLenum target, GLenum pname, GLint param) {
    glTexParameteri(target, pname, param);
}

void glesGenFramebuffers (GLsizei n, GLuint* framebuffers) {
    glGenFramebuffers (n, framebuffers);
}
void glesGenRenderbuffers (GLsizei n, GLuint* renderbuffers) {
    glGenRenderbuffers ( n, renderbuffers);
}

void glesBindFramebuffer (GLenum target, GLuint framebuffer) {
    glBindFramebuffer(target, framebuffer);
}
void glesBindRenderbuffer (GLenum target, GLuint renderbuffer) {
    glBindRenderbuffer ( target, renderbuffer);
}

void glesFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glFramebufferTexture2D (target, attachment, textarget, texture, level);
}

void glesTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels) {
    glTexImage2D (target, level, internalformat, width, height, border, format, type, pixels);

}

void glesDeleteFramebuffers (GLsizei n, const GLuint* framebuffers) {
    glDeleteFramebuffers (n, framebuffers);
}
void glesDeleteProgram (GLuint program) {
    glDeleteProgram (program);
}
void glesDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers) {
    glDeleteRenderbuffers (n, renderbuffers);
}


#pragma clang diagnostic pop
