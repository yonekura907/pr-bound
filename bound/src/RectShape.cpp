//
//  RectShape.cpp
//  musique_beta01-2
//
//  Created by yonekuraakio on 2019/01/14.
//

#include "RectShape.hpp"

void RectShape::setupRectShape(ofxBox2d * world, ofSoundPlayer * sound){
    rectWidth = ofRandom(40,120);
    pos.x = ofRandom(50,ofGetWidth()-50);
    pos.y = -50;
    setPhysics(1.0, 0.5, 0.1);
    setup(world->getWorld(), pos.x, pos.y, rectWidth, rectWidth);
    
    mySound = sound;
    mySound->setMultiPlay(true);
    mySound->setLoop(false);
}


void RectShape::updateRectShape(int bang){
    bangTime = bang;
    
    
    if(lastBangTime != bangTime){
        if (bangTime % 4 == 0){
            
            mySound->play();
        }
    }
    lastBangTime = bangTime;
}


void RectShape::display(int bang){
    
    bangTime = bang;
    ofVec2f pos;
    pos.x = getPosition().x;
    pos.y = getPosition().y;
    
    float angle = this->getRotation();
    
    cout << angle << endl;
    if (bangTime % 4 == 0){
        ofSetHexColor(0x90d4e3);
    } else {
        ofSetHexColor(0x738f6c);
    }
    ofDrawRectangle(pos.x-rectWidth/2, pos.y-rectWidth/2, rectWidth, rectWidth);
}


void RectShape::remove(){
    
    ofVec2f pos;
    pos.x = getPosition().x;
    pos.y = getPosition().x;
    
    if(pos.x > ofGetWidth() || pos.x < -50){
        isBound = false;
        mySound->stop();
        cout << "remove" << endl;
    }
    
}
