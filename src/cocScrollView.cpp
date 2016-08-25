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
bWindowPosChanged(false),
bWindowSizeChanged(false),
bContentPosChanged(false),
bContentSizeChanged(false),
dragVelDecay(0.9, 0.9),
dragBoundsLimit(100, 100),
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

//--------------------------------------------------------------
void ScrollView::setScrollToFitWindow(float time) {
    commands.push_back( Command::create() );
    commands.back()->type = Command::Type::WindowFit;
    commands.back()->timeTotal = time;
}

void ScrollView::setScrollToFillWindow(float time) {
    commands.push_back( Command::create() );
    commands.back()->type = Command::Type::WindowFill;
    commands.back()->timeTotal = time;
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

    coc::Rect windowRect = getWindowRect();
    float windowW = windowRect.getW();
    float windowH = windowRect.getH();
    float windowDiagonal = std::sqrt(windowW * windowW + windowH * windowH);
    
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
            buttons.push_back( initButton() );
        }
    }
    
    bool bUpdateButtonRect = false;
    bUpdateButtonRect = bUpdateButtonRect || bNumOfButtonsChanged;
    bUpdateButtonRect = bUpdateButtonRect || bWindowChanged;
    if(bUpdateButtonRect) {
        for(int i=0; i<buttons.size(); i++) {
            buttons[i]->setRect(windowRect);
        }
    }
    
    for(int i=0; i<buttons.size(); i++) {
        buttons[i]->update();
    }
    
    //---------------------------------------------------------- commands.
    if(commands.size() > 0) {
        command = commands.back();
        commands.clear();
        
        if(command->type == Command::Type::WindowFit) {
        
            //
        
        } else if(command->type == Command::Type::WindowFill) {
        
            //
        }
    }
    
    //---------------------------------------------------------- drag.
    for(int i=0; i<buttons.size(); i++) {
        if(buttons[i]->pressedInside()) {
            dragButton = buttons[i];
            dragScrollPos = scrollPos;
            dragDownPos = dragMovePos = dragMovePosPrev = dragButton->getPointPosLast();
            dragVel = glm::vec2(0, 0);
        }
    }
    
    bool bDragging = (dragButton != nullptr);
    if(bDragging) {
        
        dragMovePosPrev = dragMovePos;
        dragMovePos = dragButton->getPointPosLast();
        dragDist = dragMovePos - dragDownPos;
        dragVel = dragMovePos - dragMovePosPrev;
        
        bool bDragReleased = false;
        bDragReleased = bDragReleased || dragButton->releasedInside();
        bDragReleased = bDragReleased || dragButton->releasedOutside();
        if(bDragReleased) {
            dragButton = nullptr;
        }
        
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

    //---------------------------------------------------------- contain to bounds.
    glm::vec2 boundsPos0(coc::min(windowSize.x - scrollSize.x, 0),
                         coc::min(windowSize.y - scrollSize.y, 0));
    glm::vec2 boundsPos1(0, 0);
    
    if(bDragging) {

        // when dragging past the bounds,
        // the below code performs an ios style drag mechanic.
        // it allows the content to be dragged slightly past the bounds,
        // to a limit set in the dragBoundsLimit.

        if(scrollPos.x > boundsPos1.x) { // beyond left bounds.
        
            float dragBeyondBounds = scrollPos.x - boundsPos1.x;
            float dragOffset = dragDist.x - dragBeyondBounds;
            dragBeyondBounds = coc::map(dragBeyondBounds, 0, windowDiagonal, 0, dragBoundsLimit.x, true);
            scrollPos.x = dragScrollPos.x + dragOffset + dragBeyondBounds;
            
        } else if(scrollPos.x < boundsPos0.x) { // beyond right bounds.
        
            float dragBeyondBounds = scrollPos.x - boundsPos0.x;
            float dragOffset = dragDist.x - dragBeyondBounds;
            dragBeyondBounds = coc::map(dragBeyondBounds, 0, -windowDiagonal, 0, -dragBoundsLimit.x, true);
            scrollPos.x = dragScrollPos.x + dragOffset + dragBeyondBounds;
        }

        if(scrollPos.y > boundsPos1.y) { // beyond top bounds.
        
            float dragBeyondBounds = scrollPos.y - boundsPos1.y;
            float dragOffset = dragDist.y - dragBeyondBounds;
            dragBeyondBounds = coc::map(dragBeyondBounds, 0, windowDiagonal, 0, dragBoundsLimit.y, true);
            scrollPos.y = dragScrollPos.y + dragOffset + dragBeyondBounds;
            
        } else if(scrollPos.y < boundsPos0.y) { // beyond bottom bounds.
        
            float dragBeyondBounds = scrollPos.y - boundsPos0.y;
            float dragOffset = dragDist.y - dragBeyondBounds;
            dragBeyondBounds = coc::map(dragBeyondBounds, 0, -windowDiagonal, 0, -dragBoundsLimit.y, true);
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
    
    //---------------------------------------------------------- model matrix.
    float modelMatrixScale = scrollSize.x / contentSize.x;
    modelMatrix = glm::translate(glm::vec3(windowPos.x + scrollPos.x, windowPos.y + scrollPos.y, 0.0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(modelMatrixScale, modelMatrixScale, 1.0));
    
    //---------------------------------------------------------- flags.
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
                buttons[i]->pointMoved(x, y);
            } else if(type == ButtonPoint::Type::Pressed) {
                buttons[i]->pointPressed(x, y);
            } else if(type == ButtonPoint::Type::Dragged) {
                buttons[i]->pointDragged(x, y);
            } else if(type == ButtonPoint::Type::Released) {
                buttons[i]->pointReleased(x, y);
            }
            break;
        }
    }
}

}