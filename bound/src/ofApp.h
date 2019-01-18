#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxJSON.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <random>


#include "ofxOsc.h"
#include "Ball.hpp"
#include "RectShape.hpp"
#include "CircleShape.hpp"
#include "TrianglePolyShape.hpp"

#define N_SOUNDS 5
class SoundData {
public:
    int  soundID;
    bool bHit;
};

#define SEND_PORT 7400
#define RECEIVE_PORT 7100
#define HOST "127.0.0.1"


// -------------------------------------------------

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void setCircles();
        void setRects();
        void setTriangles();
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
    
    
    // p5 properties
    float width = ofGetWidth();
    float height = ofGetHeight();
    
    //JSON
    ofxJSONElement json;
    
    //OSC
    ofxOscSender sender;
    // OSCで送信するデータの作成
    ofxOscMessage msg;


    // box2d world
    ofxBox2d box2d;
    
    ofVec2f shapeMinArea, shapeMaxArea;
    
    //地面
    ofPolyline groundLine;
    
    vector <shared_ptr<Ball> > balls;
    ofVec2f ballPos;
    
    int noteNum;
    int midiNum[22] = {48,50,52,53,55,57,59,60,62,64,65,67,69,71,72,74,76,77,79,81,83,84};
    
    //落下の円
//    vector <shared_ptr<ofxBox2dCircle>> circles;
    vector <shared_ptr<CircleShape>> circles;
    vector <shared_ptr<RectShape>> rects;
//    vector <shared_ptr<ofxBox2dRect>> rects;
    vector <shared_ptr<TrianglePolyShape>> triangles;
    
    // this is the function for contacts
//    void contactStart(ofxBox2dContactArgs &e);
//    void contactEnd(ofxBox2dContactArgs &e);
    ofSoundPlayer  sound[N_SOUNDS];
    
    //シーンの切り替え
    int scene = 0;
    ofColor *colors = new ofColor[6];
    ofColor *bgColor = new ofColor[3];
    
    
};
