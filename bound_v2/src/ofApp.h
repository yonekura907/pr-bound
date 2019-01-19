#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"
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
    
    // ------------------------------------------
    ofxPanel panel;
    vector < shared_ptr<ofxKinectV2> > kinects;
    vector <ofTexture> texDepth;
    vector <ofTexture> texRGB;
    
    //OpenCVで扱うカラーイメージ
    ofxCvColorImage colorImg;
    //OpenCVで扱うグレースケールイメージ
    ofxCvGrayscaleImage grayImage;
    //背景のグレースケールイメージ
    ofxCvGrayscaleImage grayBg;
    //背景との差分のグレースケールイメージ
    ofxCvGrayscaleImage grayDiff;
    //輪郭抽出のためのインスタンス
    ofxCvContourFinder contourFinder;
    
    //背景を記録したかどうか
    bool bLearnBakground;
    //背景の差分の閾値
    int threshold;
    
    ofVec2f displaySize;
    
    // 物体検出の面積
    float boundingArea;
    // 物体検出をする最小面積
    float boundingAreaMin;
    // 物体検出をする最大面積
    float boundingAreaMax;
    
    // ボールの座標
    ofVec2f pos;
    // 1フレーム前のボールの座標
    ofVec2f prePos;
    // ボールと地面が設置するy座標
    float groundY;
    // 地面からの検出範囲
    float thresholdGroundY;
    // y方向のボールのスピード
    float speedY;
    // 1フレーム前のy方向のボールのスピード
    float preSpeedY;
    // バウンドの検出
    bool bound;
    
    // -------------------------------------------------
    
    //OSC
    ofxOscSender sender;
    
    // box2d world
    ofxBox2d box2d;
    
    //ボールのクラス
    vector <shared_ptr<Ball> > balls;
    //ボールの座標
    ofVec2f ballPos;
    
    // シェイプのアニメーションクラス
    unique_ptr<BoundScene> bScene;
    
    int noteNum;
    int midiNum[22] = {48,50,52,53,55,57,59,60,62,64,65,67,69,71,72,74,76,77,79,81,83,84};
};
