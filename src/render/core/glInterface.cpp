//
//  glInterface.cpp
//  VisualEffect
//
//  Created by Jason on 2022/2/18.
//

#include "glInterface.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void glesEnableVertexAttribArray(GLuint index) {
    glEnableVertexAttribArray(index);
}

#pragma clang diagnostic pop
