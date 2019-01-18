//
//  Ball.cpp
//  bound
//
//  Created by yonekuraakio on 2019/01/11.
//

#include "Ball.hpp"


void Ball::setupBall(int x, int y, ofxBox2d * world){
    setPhysics(1.4, 0.7, 0.1);
    setup(world->getWorld(), x, y, radius);
}


void Ball::updateBall(){
    
    //ボールの現在座標
    pos.x = getPosition().x;
    pos.y = getPosition().y;
    
    //ボールの速度を保存
    velocity = getVelocity().y;
//    cout << "velocity" << velocity << endl;
    
    //速度を前回の状態と比較
    if(velocity != lastVelocity){
        //前回との差分
        float diff =  lastVelocity - velocity;
        //指定の差分以下なら
        if(diff > diffVal){
            accelerationCount ++;
            isBound = true;
        }
    }
    //1フレーム前の速度を保存
    lastVelocity = velocity;
    
    //地面までの値
    refPosY = (ofGetHeight()-radius) - pos.y;
    //    cout << "refPosY: " << refPosY << endl;
    
    if(isBound == false){
        if(refPosY > maxPosY){
            maxPosY = refPosY;
        }
    }
}

void Ball::display(){
    ofSetCircleResolution(64);
    ofSetHexColor(0xffffff);
    ofDrawCircle(pos.x, pos.y, 100);
}


void Ball::reset(){
    accelerationCount = 0;
    maxPosY = 0;
    isBound = false;
}
