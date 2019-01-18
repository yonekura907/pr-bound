//
//  BoundScene.hpp
//  bound
//
//  Created by yonekuraakio on 2019/01/18.
//

#ifndef BoundScene_hpp
#define BoundScene_hpp

#include <stdio.h>
#include "ofMain.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <random>
#include<stdlib.h>
#include "ofxBox2d.h"
#include "RectShape.hpp"
#include "CircleShape.hpp"
#include "TrianglePolyShape.hpp"
#include "ofxJSON.h"

#define N_SOUNDS 5
class SoundData {
public:
    int  soundID;
    bool bHit;
};

class BoundScene {
public:
    
    BoundScene(ofxBox2d *world);
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    
//    void setCircles();
//    void setRects();
//    void setTriangles();
    
    void setScene();
    void sc01();
    void sc02();
    void sc03();
    void sc04();
    void sc05();
    void sc06();
    void sc07();
    void sc08();
    void sc09();
    void sc10();
    
    //JSON
    ofxJSONElement json;
    
    //box2d
    ofxBox2d *box2d;
    ofVec2f shapeMinArea, shapeMaxArea;
    vector <shared_ptr<CircleShape>> circles;
    vector <shared_ptr<RectShape>> rects;
    vector <shared_ptr<TrianglePolyShape>> triangles;
    
    //シーンの切り替え
    int scene = 0;
    
    //カラー
    ofColor *colors = new ofColor[6];
    int sNum[6]={0,1,2,3,4,5};
    
    ofSoundPlayer  sound[N_SOUNDS];

};

#endif /* BoundScene_hpp */
