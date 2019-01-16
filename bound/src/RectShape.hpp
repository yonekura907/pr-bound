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
    
    void setupRectShape(ofxBox2d * world, ofSoundPlayer * sound);
    void updateRectShape(int);
    void display(int);
    void remove();
    
    bool isBound = false; //跳ね返るタイミングのフラグ
    int bangTime, lastBangTime;
    float rectWidth; //ボールの半径
    ofVec2f pos; //ボールの座標
    
    ofSoundPlayer * mySound;
    
    
};

#endif /* RectShape_hpp */
