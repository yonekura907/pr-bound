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
    box2d->createGround(0, ofGetHeight()-1, ofGetWidth(), ofGetHeight()-1);
    groundLine.addVertex(0, ofGetHeight());
    groundLine.addVertex(ofGetWidth(), ofGetHeight());
}

void Ground::update(){
    
}

void Ground::draw(){
    //地面の描画　確認用
    //    ofSetHexColor(0xFFFFFF);
    //    groundLine.draw();
}
