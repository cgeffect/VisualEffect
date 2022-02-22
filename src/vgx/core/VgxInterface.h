//
//  VgxInterface.hpp
//  VisualEffect
//
//  Created by Jason on 2022/2/18.
//

#ifndef VgxInterface_hpp
#define VgxInterface_hpp
#include "CGOpenGL.h"

void glesEnableVertexAttribArray(GLuint index);
void glesGenTextures (GLsizei n, GLuint* textures);
void glesBindTexture (GLenum target, GLuint texture);
void glesTexParameteri (GLenum target, GLenum pname, GLint param);
void glesGenFramebuffers (GLsizei n, GLuint* framebuffers);
void glesGenRenderbuffers (GLsizei n, GLuint* renderbuffers);
void glesBindFramebuffer (GLenum target, GLuint framebuffer);
void glesBindRenderbuffer (GLenum target, GLuint renderbuffer);
void glesFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void glesTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);

#endif /* VgxInterface_hpp */
