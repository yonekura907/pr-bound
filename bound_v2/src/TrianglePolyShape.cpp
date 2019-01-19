//
//  TriangleShape.cpp
//  bound
//
//  Created by yonekuraakio on 2019/01/16.
//

#include "TrianglePolyShape.hpp"


void TrianglePolyShape::setupShape(ofxBox2d *world, float x, float y, float radius, int cornerCount, ofColor *col, ofSoundPlayer* sound){
    pos.x = x;
    pos.y = y;
    selfRadius = radius;
    selfCornerCount = cornerCount;
    //    setup(world->getWorld(), pos.x, pos.y, radius);
    
    selfColor = col;
    selfWorld = world;
    
    //    cout << selfWorld << endl;
    
    mySound = sound;
    mySound->setMultiPlay(true);
    mySound->setLoop(false);
    
    //    pos.x = getPosition().x;
    //    pos.y = getPosition().y;
    
    ofFill();
    ofSetColor(*selfColor);
    
    for (int i = 0; i < selfCornerCount; i++) {
        addVertex(pos.x + selfRadius * cos(ofDegToRad(360*i/selfCornerCount)), pos.y + selfRadius * sin(ofDegToRad(360*i/selfCornerCount)));
    }
    close();
    setPhysics(1.4, 0.8, 0.2);
    create(selfWorld->getWorld());
    
}


void TrianglePolyShape::display(){
    
    ofFill();
    ofSetColor(*selfColor);
    this->draw();
    
    //
    //    float theta = ofDegToRad(0);
    //    int cornerCount = 3;
    //    for (int i = 0; i < cornerCount; i++) {
    //        addVertex(pos.x + radius * cos(ofDegToRad(360*i/cornerCount)), pos.y + radius * sin(ofDegToRad(360*i/cornerCount)));
    //    }
    //    close();
    //    setPhysics(1.0, 0.4, 0.2);
    //    create(selfWorld->getWorld());
    
};
