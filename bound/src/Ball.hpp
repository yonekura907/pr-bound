#pragma once
//
//  Ball.hpp
//  bound
//
//  Created by yonekuraakio on 2019/01/11.
//
#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"


class Ball: public ofxBox2dCircle {
public:
    void setupBall(int, int, ofxBox2d * world);
    void updateBall(float, float);
    void getBound();
    void getMaxPos();
    void display();
    void reset();
    
    bool isBound = false; //跳ね返るタイミングのフラグ
    float diffVal = 20; //速度差の許容値　この数値で音が鳴るタイミングが変わる
    float radius = 140; //ボールの半径
    ofVec2f pos; //ボールの座標
    float refPosY; //地面までの値 Y座標を反転
    float maxPosY; //ball高さのの最大値　この値が音階としてOSC送信される
    
    float velocity = 0.0;
    float lastVelocity = 0.0;
    int accelerationCount = 0;
    
//        ofSoundPlayer mySound;
};


#endif /* Ball_hpp */
