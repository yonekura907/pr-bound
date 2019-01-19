//
//  Ground.cpp
//  bound
//
//  Created by yonekuraakio on 2019/01/19.
//

#include "Ground.hpp"

Ground::Ground(ofxBox2d *world){
    box2d = world;
}

void Ground::setup(){
    box2d->createGround(200, ofGetHeight(), ofGetWidth()-200, ofGetHeight());
    groundLine.addVertex(200, ofGetHeight());
    groundLine.addVertex(ofGetWidth()-200, ofGetHeight());
}

void Ground::update(){
    
}

void Ground::draw(){
    //地面の描画　確認用
    //    ofSetHexColor(0xFFFFFF);
    //    groundLine.draw();
}
