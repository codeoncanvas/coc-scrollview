//
//  ScrollView.h
//  Created by Lukasz Karluk on 2/06/2014.
//  http://codeoncanvas.cc
//

#pragma once

#include "cocCore.h"
#include "cocButton.h"

namespace coc {

//--------------------------------------------------------------
class ScrollView;
typedef std::shared_ptr<ScrollView> ScrollViewRef;

class ScrollView {
    
public:

    //----------------------------------------------------------
    class Button;
    typedef std::shared_ptr<Button> ButtonRef;
    
    class Button {
    public:
        static ButtonRef create() { return ButtonRef(new Button()); }
    
        Button():
        timeSinceLastPress(0),
        posOfLastPress(0, 0),
        bDoubleTapOnLastPress(false) {
            //
        }
        
        coc::ButtonRef button;
        float timeSinceLastPress;
        glm::vec2 posOfLastPress;
        bool bDoubleTapOnLastPress;
    };

    //----------------------------------------------------------
    class Action;
    typedef std::shared_ptr<Action> ActionRef;
    
    class Action {
    public:
        static ActionRef create() { return ActionRef(new Action()); }
        
        enum Type {
            WindowFit=0,
            WindowFill,
            ScrollPosition,
            DoubleTapZoom
        };
        
        Action():
        time(0),
        timeTotal(0),
        progress(0) {
            //
        }

        Type type;
        glm::vec2 scrollStartPos;
        glm::vec2 scrollStartSize;
        glm::vec2 scrollFinishPos;
        glm::vec2 scrollFinishSize;
        glm::vec2 windowHitPoint;
        glm::vec2 scrollPositionNormalized;
        float time;
        float timeTotal;
        float progress;
    };

    //----------------------------------------------------------
    ScrollView();
    ~ScrollView();
    
    static ScrollViewRef create() { return ScrollViewRef(new ScrollView()); }
    
    virtual coc::ButtonRef initButton() const { return coc::Button::create(); }

    void setWindowPos(const glm::vec2 & value);
    void setWindowSize(const glm::vec2 & value);
    void setWindowRect(const coc::Rect & value);
    const glm::vec2 & getWindowPos() const;
    const glm::vec2 & getWindowSize() const;
    coc::Rect getWindowRect() const;
    float getWindowDiagonal() const;
    
    void setContentPos(const glm::vec2 & value);
    void setContentSize(const glm::vec2 & value);
    void setContentRect(const coc::Rect & value);
    const glm::vec2 & getContentPos() const;
    const glm::vec2 & getContentSize() const;
    coc::Rect getContentRect() const;
    float getContentDiagonal() const;
    glm::vec2 getContentPointAtScreenPoint(const glm::vec2 & screenPoint) const;
    glm::vec2 getContentPointAtWindowPoint(const glm::vec2 & windowPoint) const;
    
    void setScrollToFitWindow(float time=0);
    void setScrollToFillWindow(float time=0);
    void setScrollPositionNormalized(const glm::vec2 & value, float time=0);
    const glm::vec2 & getScrollPos() const;
    const glm::vec2 & getScrollSize() const;
    coc::Rect getScrollRect() const;
    glm::vec2 getScrollBoundsUpperLeft() const;
    glm::vec2 getScrollBoundsUpperLeft(const glm::vec2 & scrollSize) const;
    glm::vec2 getScrollBoundsLowerRight() const;
    glm::vec2 getScrollBoundsLowerRight(const glm::vec2 & scrollSize) const;
    glm::vec2 getScrollPositionNormalized() const;
    
    void setMaxNumOfTouchPoints(unsigned int value) { numOfButtons = value; }
    
    void setDragVelocityDecay(float value);
    void setDragVelocityDecay(const glm::vec2 & value);
    const glm::vec2 & getDragVelocityDecay() const;
    
    void setDragBoundsLimit(float value);
    void setDragBoundsLimit(const glm::vec2 & value);
    const glm::vec2 & getDragBoundsLimit() const;
    
    void setScrollEasing(float value);
    void setScrollEasing(const glm::vec2 & value);
    const glm::vec2 & getScrollEasing() const;
    
    void setBounceEasing(float value);
    void setBounceEasing(const glm::vec2 & value);
    const glm::vec2 & getBounceEasing() const;
    
    void setEnabled(bool value);
    bool getEnabled() const;
    
    void setDoubleTapEnabled(bool value);
    bool getDoubleTapEnabled() const;
    
    void setDoubleTapTimeLimit(float value);
    float getDoubleTapTimeLimit() const;
    
    void setDoubleTapDistLimit(float value);
    float getDoubleTapDistLimit() const;
    
    void setDoubleTapZoomRate(float value);
    float getDoubleTapZoomRate() const;
    
    const glm::mat4x4 & getModelMatrix() const;
    const float * getModelMatrixPtr() const;
    
    //----------------------------------------------------------
    virtual void setup();
    
    virtual void update(float timeDelta=0);
    
    virtual void draw() const {}

    //----------------------------------------------------------
	virtual void pointMoved(int x, int y, unsigned int pointID);
    virtual void pointPressed(int x, int y, unsigned int pointID);
	virtual void pointDragged(int x, int y, unsigned int pointID);
	virtual void pointReleased(int x, int y, unsigned int pointID);
    virtual void pointNew(ButtonPoint::Type type, int x, int y, unsigned int pointID);
    
protected:

	virtual void begin() {}
	virtual void end() {}
    
    unsigned int numOfButtons;
    std::vector<ButtonRef> buttons;
    ButtonRef buttonDrag;
    ButtonRef buttonDoubleTap;
    bool bEnabled;
    bool bEnabledChanged;
    
    glm::vec2 windowPos;
    glm::vec2 windowSize;
    bool bWindowPosChanged;
    bool bWindowSizeChanged;
    
    glm::vec2 contentPos;
    glm::vec2 contentSize;
    bool bContentPosChanged;
    bool bContentSizeChanged;
    
    glm::vec2 scrollPos;
    glm::vec2 scrollSize;
    
    std::vector<ActionRef> actions;
    ActionRef action;

    glm::vec2 dragScrollPos;
    glm::vec2 dragDownPos;
    glm::vec2 dragMovePos;
    glm::vec2 dragMovePosPrev;
    glm::vec2 dragDist;
    glm::vec2 dragVel;
    glm::vec2 dragVelDecay;
    glm::vec2 dragBoundsLimit;
    
    glm::vec2 scrollEasing;
    glm::vec2 bounceEasing;
    
    bool bDoubleTapEnabled;
    float doubleTapTimeLimit;
    float doubleTapDistLimit;
    float doubleTapZoomRate;
    
    glm::mat4 modelMatrix;
    
};

}