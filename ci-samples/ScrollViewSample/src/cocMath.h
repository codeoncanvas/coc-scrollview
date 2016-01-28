//
//	    ┌─┐╔═╗┌┬┐┌─┐
//      │  ║ ║ ││├┤
//      └─┘╚═╝─┴┘└─┘
//	 ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
//	 │  ├─┤║║║└┐┌┘├─┤└─┐
//	 └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
//	http://CodeOnCanvas.cc
//
// Created by Rene Christen on 28/01/2016.
// Copyright (c) 2016, Code on Canvas Pty Ltd
//

#if defined( COC_OF )

//

#elif defined( COC_CI )

#include "cinder/CinderMath.h"

#endif


namespace coc {


#if defined(COC_CI)

float min( float x, float y ) { return ci::math<float>::min( x, y ); }
float max( float x, float y ) { return ci::math<float>::max( x, y ); }
float clamp( float x, float min = 0, float max = 1 ) { return ci::math<float>::clamp( x, min, max ); }
float abs( float x ) { return ci::math<float>::abs( x ); }

float map( float val, float inMin, float inMax, float outMin, float outMax, bool clamp = false ) {
	if ( clamp ) return ci::math<float>::clamp( ci::lmap<float>( val, inMin, inMax, outMin, outMax ), outMin, outMax );
	return ci::lmap<float>( val, inMin, inMax, outMin, outMax );
}

#elif defined(COC_OF)

float min(float x, float y) { return MIN(x,y); }
float max(float x, float y) { return MAX(x,y); }
float clamp(float x, float min = 0, float max = 1) { return ofClamp(x,min,max); }
float abs(float x) { return ABS(x); }

float map(float val, float inMin, float inMax, float outMin, float outMax, bool clamp = false) {
	return ofMap(val,inMin,inMax,outMin,outMax,clamp);
}

#endif

}//namespace coc