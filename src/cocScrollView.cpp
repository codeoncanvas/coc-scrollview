//
//  ScrollView.cpp
//  Created by Lukasz Karluk on 2/06/2014.
//  http://codeoncanvas.cc
//

#include "cocScrollView.h"

namespace coc {

//--------------------------------------------------------------
static float const kEasingStop = 0.001;

//--------------------------------------------------------------
ScrollView::ScrollView() :
numOfButtons(10),
doubleTapTimeLimit(0.25),
doubleTapDistLimit(22),
doubleTapZoomRate(2.0),
bEnabled(true),
bEnabledChanged(false),
bWindowPosChanged(false),
bWindowSizeChanged(false),
bContentPosChanged(false),
bContentSizeChanged(false),
dragVelDecay(0.9, 0.9),
dragBoundsLimit(0.1, 0.1),
scrollEasing(1.0, 1.0),
bounceEasing(1.0, 1.0) {
    //
}

ScrollView::~ScrollView() {
    //
}

//--------------------------------------------------------------
void ScrollView::setWindowPos(const glm::vec2 & value) {
    bWindowPosChanged = (windowPos != value);
    windowPos = value;
}

void ScrollView::setWindowSize(const glm::vec2 & value) {
    bWindowSizeChanged = (windowSize != value);
    windowSize = value;
}

void ScrollView::setWindowRect(const coc::Rect & value) {
    setWindowPos(glm::vec2(value.getX(), value.getY()));
    setWindowSize(glm::vec2(value.getW(), value.getH()));
}

const glm::vec2 & ScrollView::getWindowPos() const {
    return windowPos;
}

const glm::vec2 & ScrollView::getWindowSize() const {
    return windowSize;
}

coc::Rect ScrollView::getWindowRect() const {
    coc::Rect rect;
    rect.setX(windowPos.x);
    rect.setY(windowPos.y);
    rect.setW(windowSize.x);
    rect.setH(windowSize.y);
    return rect;
}

float ScrollView::getWindowDiagonal() const {
    return glm::length(windowSize);
}

//--------------------------------------------------------------
void ScrollView::setContentPos(const glm::vec2 & value) {
    bContentPosChanged = (contentPos != value);
    contentPos = value;
}

void ScrollView::setContentSize(const glm::vec2 & value) {
    bContentSizeChanged = (contentSize != value);
    contentSize = value;
}

void ScrollView::setContentRect(const coc::Rect & value) {
    setContentSize(glm::vec2(value.getW(), value.getH()));
}

const glm::vec2 & ScrollView::getContentPos() const {
    return contentPos;
}

const glm::vec2 & ScrollView::getContentSize() const {
    return contentSize;
}

coc::Rect ScrollView::getContentRect() const {
    coc::Rect rect;
    rect.setX(contentPos.x);
    rect.setY(contentPos.y);
    rect.setW(contentSize.x);
    rect.setH(contentSize.y);
    return rect;
}

float ScrollView::getContentDiagonal() const {
    return glm::length(contentSize);
}

glm::vec2 ScrollView::getContentPointAtScreenPoint(const glm::vec2 & screenPoint) const {
    glm::vec2 windowPoint = screenPoint - windowPos;
    return getContentPointAtWindowPoint(windowPoint);
}

glm::vec2 ScrollView::getContentPointAtWindowPoint(const glm::vec2 & windowPoint) const {
    glm::vec2 contentPoint;
    contentPoint.x = coc::map(windowPoint.x, scrollPos.x, scrollPos.x + scrollSize.x, 0, contentSize.x, true);
    contentPoint.y = coc::map(windowPoint.y, scrollPos.y, scrollPos.y + scrollSize.y, 0, contentSize.y, true);
    return contentPoint;
}

//--------------------------------------------------------------
void ScrollView::setScrollToFitWindow(float time) {
    actions.push_back( Action::create() );
    actions.back()->type = Action::Type::WindowFit;
    actions.back()->timeTotal = time;
}

void ScrollView::setScrollToFillWindow(float time) {
    actions.push_back( Action::create() );
    actions.back()->type = Action::Type::WindowFill;
    actions.back()->timeTotal = time;
}

const glm::vec2 & ScrollView::getScrollPos() const {
    return scrollPos;
}

const glm::vec2 & ScrollView::getScrollSize() const {
    return scrollSize;
}

coc::Rect ScrollView::getScrollRect() const {
    coc::Rect rect;
    rect.setX(scrollPos.x);
    rect.setY(scrollPos.y);
    rect.setW(scrollSize.x);
    rect.setH(scrollSize.y);
    return rect;
}

//--------------------------------------------------------------
void ScrollView::setDragVelocityDecay(float value) {
    setDragVelocityDecay(glm::vec2(value, value));
}

void ScrollView::setDragVelocityDecay(const glm::vec2 & value) {
    dragVelDecay = value;
}

const glm::vec2 & ScrollView::getDragVelocityDecay() const {
    return dragVelDecay;
}

//--------------------------------------------------------------
void ScrollView::setDragBoundsLimit(float value) {
    setDragBoundsLimit(glm::vec2(value, value));
}

void ScrollView::setDragBoundsLimit(const glm::vec2 & value) {
    dragBoundsLimit = value;
}

const glm::vec2 & ScrollView::getDragBoundsLimit() const {
    return dragBoundsLimit;
}

//--------------------------------------------------------------
void ScrollView::setScrollEasing(float value) {
    setScrollEasing(glm::vec2(value, value));
}

void ScrollView::setScrollEasing(const glm::vec2 & value) {
    scrollEasing = value;
}

const glm::vec2 & ScrollView::getScrollEasing() const {
    return scrollEasing;
}

//--------------------------------------------------------------
void ScrollView::setBounceEasing(float value) {
    setBounceEasing(glm::vec2(value, value));
}

void ScrollView::setBounceEasing(const glm::vec2 & value) {
    bounceEasing = value;
}

const glm::vec2 & ScrollView::getBounceEasing() const {
    return bounceEasing;
}

//--------------------------------------------------------------
void ScrollView::setEnabled(bool value) {
    bEnabledChanged = bEnabled != value;
    bEnabled = value;
}

bool ScrollView::getEnabled() const {
    return bEnabled;
}

//--------------------------------------------------------------
void ScrollView::setDoubleTapTimeLimit(float value) {
    doubleTapTimeLimit = value;
}

float ScrollView::getDoubleTapTimeLimit() const {
    return doubleTapTimeLimit;
}

//--------------------------------------------------------------
void ScrollView::setDoubleTapDistLimit(float value) {
    doubleTapDistLimit = value;
}

float ScrollView::getDoubleTapDistLimit() const {
    return doubleTapDistLimit;
}

//--------------------------------------------------------------
void ScrollView::setDoubleTapZoomRate(float value) {
    doubleTapZoomRate = value;
}

float ScrollView::getDoubleTapZoomRate() const {
    return doubleTapZoomRate;
}

//--------------------------------------------------------------
const glm::mat4x4 & ScrollView::getModelMatrix() const {
    return modelMatrix;
}

const float * ScrollView::getModelMatrixPtr() const {
    return &modelMatrix[0][0];
}

//--------------------------------------------------------------
void ScrollView::setup() {
    //
}

//--------------------------------------------------------------
void ScrollView::update(float timeDelta) {

    coc::Rect contentRect = getContentRect();
    coc::Rect windowRect = getWindowRect();
    float windowDiagonal = getWindowDiagonal();
    
    bool bWindowChanged = false;
    bWindowChanged = bWindowChanged || bWindowPosChanged;
    bWindowChanged = bWindowChanged || bWindowSizeChanged;
    
    if(bContentSizeChanged) {
        
        // when content changes,
        // reset the scroll size and position to default.
    
        scrollSize = contentSize;
        scrollPos = glm::vec2(0, 0);
    }

    //---------------------------------------------------------- buttons.
    bool bNumOfButtonsChanged = (buttons.size() != numOfButtons);
    if(bNumOfButtonsChanged) {
        buttons.clear();
        for(int i=0; i<numOfButtons; i++) {
            buttons.push_back( Button::create() );
            buttons.back()->button = initButton();
        }
    }
    
    bool bUpdateButtonRect = false;
    bUpdateButtonRect = bUpdateButtonRect || bNumOfButtonsChanged;
    bUpdateButtonRect = bUpdateButtonRect || bWindowChanged;
    if(bUpdateButtonRect) {
        for(int i=0; i<buttons.size(); i++) {
            buttons[i]->button->setRect(windowRect);
        }
    }
    
    bool bUpdateButtonEnabled = false;
    bUpdateButtonEnabled = bUpdateButtonEnabled || bNumOfButtonsChanged;
    bUpdateButtonEnabled = bUpdateButtonEnabled || bEnabledChanged;
    if(bUpdateButtonEnabled) {
        for(int i=0; i<buttons.size(); i++) {
            buttons[i]->button->setEnabled(bEnabled);
            buttons[i]->button->reset();
        }
    }

    bool bDragging = false;
    bool bDragStart = false;
    bool bDragFinish = false;
    bool bDoubleTapStart = false;
    glm::vec2 buttonDragPos;
    glm::vec2 buttonDoubleTapPos;
    
    for(int i=0; i<buttons.size(); i++) {
        const ButtonRef & buttonRef = buttons[i];
        buttonRef->button->update();
        buttonRef->timeSinceLastPress += timeDelta;
        
        bool bPressed = buttonRef->button->pressedInside();
        if(bPressed) {

            float timeSinceLastPress = buttonRef->timeSinceLastPress;
            const glm::vec2 & posOfLastPress = buttonRef->posOfLastPress;
            const glm::vec2 & posOfThisPress = buttonRef->button->getPointPosLast();
            bool bDoubleTapOnLastPress = buttonRef->bDoubleTapOnLastPress;
            
            // double tap is registered when two quick presses are,
            // 1. within a close time period of one another.
            // 2. within a close position to one another.
            // bDoubleTapOnLastPress - prevents a double tap firing twice on 3 quick presses.
        
            bool bDoubleTap = true;
            bDoubleTap = bDoubleTap && (timeSinceLastPress < doubleTapTimeLimit);
            bDoubleTap = bDoubleTap && (glm::length(posOfThisPress - posOfLastPress) < doubleTapDistLimit);
            bDoubleTap = bDoubleTap && (bDoubleTapOnLastPress == false);
            
            buttonRef->timeSinceLastPress = 0;
            buttonRef->posOfLastPress = buttonRef->button->getPointPosLast();
            buttonRef->bDoubleTapOnLastPress = bDoubleTap;
            
            if(bDoubleTap) {
                buttonDoubleTap = buttonRef;
                bDoubleTapStart = true;
            } else {
                buttonDrag = buttonRef;
                bDragStart = true;
            }
        }
        
        bool bReleased = false;
        bReleased = bReleased || buttonRef->button->releasedInside();
        bReleased = bReleased || buttonRef->button->releasedOutside();
        if(bReleased) {
            if(buttonDrag == buttonRef) {
                bDragFinish = true;
            }
        }
    }
    
    bDragging = (buttonDrag != nullptr);
    if(bDragging) {
        buttonDragPos = buttonDrag->button->getPointPosLast();
        if(bDragFinish) {
            buttonDrag = nullptr;
        }
    }
    
    if(bDoubleTapStart) {
        buttonDoubleTapPos = buttonDoubleTap->button->getPointPosLast();
    }
    
    //---------------------------------------------------------- drag.
    if(bDragStart) {
        dragScrollPos = scrollPos;
        dragDownPos = dragMovePos = dragMovePosPrev = buttonDragPos;
        dragVel = glm::vec2(0, 0);
    }
    
    if(bDragging) {
        
        dragMovePosPrev = dragMovePos;
        dragMovePos = buttonDragPos;
        dragDist = dragMovePos - dragDownPos;
        dragVel = dragMovePos - dragMovePosPrev;
        
        scrollPos = dragScrollPos + dragDist;
        
    } else {
    
        dragVel *= dragVelDecay;
        if(coc::abs(dragVel.x) < kEasingStop) {
            dragVel.x = 0;
        }
        if(coc::abs(dragVel.y) < kEasingStop) {
            dragVel.y = 0;
        }
        
        scrollPos += dragVel;
    }
    
    //---------------------------------------------------------- actions.
    if(bDragStart) {
        actions.clear();
        action = nullptr;
    }
    
    if(bDoubleTapStart) {
        actions.push_back( Action::create() );
        actions.back()->type = Action::Type::DoubleTapZoom;
        actions.back()->windowHitPoint.x = buttonDoubleTapPos.x - windowPos.x;
        actions.back()->windowHitPoint.y = buttonDoubleTapPos.y - windowPos.y;
    }
    
    if(actions.size() > 0) {
        action = actions.back();
        actions.clear();
        
        bool bResizeToWindow = false;
        bResizeToWindow = bResizeToWindow || (action->type == Action::Type::WindowFit);
        bResizeToWindow = bResizeToWindow || (action->type == Action::Type::WindowFill);
        if(bResizeToWindow) {
        
            bool bWindowFill = (action->type == Action::Type::WindowFill);
        
            action->scrollStartPos = scrollPos;
            action->scrollStartSize = scrollSize;
            
            coc::Rect windowSizeRect;
            windowSizeRect.setW(windowSize.x);
            windowSizeRect.setH(windowSize.y);
            coc::Rect scrollRect = contentRect;
            scrollRect.fitInto(windowSizeRect, bWindowFill);
            
            action->scrollFinishPos.x = scrollRect.getX();
            action->scrollFinishPos.y = scrollRect.getY();
            action->scrollFinishSize.x = scrollRect.getW();
            action->scrollFinishSize.y = scrollRect.getH();
        }
        
        bool bDoubleTapZoom = false;
        bDoubleTapZoom = bDoubleTapZoom || (action->type == Action::Type::DoubleTapZoom);
        if(bDoubleTapZoom) {

            action->scrollStartPos = scrollPos;
            action->scrollStartSize = scrollSize;
            
            float scrollScale = scrollSize.x / contentSize.x;
            if(scrollScale == 1.0) {

                coc::Rect windowSizeRect;
                windowSizeRect.setW(windowSize.x);
                windowSizeRect.setH(windowSize.y);
                coc::Rect scrollRect = contentRect;
                scrollRect.fitInto(windowSizeRect, false);
                
                action->scrollFinishPos.x = scrollRect.getX();
                action->scrollFinishPos.y = scrollRect.getY();
                action->scrollFinishSize.x = scrollRect.getW();
                action->scrollFinishSize.y = scrollRect.getH();
            
            } else {
            
                float zoomScale = 1.0;
            
                const glm::vec2 & windowPoint = action->windowHitPoint;
                glm::vec2 contentPoint = getContentPointAtWindowPoint(windowPoint);
                
                glm::vec2 p0(0, 0);
                glm::vec2 p1(contentSize.x, contentSize.y);
                p0 -= contentPoint;
                p1 -= contentPoint;
                p0 *= zoomScale;
                p1 *= zoomScale;
                p0 += windowPoint;
                p1 += windowPoint;
                
                glm::vec2 scrollFinishPos = p0;
                glm::vec2 scrollFinishSize = p1 - p0;
                
                glm::vec2 boundsPos0(windowSize.x - scrollFinishSize.x,
                                     windowSize.y - scrollFinishSize.y);
                glm::vec2 boundsPos1(0, 0);
                
                if(scrollFinishSize.x < windowSize.x) {
                    boundsPos0.x = boundsPos1.x = (windowSize.x - scrollFinishSize.x) * 0.5;
                }
                if(scrollFinishSize.y < windowSize.y) {
                    boundsPos0.y = boundsPos1.y = (windowSize.y - scrollFinishSize.y) * 0.5;
                }
                
                if(scrollFinishPos.x > boundsPos1.x) { // beyond left bounds.
                    scrollFinishPos.x = boundsPos1.x;
                } else if(scrollFinishPos.x < boundsPos0.x) { // beyond right bounds.
                    scrollFinishPos.x = boundsPos0.x;
                }

                if(scrollFinishPos.y > boundsPos1.y) { // beyond top bounds.
                    scrollFinishPos.y = boundsPos1.y;
                } else if(scrollFinishPos.y < boundsPos0.y) { // beyond bottom bounds.
                    scrollFinishPos.y = boundsPos0.y;
                }

                action->scrollFinishPos = scrollFinishPos;
                action->scrollFinishSize = scrollFinishSize;
            }
            
            float diagStart = glm::length(action->scrollStartSize);
            float diagFinish = glm::length(action->scrollFinishSize);
            float diagContent = glm::length(contentSize);
            action->timeTotal = coc::abs(diagFinish - diagStart) / (diagContent * doubleTapZoomRate);
        }
    }
    
    bool bActioning = (action != nullptr);
    if(bActioning) {
    
        if(action->timeTotal == 0) {
            action->progress = 1.0;
        } else {
            action->time += timeDelta;
            action->progress = coc::map(action->time, 0, action->timeTotal, 0.0, 1.0, true);
        }
        
        scrollPos.x = coc::map(action->progress, 0.0, 1.0, action->scrollStartPos.x, action->scrollFinishPos.x);
        scrollPos.y = coc::map(action->progress, 0.0, 1.0, action->scrollStartPos.y, action->scrollFinishPos.y);
        scrollSize.x = coc::map(action->progress, 0.0, 1.0, action->scrollStartSize.x, action->scrollFinishSize.x);
        scrollSize.y = coc::map(action->progress, 0.0, 1.0, action->scrollStartSize.y, action->scrollFinishSize.y);
        
        if(action->progress == 1.0) {
            action = nullptr;
        }
    }

    //---------------------------------------------------------- contain to bounds.
    bool bContainToBounds = true;
    bContainToBounds = bContainToBounds && (bActioning == false);
    if(bContainToBounds) {

        glm::vec2 boundsPos0(windowSize.x - scrollSize.x,
                             windowSize.y - scrollSize.y);
        glm::vec2 boundsPos1(0, 0);
        
        // when the scroll size is smaller then the window size,
        // center the scroll view in the middle of the window.
        
        if(scrollSize.x < windowSize.x) {
            boundsPos0.x = boundsPos1.x = (windowSize.x - scrollSize.x) * 0.5;
        }
        if(scrollSize.y < windowSize.y) {
            boundsPos0.y = boundsPos1.y = (windowSize.y - scrollSize.y) * 0.5;
        }
        
        if(bDragging) {

            // when dragging past the bounds,
            // the below code performs an ios style drag mechanic.
            // it allows the content to be dragged slightly past the bounds,
            // to a limit set in the dragBoundsLimit.

            if(scrollPos.x > boundsPos1.x) { // beyond left bounds.
            
                float dragBeyondBounds = scrollPos.x - boundsPos1.x;
                float dragOffset = dragDist.x - dragBeyondBounds;
                dragBeyondBounds = coc::map(dragBeyondBounds, 0, windowDiagonal, 0, windowDiagonal * dragBoundsLimit.x, true);
                scrollPos.x = dragScrollPos.x + dragOffset + dragBeyondBounds;
                
            } else if(scrollPos.x < boundsPos0.x) { // beyond right bounds.
            
                float dragBeyondBounds = scrollPos.x - boundsPos0.x;
                float dragOffset = dragDist.x - dragBeyondBounds;
                dragBeyondBounds = coc::map(dragBeyondBounds, 0, -windowDiagonal, 0, -windowDiagonal * dragBoundsLimit.x, true);
                scrollPos.x = dragScrollPos.x + dragOffset + dragBeyondBounds;
            }

            if(scrollPos.y > boundsPos1.y) { // beyond top bounds.
            
                float dragBeyondBounds = scrollPos.y - boundsPos1.y;
                float dragOffset = dragDist.y - dragBeyondBounds;
                dragBeyondBounds = coc::map(dragBeyondBounds, 0, windowDiagonal, 0, windowDiagonal * dragBoundsLimit.y, true);
                scrollPos.y = dragScrollPos.y + dragOffset + dragBeyondBounds;
                
            } else if(scrollPos.y < boundsPos0.y) { // beyond bottom bounds.
            
                float dragBeyondBounds = scrollPos.y - boundsPos0.y;
                float dragOffset = dragDist.y - dragBeyondBounds;
                dragBeyondBounds = coc::map(dragBeyondBounds, 0, -windowDiagonal, 0, -windowDiagonal * dragBoundsLimit.y, true);
                scrollPos.y = dragScrollPos.y + dragOffset + dragBeyondBounds;
            }

        } else {
        
            // when the user stops dragging,
            // the below code ensures that if the content is out of bounds,
            // it moves the content back into the bounds with an easing value set in bounceEasing.
            
            glm::vec2 contentTargetPos;
            contentTargetPos.x = coc::clamp(scrollPos.x, boundsPos0.x, boundsPos1.x);
            contentTargetPos.y = coc::clamp(scrollPos.y, boundsPos0.y, boundsPos1.y);
            
            scrollPos += (contentTargetPos - scrollPos) * bounceEasing;
            if(coc::abs(scrollPos.x - contentTargetPos.x) < kEasingStop) {
                scrollPos.x = contentTargetPos.x;
            }
            if(coc::abs(scrollPos.y - contentTargetPos.y) < kEasingStop) {
                scrollPos.y = contentTargetPos.y;
            }
        }
    }
    
    //---------------------------------------------------------- model matrix.
    float modelMatrixScale = scrollSize.x / contentSize.x;
    modelMatrix = glm::translate(glm::vec3(windowPos.x + scrollPos.x, windowPos.y + scrollPos.y, 0.0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(modelMatrixScale, modelMatrixScale, 1.0));
    
    //---------------------------------------------------------- flags.
    bEnabledChanged = false;
    bWindowPosChanged = false;
    bWindowSizeChanged = false;
    bContentPosChanged = false;
    bContentSizeChanged = false;
}

//--------------------------------------------------------------
void ScrollView::pointMoved(int x, int y, unsigned int pointID) {
    pointNew(ButtonPoint::Type::Moved, x, y, pointID);
}

void ScrollView::pointPressed(int x, int y, unsigned int pointID) {
    pointNew(ButtonPoint::Type::Pressed, x, y, pointID);
}

void ScrollView::pointDragged(int x, int y, unsigned int pointID) {
    pointNew(ButtonPoint::Type::Dragged, x, y, pointID);
}

void ScrollView::pointReleased(int x, int y, unsigned int pointID) {
    pointNew(ButtonPoint::Type::Released, x, y, pointID);
}

void ScrollView::pointNew(ButtonPoint::Type type, int x, int y, unsigned int pointID) {
    if(pointID > buttons.size()-1) {
        assert(NULL); // increase num of buttons.
    }
    for(int i=0; i<buttons.size(); i++) {
        if(i == pointID) {
            if(type == ButtonPoint::Type::Moved) {
                buttons[i]->button->pointMoved(x, y);
            } else if(type == ButtonPoint::Type::Pressed) {
                buttons[i]->button->pointPressed(x, y);
            } else if(type == ButtonPoint::Type::Dragged) {
                buttons[i]->button->pointDragged(x, y);
            } else if(type == ButtonPoint::Type::Released) {
                buttons[i]->button->pointReleased(x, y);
            }
            break;
        }
    }
}

}