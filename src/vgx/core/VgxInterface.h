//
//  VgxInterface.hpp
//  VisualEffect
//
//  Created by Jason on 2022/2/18.
//

#ifndef VgxInterface_hpp
#define VgxInterface_hpp

#include "VgxGL.h"

GL_API void GL_APIENTRY glesEnableVertexAttribArray(GLuint index);
GL_API void GL_APIENTRY glesGenTextures (GLsizei n, GLuint* textures);
GL_API void GL_APIENTRY glesBindTexture (GLenum target, GLuint texture);
GL_API void GL_APIENTRY glesTexParameteri (GLenum target, GLenum pname, GLint param);
GL_API void GL_APIENTRY glesTexParameterf (GLenum target, GLenum pname, GLint param);
GL_API void GL_APIENTRY glesGenFramebuffers (GLsizei n, GLuint* framebuffers);
GL_API void GL_APIENTRY glesGenRenderbuffers (GLsizei n, GLuint* renderbuffers);
GL_API void GL_APIENTRY glesBindFramebuffer (GLenum target, GLuint framebuffer);
GL_API void GL_APIENTRY glesBindRenderbuffer (GLenum target, GLuint renderbuffer);
GL_API void GL_APIENTRY glesFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GL_API void GL_APIENTRY glesTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
GL_API void GL_APIENTRY glesDeleteFramebuffers (GLsizei n, const GLuint* framebuffers);
GL_API void GL_APIENTRY glesDeleteProgram (GLuint program);
GL_API void GL_APIENTRY glesDeleteRenderbuffers (GLsizei n, const GLuint* renderbuffers);
GL_API void GL_APIENTRY glesViewport (GLint x, GLint y, GLsizei width, GLsizei height);
GL_API void GL_APIENTRY glesVertexAttribPointer (GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
GL_API void GL_APIENTRY glesUniform1i (GLint location, GLint x);
GL_API void GL_APIENTRY glesDisableVertexAttribArray (GLuint index);
GL_API void GL_APIENTRY glesDrawArrays (GLenum mode, GLint first, GLsizei count);
GL_API void GL_APIENTRY glesDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
GL_API void GL_APIENTRY glesActiveTexture (GLenum texture);
GL_API void GL_APIENTRY glesAttachShader (GLuint program, GLuint shader);
GL_API GLenum GL_APIENTRY glesCheckFramebufferStatus (GLenum target)   ;
GL_API void GL_APIENTRY glesClear (GLbitfield mask);
GL_API void GL_APIENTRY glesClearColor (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
GL_API GLuint GL_APIENTRY glesCreateProgram (void);
GL_API GLuint GL_APIENTRY glesCreateShader (GLenum type);
GL_API void GL_APIENTRY glesLinkProgram (GLuint program);
GL_API void GL_APIENTRY glesDeleteShader (GLuint shader);
GL_API GLenum GL_APIENTRY glesGetError (void);
GL_API void GL_APIENTRY glesGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
GL_API void GL_APIENTRY glesGetProgramiv (GLuint program, GLenum pname, GLint* params);

#endif /* VgxInterface_hpp */
