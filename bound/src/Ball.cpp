//
//  Ball.cpp
//  bound
//
//  Created by yonekuraakio on 2019/01/11.
//

#include "Ball.hpp"

void Ball::setupBall(int x, int y, ofxBox2d * world){
    setPhysics(1.4, 0.7, 0.1); // 本番では引数の先頭を0.0にする
    setup(world->getWorld(), x, y, radius);
}

void Ball::updateBall(float x, float y){
    //Kinectバージョン ここから----------------------
    pos.x = x;
    pos.y = y;
    
    // Kinectの値をBox2dのボールに与える
//    setPosition(pos.x, pos.y);
    //Kinectバージョン　ここまで-----------------------
    
    
    // Kinect無しバージョン ここから------------------------
    //ボールの現在座標
    pos.x = getPosition().x;
    pos.y = getPosition().y;
    //ボールの速度を保存
    velocity = getVelocity().y;
//    cout << "velocity" << velocity << endl;
//    速度を前回の状態と比較
    if(velocity != lastVelocity){
        //前回との差分
        float diff =  lastVelocity - velocity;
        //指定の差分以下なら
        if(diff > diffVal){
            accelerationCount ++;
            isBound = true;
        }
    }
//    if(pos.y != lastPosY){
//        //前回との差分
//        float diff =  lastPosY - pos.y;
//        //指定の差分以下なら
//        if(diff > diffVal && maxPosY > ofGetHeight()/2){
//            accelerationCount ++;
//            isBound = true;
//        }
//    }
//    //1フレーム前の速度を保存
    lastVelocity = velocity;
    lastPosY = pos.y;
    //地面までの値
    refPosY = (ofGetHeight()-radius) - pos.y;
//        cout << "maxPosY: " << maxPosY << endl;
    
    if(isBound == false){
        if(refPosY > maxPosY){
            maxPosY = refPosY;
        }
    }
    // Kinect無しバージョン ここまで ------------------
}
void Ball::display(){
    ofSetCircleResolution(64);
    ofSetHexColor(0xDDDDDD);
    ofDrawCircle(pos.x, pos.y, radius);
    ofSetHexColor(0xEEEEEE);
    ofDrawCircle(pos.x, pos.y, radius-20);
}

void Ball::reset(){
    accelerationCount = 0;
    maxPosY = 0;
    isBound = false;
}
