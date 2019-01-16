#pragma once
//
//  RectShape.hpp
//  musique_beta01-2
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
    
    void setupShape(ofxBox2d * world, float x, float y, ofColor *col,  ofSoundPlayer * sound);

    void display();
//    void remove();
    
    
    float rectWidth = 16; //ボールの半径
    ofVec2f pos; //ボールの座標
    ofSoundPlayer * mySound;
    
    ofColor *selfColor;
};

#endif /* RectShape_hpp */
