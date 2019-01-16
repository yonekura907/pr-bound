//
//  RectShape.cpp
//  musique_beta01-2
//
//  Created by yonekuraakio on 2019/01/14.
//

#include "RectShape.hpp"

void RectShape::setupShape(ofxBox2d *world, float x, float y, ofColor *col, ofSoundPlayer* sound){
    pos.x = x;
    pos.y = y;
    setPhysics(1.0, 0.5, 0.1);
    setup(world->getWorld(), pos.x, pos.y, rectWidth, rectWidth);
    
    selfColor = col;
    
    mySound = sound;
    mySound->setMultiPlay(true);
    mySound->setLoop(false);
}


void RectShape::display(){
    
    pos.x = getPosition().x;
    pos.y = getPosition().y;
    
    ofFill();
    ofSetColor(*selfColor);
    ofSetRectMode(OF_RECTMODE_CORNER);

    ofDrawRectangle(pos.x, pos.y, rectWidth, rectWidth);
    
}
