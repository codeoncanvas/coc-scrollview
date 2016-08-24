//
//  ScrollView.h
//  Created by Lukasz Karluk on 2/06/2014.
//  http://codeoncanvas.cc
//

#pragma once

#include "cocCore.h"
#include "cocButton.h"

namespace coc {

class ScrollView;
typedef std::shared_ptr<ScrollView> ScrollViewRef;

class ScrollView {
    
public:
    
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
    
    void setContentSize(const glm::vec2 & value);
    void setContentRect(const coc::Rect & value);
    const glm::vec2 & getContentSize() const;
    
    void setMaxNumOfTouchPoints(unsigned int value) { numOfButtons = value; }
    
    void setDragVelocityDecay(float value);
    float getDragVelocityDecay() const;
    
    void setScrollEasing(float value);
    void setScrollEasing(const glm::vec2 & value);
    const glm::vec2 & getScrollEasing() const;
    
    void setBounceEasing(float value);
    void setBounceEasing(const glm::vec2 & value);
    const glm::vec2 & getBounceEasing() const;
    
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
    std::vector<coc::ButtonRef> buttons;
    
    glm::vec2 windowPos;
    glm::vec2 windowSize;
    bool bWindowPosChanged;
    bool bWindowSizeChanged;
    
    glm::vec2 contentPos;
    glm::vec2 contentSize;
    glm::vec2 contentInitSize;
    bool bContentSizeChanged;

    coc::ButtonRef dragButton;
    glm::vec2 dragDownPos;
    glm::vec2 dragMovePos;
    glm::vec2 dragMovePosPrev;
    glm::vec2 dragVel;
    float dragVelDecay;
    
    glm::vec2 scrollEasing;
    glm::vec2 bounceEasing;
    
    glm::mat4 modelMatrix;
    
};

}