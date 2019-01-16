//
//  TriangleShape.hpp
//  bound
//
//  Created by yonekuraakio on 2019/01/16.
//

#ifndef TrianglePolyShape_hpp
#define TrianglePolyShape_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"



class TrianglePolyShape: public ofxBox2dPolygon{
public:
    void setupShape(ofxBox2d *world, float x, float y, ofColor *col, ofSoundPlayer *sound);
    void display();
    //    void remove();
    
    float radius = 16; //ボールの半径
    ofVec2f pos;
    ofSoundPlayer * mySound;
    
    ofColor *selfColor;
    
    ofxBox2d *selfWorld;
};



#endif /* TrianglePolyShape_hpp */
