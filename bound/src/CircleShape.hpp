//
//  CircleShape.hpp
//  musique_beta01-2
//
//  Created by yonekuraakio on 2019/01/16.
//

#ifndef CircleShape_hpp
#define CircleShape_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"

class CircleShape: public ofxBox2dCircle{
public:
    void setupShape(ofxBox2d *world, float x, float y, ofColor *col, ofSoundPlayer *sound);
    void display();
//    void remove();
    
    float radius = 16; //ボールの半径
    ofVec2f pos;
    ofSoundPlayer * mySound;
    
    ofColor *circleColor;
    
};






#endif /* CircleShape_hpp */
