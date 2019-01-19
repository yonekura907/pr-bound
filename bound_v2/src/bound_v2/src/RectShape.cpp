//
//  RectShape.cpp
//  bounds
//
//  Created by yonekuraakio on 2019/01/14.
//

#include "RectShape.hpp"

void RectShape::setupShape(ofxBox2d *world, float x, float y, float rectWidth, ofColor *col, ofSoundPlayer* sound){
    pos.x = x;
    pos.y = y;
    selfWidth = rectWidth;
    setPhysics(1.4, 0.9, 0.2);
    setup(world->getWorld(), pos.x, pos.y, selfWidth, selfWidth);
    
    selfColor = col;
    
    mySound = sound;
    mySound->setMultiPlay(true);
    mySound->setLoop(false);
}


void RectShape::display(){
    
    pos.x = getPosition().x;
    pos.y = getPosition().y;
    
    float w = getWidth();
    float h = getHeight();
    
    //    cozzut << "w:" << w << "h:" << h << endl;
    
    ofFill();
    ofSetColor(*selfColor);
    //    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofDrawRectangle(pos.x-w/2, pos.y-h/2, w, h);
    
}
