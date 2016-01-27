//
//  ofxScrollView.h
//  Created by Lukasz Karluk on 27/01/2016.
//  http://codeoncanvas.cc
//

#pragma once

#if defined( COC_OF )

#include "cocScrollView.h"

class ofMouseEventArgs;
class ofTouchEventArgs;

class ofxScrollView : public coc::ScrollView {

public:

    ofxScrollView();

    void begin();
    void end();

    void mouseMoved(ofMouseEventArgs & mouse);
    void mouseDragged(ofMouseEventArgs & mouse);
    void mousePressed(ofMouseEventArgs & mouse);
    void mouseReleased(ofMouseEventArgs & mouse);
    
    void touchDown(ofTouchEventArgs &touch);
    void touchMoved(ofTouchEventArgs &touch);
    void touchUp(ofTouchEventArgs &touch);
    void touchDoubleTap(ofTouchEventArgs &touch);
    void touchCancelled(ofTouchEventArgs &touch);
    
protected:

    void setUserInteractionOn();
    void setUserInteractionOff();
    
};

#endif