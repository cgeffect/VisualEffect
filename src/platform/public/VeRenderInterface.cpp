//
//  VeRenderInterface.cpp
//  libVisualEffect
//
//  Created by Jason on 2022/2/20.
//

#include "VeRenderInterface.h"

#include "VgxFramebuffer.h"
#include "VgxFilter.h"
#include "VgxDataInput.h"
#include "VgxTextureOutput.h"
#include "VgxDataInput.h"

using namespace vgx;

int setData1(unsigned const char *data, int width, int height) {

    auto _dataInput = new VgxDataInput();
    auto _filter = new VgxFilter();
    auto _output = new VgxTextureOutput();

    _dataInput->setInputData(data, width, height);
    _dataInput->addTarget(_filter);
    _filter->addTarget(_output);
    _dataInput->requestRender();
    int texId = _output->getTexId();
    return texId;
}
