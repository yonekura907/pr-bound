#pragma once
//
//  RectShape.hpp
//  bound
//
//  Created by yonekuraakio on 2019/01/14.
//

#ifndef RectShape_hpp
#define RectShape_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"


class RectShape: public ofxBox2dRect {
public:
    
    void setupShape(ofxBox2d * world, float x, float y, float rectWidth, ofColor *col, ofSoundPlayer * sound);

    void display();
//    void remove();
    
    float selfWidth; //長さ
    ofVec2f pos; //座標
    ofSoundPlayer * mySound;
    ofColor *selfColor;
};

#endif /* RectShape_hpp */
