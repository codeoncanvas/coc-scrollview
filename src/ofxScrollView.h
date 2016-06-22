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
