#pragma once

#include "ofMain.h"
#include "ofxScrollView.h"
#include "Grid.h"

class ofApp : public ofBaseApp{
    
public:

    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    coc::Rect screenRect;
    coc::Rect windowRect;
    coc::Rect contentRect;
    ofxScrollView scrollView;
    
    Grid grid;
    
    ofVec2f touchPoint;
    float touchTime = 0.0;
};
