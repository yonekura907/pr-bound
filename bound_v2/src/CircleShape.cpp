//
//  CircleShape.cpp
//  bound
//
//  Created by yonekuraakio on 2019/01/16.
//

#include "CircleShape.hpp"

void CircleShape::setupShape(ofxBox2d *world, float x, float y, float radius, ofColor *col, ofSoundPlayer* sound){
    pos.x = x;
    pos.y = y;
    selfRadius = radius;
    setPhysics(1.4, 0.8, 0.2);
    setup(world->getWorld(), pos.x, pos.y, selfRadius);
    
    selfColor = col;
    
    mySound = sound;
    mySound->setMultiPlay(true);
    mySound->setLoop(false);
}


void CircleShape::display(){
    pos.x = getPosition().x;
    pos.y = getPosition().y;
    
    ofFill();
    ofSetColor(*selfColor);
    ofDrawCircle(pos.x, pos.y, selfRadius);
};

