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

namespace coc {
 
using namespace ci;
using namespace ci::app;
using namespace std;

ciScrollView::ciScrollView() : ScrollView() {
#ifdef CINDER_COCOA_TOUCH
	bPinchZoomSupported = false;
#endif
}

//----------------------------------------------------------
void ciScrollView::begin() {
	gl::pushModelMatrix();
	gl::multModelMatrix(getMatrix());
    
}

void ciScrollView::end() {
	gl::popModelMatrix();
}

//----------------------------------------------------------
void ciScrollView::mouseMoved(MouseEvent & mouse) {
	ScrollView::mouseMoved(mouse.getPos().x, mouse.getPos().y);
}

void ciScrollView::mouseDragged(MouseEvent & mouse) {
    
    if (mouse.isRightDown()) {
        ScrollView::mouseDragged(mouse.getPos().x, mouse.getPos().y, 2);
    }
    else {
        ScrollView::mouseDragged(mouse.getPos().x, mouse.getPos().y, 0);
    }
}

void ciScrollView::mousePressed(MouseEvent & mouse) {
    if (mouse.isRightDown()) {
        ScrollView::mousePressed(mouse.getPos().x, mouse.getPos().y, 2);
    }
    else {
      ScrollView::mousePressed(mouse.getPos().x, mouse.getPos().y, 0);
    }
	
}

void ciScrollView::mouseReleased(MouseEvent & mouse) {
    
    if (mouse.isRightDown()) {
        ScrollView::mouseReleased(mouse.getPos().x, mouse.getPos().y, 2);
    }
    else {
        ScrollView::mouseReleased(mouse.getPos().x, mouse.getPos().y, 0);
    }
}


//----------------------------------------------------------
void ciScrollView::setUserInteractionOn() {

	cbMouseDown = getWindow()->getSignalMouseDown().connect( std::bind( &ciScrollView::mousePressed, this, std::placeholders::_1 ) );
	cbMouseDrag = getWindow()->getSignalMouseDrag().connect( std::bind( &ciScrollView::mouseDragged, this, std::placeholders::_1 ) );
	cbMouseUp = getWindow()->getSignalMouseUp().connect( std::bind( &ciScrollView::mouseReleased, this, std::placeholders::_1 ) );
}

void ciScrollView::setUserInteractionOff() {

	cbMouseDown.disconnect();
	cbMouseDrag.disconnect();
	cbMouseUp.disconnect();

}

}//namespace coc

#endif