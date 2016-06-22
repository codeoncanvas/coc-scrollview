/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

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
