#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include<stdlib.h>
#include "ofxOsc.h"
#include "ofxBox2d.h"
#include "Ball.hpp"
#include "BoundScene.hpp"

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

    //OSC
    ofxOscSender sender;

    // box2d world
    ofxBox2d box2d;
    
    //地面
    ofPolyline groundLine;
    
    vector <shared_ptr<Ball> > balls;
    ofVec2f ballPos;
    
    // シェイプのアニメーションクラス
    BoundScene* bScene;

    int noteNum;
    int midiNum[22] = {48,50,52,53,55,57,59,60,62,64,65,67,69,71,72,74,76,77,79,81,83,84};

};
