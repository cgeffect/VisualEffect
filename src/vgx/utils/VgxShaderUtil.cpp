//
//  CGShaderUtil.h
//  Vgx
//
//  Created by Jason on 2021/6/23.
//
#include <cstring>
#include "VgxShaderUtil.h"
#include "VgxLog.h"
#include "VgxInterface.h"
#include <iostream>

int CG_LOG_LEVEL = 4;

using namespace vgx;

void VgxShaderUtil::setLogLevel(int level) {
    CG_LOG_LEVEL = level;
}
GLuint VgxShaderUtil::loadShader(GLenum type, const GLchar *source) {
    GLuint shader = glesCreateShader(type);

    if (shader != 0 && source != NULL) {
        GLint length = (GLint)strlen(source);
        glShaderSource(shader, 1, &source, &length);
        glCompileShader(shader);
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled == 0) {
            printf("glError: Could not compile shader %d:\n %s", type, source);
            char temp[512] = {0};
            GLsizei length;
            glGetShaderInfoLog(shader, 512, &length, temp);
            printf("glError %s", temp);
            glesDeleteShader(shader);
            shader = 0;

        }
    }
    return shader;
}

GLuint VgxShaderUtil::createProgram(const GLchar *vertexSource, const GLchar *fragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    glCheckError("loadShader GL_VERTEX_SHADER");

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    glCheckError("loadShader GL_FRAGMENT_SHADER");

    GLuint program = glesCreateProgram();
    if (program != 0) {
        glesAttachShader(program, vertexShader);
        glCheckError("glAttachShader");
        glesAttachShader(program, pixelShader);
        glCheckError("glAttachShader");
        glesLinkProgram(program);
        GLint linkStatus;
        glesGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            printf("glError: Could not link program: ");
            char temp[512] = {0};
            GLsizei length;
            glesGetProgramInfoLog(program, 512, &length, temp);
            printf("glError %s", temp);
            glesDeleteProgram(program);
            program = 0;
        }
        glesDeleteShader(vertexShader);
        glesDeleteShader(pixelShader);
    }
    return program;
}

GLuint VgxShaderUtil::genTexture() {
    GLuint tid;
    glesGenTextures(1, &tid);
    glesBindTexture(GL_TEXTURE_2D, tid);
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glesBindTexture(GL_TEXTURE_2D, 0);
    return tid;
}

GLuint VgxShaderUtil::genTexture(int w, int h, GLenum f) {
    if(w * h <= 0) {
        return TEXTURE_NULL;
    }
    GLuint tid;
    glesGenTextures(1, &tid);
    if (tid > TEXTURE_NULL) {
        glesBindTexture(GL_TEXTURE_2D, tid);
        glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glesTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glesTexImage2D(GL_TEXTURE_2D, 0, f, w, h, 0, f, GL_UNSIGNED_BYTE, 0);
        glesBindTexture(GL_TEXTURE_2D, 0);
    }
    return tid;
}


GLuint VgxShaderUtil::genTexture(void *data, int w, int h) {
    GLuint tid;
    glesGenTextures(1, (GLuint *) &tid);
    glesBindTexture(GL_TEXTURE_2D, (GLuint) tid);
    glesTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glesTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glesTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glesTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glesTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    return tid;
}

void VgxShaderUtil::glCheckError(const char *flag) {
    GLenum error;
    while ((error = glesGetError()) != GL_NO_ERROR) {
        switch (error) {
            case GL_NO_ERROR:
                printf("GL_NO_ERROR: gl success\n");
                break;
            case GL_INVALID_ENUM:
                printf("GL_INVALID_ENUM: 为枚举参数指定了不可接受的值\n");
                break;
            case GL_INVALID_VALUE:
                printf("GL_INVALID_VALUE: 数字参数超出范围\n");
                break;
            case GL_INVALID_OPERATION:
                printf("GL_INVALID_OPERATION: 当前状态下不允许指定的操作\n");
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                printf("GL_INVALID_FRAMEBUFFER_OPERATION: 该命令试图渲染到帧缓冲区或从帧缓冲区读取，而当前绑定的帧缓冲区不是帧缓冲区完成状态, 即glCheckFramebufferStatus的返回值不是GL_FRAMEBUFFER_COMPLETE\n");
                break;
            case GL_OUT_OF_MEMORY:
                printf("GL_OUT_OF_MEMORY: 没有足够的内存来执行命令。 在记录此错误之后，GL的状态是未定义的，除了错误标志的状态。\n");
                break;
            default:
                printf("其他gl错误\n");
                break;
        }
        printf("%s: glError: 0x%X\n", flag, error);
    }
}
