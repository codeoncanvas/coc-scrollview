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

#pragma once

#ifdef COC_CI

#include "cocScrollView.h"
#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

namespace coc {

class ciScrollView : public coc::ScrollView {

public:

	ciScrollView();

	void begin();
	void end();

	void mouseMoved(ci::app::MouseEvent & mouse);
	void mouseDragged(ci::app::MouseEvent & mouse);
	void mousePressed(ci::app::MouseEvent & mouse);
	void mouseReleased(ci::app::MouseEvent & mouse);

#ifdef CINDER_COCOA_TOUCH
	//todo: touch events
#endif

protected:

	void setUserInteractionOn();
	void setUserInteractionOff();

	ci::signals::ScopedConnection  cbMouseDown, cbMouseDrag, cbMouseUp;

};//class ciScrollView

}//namespace coc

#endif


