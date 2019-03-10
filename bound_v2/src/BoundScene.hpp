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
#include "ofxOsc.h"
#include "ofxBox2d.h"
#include "RectShape.hpp"
#include "CircleShape.hpp"
#include "TrianglePolyShape.hpp"
#include "Ground.hpp"
#include "ofxJSON.h"

#define N_SOUNDS 7
class SoundData {
public:
    int  soundID;
    bool bHit;
};

class BoundScene {
public:
    
    BoundScene(ofxBox2d *world, ofxOscSender *sender);
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
    
    // OSC
    void sendOscMessage(int);
    
    
    //JSON
    ofxJSONElement json;
    
    //box2d
    ofxBox2d *box2d;
    
    //OSC
    ofxOscSender *oscSender;
    
    //地面
    unique_ptr<Ground> ground;
    
    //落下シェイプ
    ofVec2f shapeMinArea, shapeMaxArea;
    vector <shared_ptr<CircleShape>> circles;
    vector <shared_ptr<RectShape>> rects;
    vector <shared_ptr<TrianglePolyShape>> triangles;
    
    //シーンの切り替え
    int scene = 0;
    
    //カラー
    ofColor *colors = new ofColor[6];
    int sNum[6]={0,1,2,3,4,5};
    
    //サウンド
    ofSoundPlayer sound[N_SOUNDS];
    
};

#endif /* BoundScene_hpp */
