#pragma once

#include "ofxiOS.h"
#include "ofxScrollView.h"
#include "Grid.h"

class ofApp : public ofxiOSApp {
	
public:

    void setup();
    void update();
    void draw();
    void exit();
	
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
    coc::Rect windowRect;
    coc::Rect contentRect;
    ofxScrollView scrollView;
    
    Grid grid;
    ofTexture image;
    
    ofVec2f touchPoint;
    float touchTime = 0.0;

};


