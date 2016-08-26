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
// Copyright (c) 2016, Code on Canvas Pty Ltd//

#include "Grid.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Grid::Grid() {
	size.x = 4096;
	size.y = 4096;
}

Grid::~Grid() {
	//
}

void Grid::setup(float w, float h) {
	size.x = w;
	size.y = h;
}

float Grid::getWidth() {
	return size.x;
}

float Grid::getHeight() {
	return size.y;
}

void Grid::draw() {
	gl::color(Color(1,1,1));
	gl::drawSolidRect( Rectf( 0, 0, size.x, size.y) );

	int countX = 20;
	int countY = 20;
	float sizeX = size.x / countX;
	float sizeY = size.y / countY;

	gl::color(Color(0,0,0));

	for(int yi=0; yi<countY; yi++) {
		for(int xi=0; xi<countX; xi++) {
        
            int i = (yi * countX) + xi;
            int x = xi * sizeX;
            int y = yi * sizeY;
            
            continue; // TEMP.
            
            gl::drawString(toString(i), glm::vec2(x + 10, y + 20), ci::ColorA(0, 0, 0, 1));
		}
	}

	gl::color(Color(1,0,0));
	gl::drawStrokedRect( Rectf(0, 0, size.x, size.y) );

	for(int yi=1; yi<countY; yi++) {
		int x0 = 0;
		int x1 = size.x;
		int y0 = yi * sizeY;
		int y1 = y0;
		gl::drawLine(vec2(x0, y0),vec2(x1, y1));
	}

	for(int xi=1; xi<countX; xi++) {
		int x0 = xi * sizeX;
		int x1 = x0;
		int y0 = 0;
		int y1 = size.y;
		gl::drawLine(vec2(x0, y0),vec2(x1, y1));
	}

	gl::color(Color(1,1,1));
}
