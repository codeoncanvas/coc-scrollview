//
//  ScrollView.h
//  Created by Lukasz Karluk on 2/06/2014.
//  http://codeoncanvas.cc
//

#pragma once

#include "cocCore.h"

namespace coc {

//--------------------------------------------------------------
class ScrollViewTouchPoint {
public:
    ScrollViewTouchPoint() {
        touchID = 0;
        touchDownTimeInSec = 0;
    }
    int touchID;
    glm::vec2 touchPos;
    float touchDownTimeInSec;
};

//--------------------------------------------------------------
class ScrollView {
    
public:
    
    ScrollView();
    ~ScrollView();
    
    void setUserInteraction(bool bEnable);
    bool getUserInteraction();
    void setPinchZoom(bool bEnable);
    void setScrollEasing(float value);
    void setBounceBack(float value);
    void setDragVelocityDecay(float value);
    void setDoubleTapZoom(bool bEnable);
    void setDoubleTapZoomRangeMin(float value);
    void setDoubleTapZoomRangeMax(float value);
    void setDoubleTapZoomIncrement(float value);
    void setDoubleTapZoomIncrementTimeInSec(float value);
    void setDoubleTapRegistrationTimeInSec(float value);
    void setDoubleTapRegistrationDistanceInPixels(float value);

    virtual void setup();
    virtual void reset();
    
    void setWindowRect(const coc::Rect & rect);
    void setContentRect(const coc::Rect & rect);
    
    void fitContentToWindow(cocAspectRatioMode aspectRatioMode);

    void setScale(float value);
    void setScaleMin(float value);
    void setScaleMax(float value);
    
    float getScale();
    float getScaleMin();
    float getScaleMax();
    
    void setZoom(float value);
    float getZoom();
    bool isZoomed();
    bool isZoomedInMax();
    bool isZoomedOutMax();
    
    float zoomToScale(float value);
    float scaleToZoom(float value);

    void zoomToMin(const glm::vec2 & screenPoint, float timeSec=0.0);
    void zoomToMax(const glm::vec2 & screenPoint, float timeSec=0.0);
    void zoomTo(const glm::vec2 & screenPoint, float zoom, float timeSec=0.0);
    void zoomToContentPointAndPositionAtScreenPoint(const glm::vec2 & contentPoint,
                                                    const glm::vec2 & screenPoint,
                                                    float zoom,
                                                    float timeSec=0.0);
    void moveContentPointToScreenPoint(const glm::vec2 & contentPoint,
                                       const glm::vec2 & screenPoint,
                                       float timeSec=0.0);
    bool animStart(float animTimeInSec);
    
    void setScrollPositionX(float x, bool bEase=true);
    void setScrollPositionY(float y, bool bEase=true);
    void setScrollPosition(float x, float y, bool bEase=true);
    
    glm::vec2 getScrollPosition();
    glm::vec2 getScrollPositionNorm();
    
    const coc::Rect & getWindowRect();
    const coc::Rect & getContentRect();
    const coc::Rect & getScrollRect();
    const glm::mat4x4 & getMatrix();
    const float * getMatrixPtr();
    
    virtual void update();

    //-------------------------------------------------------------- the brains!
    coc::Rect getRectContainedInWindowRect(const coc::Rect & rect,
                                             float easing=1.0);
    
    coc::Rect getRectZoomedAtScreenPoint(const coc::Rect & rect,
                                           const glm::vec2 & screenPoint,
                                           float zoom=0.0);
    
    coc::Rect getRectWithContentPointAtScreenPoint(const coc::Rect & rect,
                                                     const glm::vec2 & contentPoint,
                                                     const glm::vec2 & screenPoint);
    
    glm::mat4x4 getMatrixForRect(const coc::Rect & rect);

    glm::vec2 getContentPointAtScreenPoint(const glm::vec2 & screenPoint);
    
    glm::vec2 getContentPointAtScreenPoint(const coc::Rect & rect,
                                         const glm::vec2 & screenPoint);
    
    glm::vec2 getScreenPointAtContentPoint(const coc::Rect & rect,
                                         const glm::vec2 & contentPoint);

    //--------------------------------------------------------------

    virtual void dragDown(const glm::vec2 & point);
    virtual void dragMoved(const glm::vec2 & point);
    virtual void dragUp(const glm::vec2 & point);
    virtual void dragCancel();
    
    virtual void zoomDown(const glm::vec2 & point, float pointDist);
    virtual void zoomMoved(const glm::vec2 & point, float pointDist);
    virtual void zoomUp(const glm::vec2 & point, float pointDist);
    virtual void zoomCancel();
    
    coc::Rect windowRect;
    coc::Rect contentRect;
    
    bool bUserInteractionEnabled;
    bool bPinchZoomEnabled;
    bool bPinchZoomSupported;

    coc::Rect scrollRect;
    coc::Rect scrollRectEased;
    coc::Rect scrollRectAnim0;
    coc::Rect scrollRectAnim1;
    float scrollEasing;
    float bounceBack;
    
    glm::vec2 dragDownPos;
    glm::vec2 dragMovePos;
    glm::vec2 dragMovePosPrev;
    glm::vec2 dragVel;
    float dragVelDecay;
    bool bDragging;
    
    glm::vec2 zoomDownPos;
    glm::vec2 zoomMovePos;
    glm::vec2 zoomMovePosPrev;
    float zoomDownDist;
    float zoomMoveDist;
    bool bZooming;
    
    float animTimeStart;
    float animTimeTotal;
    bool bAnimating;

    bool bDoubleTapZoomEnabled;
    float doubleTapZoomRangeMin;
    float doubleTapZoomRangeMax;
    float doubleTapZoomIncrement;
    float doubleTapZoomIncrementTimeInSec;
    float doubleTapRegistrationTimeInSec;
    float doubleTapRegistrationDistanceInPixels;
    
    float scale;
    float scaleDown;
    float scaleMin;
    float scaleMax;
    glm::mat4x4 mat;
    
    std::vector<ScrollViewTouchPoint> touchPoints;
    ScrollViewTouchPoint touchDownPointLast;
    
    //----------------------------------------------------------
    virtual void mouseMoved(int x, int y);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    
    //----------------------------------------------------------
    virtual void touchDown(int x, int y, int id);
    virtual void touchMoved(int x, int y, int id);
    virtual void touchUp(int x, int y, int id);
    virtual void touchDoubleTap(int x, int y, int id);
    virtual void touchCancelled(int x, int y, int id);
    
    //----------------------------------------------------------
    
protected:
    
    virtual void setUserInteractionOn() {
        // override - this is specific to Cinder, OpenFrameworks, etc.
    }

    virtual void setUserInteractionOff() {
        // override - this is specific to Cinder, OpenFrameworks, etc.
    }
};

}