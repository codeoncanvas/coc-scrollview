//
//  ofxScrollView.cpp
//  Created by Lukasz Karluk on 27/01/2016.
//  http://codeoncanvas.cc
//

#include "ofxScrollView.h"

#if defined( COC_OF )

#include "ofGraphics.h"
#include "ofEvents.h"

ofxScrollView::ofxScrollView() : ScrollView() {
#ifdef TARGET_OPENGLES
    bPinchZoomSupported = true;
#endif
}

//----------------------------------------------------------
void ofxScrollView::begin() {
    ofMatrix4x4 mat(getMatrixPtr());
    ofPushMatrix();
    ofMultMatrix(mat);
}

void ofxScrollView::end() {
    ofPopMatrix();
}

//----------------------------------------------------------
void ofxScrollView::mouseMoved(ofMouseEventArgs & mouse) {
    ScrollView::mouseMoved(mouse.x, mouse.y);
}

void ofxScrollView::mouseDragged(ofMouseEventArgs & mouse) {
    ScrollView::mouseDragged(mouse.x, mouse.y, mouse.button);
}

void ofxScrollView::mousePressed(ofMouseEventArgs & mouse) {
    ScrollView::mousePressed(mouse.x, mouse.y, mouse.button);
}

void ofxScrollView::mouseReleased(ofMouseEventArgs & mouse) {
    ScrollView::mouseReleased(mouse.x, mouse.y, mouse.button);
}

//----------------------------------------------------------
void ofxScrollView::touchDown(ofTouchEventArgs &touch) {
    ScrollView::touchDown(touch.x, touch.y, touch.id);
}

void ofxScrollView::touchMoved(ofTouchEventArgs &touch) {
    ScrollView::touchMoved(touch.x, touch.y, touch.id);
}

void ofxScrollView::touchUp(ofTouchEventArgs &touch) {
    ScrollView::touchUp(touch.x, touch.y, touch.id);
}

void ofxScrollView::touchDoubleTap(ofTouchEventArgs &touch) {
    ScrollView::touchDoubleTap(touch.x, touch.y, touch.id);
}

void ofxScrollView::touchCancelled(ofTouchEventArgs &touch) {
    ScrollView::touchCancelled(touch.x, touch.y, touch.id);
}

//----------------------------------------------------------
void ofxScrollView::setUserInteractionOn() {
#ifdef TARGET_OPENGLES

    ofAddListener(ofEvents().touchDown, this, &ofxScrollView::touchDown);
    ofAddListener(ofEvents().touchMoved, this, &ofxScrollView::touchMoved);
    ofAddListener(ofEvents().touchUp, this, &ofxScrollView::touchUp);
    
#else

    ofAddListener(ofEvents().mousePressed, this, &ofxScrollView::mousePressed);
    ofAddListener(ofEvents().mouseDragged, this, &ofxScrollView::mouseDragged);
    ofAddListener(ofEvents().mouseReleased, this, &ofxScrollView::mouseReleased);
    
#endif
}

void ofxScrollView::setUserInteractionOff() {
#ifdef TARGET_OPENGLES

    ofRemoveListener(ofEvents().touchDown, this, &ofxScrollView::touchDown);
    ofRemoveListener(ofEvents().touchMoved, this, &ofxScrollView::touchMoved);
    ofRemoveListener(ofEvents().touchUp, this, &ofxScrollView::touchUp);
    
#else

    ofRemoveListener(ofEvents().mousePressed, this, &ofxScrollView::mousePressed);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxScrollView::mouseDragged);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxScrollView::mouseReleased);
    
#endif
}

#endif