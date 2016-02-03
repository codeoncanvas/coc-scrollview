//	    ┌─┐╔═╗┌┬┐┌─┐
//      │  ║ ║ ││├┤
//      └─┘╚═╝─┴┘└─┘
//	 ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
//	 │  ├─┤║║║└┐┌┘├─┤└─┐
//	 └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
//	http://codeoncanvas.cc
//
// Created by Rene Christen on 28/01/2016.
// Copyright (c) 2016, Code on Canvas Pty Ltd
//

#include "cocMath.h"

namespace coc {

//--------------------------------------------------------------
#ifdef COC_OF

float min(float x, float y) {
    return MIN(x, y);
}

#endif

#ifdef COC_CI

float min(float x, float y) {
    return ci::math<float>::min( x, y );
}

#endif

//--------------------------------------------------------------
#ifdef COC_OF

float max(float x, float y) {
    return MAX(x, y);
}

#endif

#ifdef COC_CI

float max(float x, float y) {
    return ci::math<float>::max( x, y );
}

#endif

//--------------------------------------------------------------
#ifdef COC_OF

float clamp(float x, float min, float max) {
    return ofClamp(x, min, max);
}

#endif

#ifdef COC_CI

float clamp(float x, float min, float max) {
    return ci::math<float>::clamp( x, min, max );
}

#endif

//--------------------------------------------------------------
#ifdef COC_OF

float abs(float x) {
    return ABS(x);
}

#endif

#ifdef COC_CI

float abs(float x) {
    return ci::math<float>::abs( x );
}

#endif

//--------------------------------------------------------------
#ifdef COC_OF

float map(float val, float inMin, float inMax, float outMin, float outMax, bool clamp) {
    return ofMap(val, inMin, inMax, outMin, outMax, clamp);
}

#endif

#ifdef COC_CI

float map(float val, float inMin, float inMax, float outMin, float outMax, bool clamp) {
    if ( clamp ) {
        return ci::math<float>::clamp( ci::lmap<float>( val, inMin, inMax, outMin, outMax ), outMin, outMax );
    }
	return ci::lmap<float>( val, inMin, inMax, outMin, outMax );
}

#endif

//--------------------------------------------------------------
#ifdef COC_OF

float lerp(float a, float b, float amount) {
    return ofLerp(a, b, amount);
}

#endif

#ifdef COC_CI

float lerp(float a, float b, float amount) {
    return ci::lerp(a, b, amount);
}

#endif

}