//
//	    ┌─┐╔═╗┌┬┐┌─┐
//      │  ║ ║ ││├┤
//      └─┘╚═╝─┴┘└─┘
//	 ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
//	 │  ├─┤║║║└┐┌┘├─┤└─┐
//	 └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
//	http://codeoncanvas.cc
//
// Created by Rene Christen on 28/01/2016.
// Copyright (c) 2016, Code on Canvas Pty Ltd
//

#ifdef COC_CI

#include "ciScrollView.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace coc {
 
void ciScrollView::begin() {
	ci::gl::pushModelMatrix();
	ci::gl::multModelMatrix(getModelMatrix());
}

void ciScrollView::end() {
	ci::gl::popModelMatrix();
}

}

#endif