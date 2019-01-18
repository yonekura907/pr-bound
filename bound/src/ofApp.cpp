#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(1280, 800);
    ofBackgroundHex(0xFFFFFF);
    ofSetVerticalSync(true);
//    ofSetLogLevel(OF_LOG_NOTICE);
    
    //OSC設定
    sender.setup(HOST,SEND_PORT);
 
    //Box2dの初期設定
    box2d.init();
    box2d.setGravity(0, 18);
    //    box2d.createBounds();
    box2d.setFPS(60.0);
    box2d.registerGrabbing(); //本番では外す　オブジェクトを掴めるように
    
    //Box2dの地面
    box2d.createGround(0, ofGetHeight()-1, ofGetWidth(), ofGetHeight()-1);
    groundLine.addVertex(0, ofGetHeight());
    groundLine.addVertex(ofGetWidth(), ofGetHeight());
    
    //ボールの生成
    auto b = std::make_shared<Ball>();
    b.get()->setupBall(ofGetWidth()/2, ofGetHeight()/2, &box2d);
    ballPos.set(ofGetWidth()/2,ofGetHeight()/2);
    balls.push_back(b);
    
    //シーンクラスの生成
    bScene = new BoundScene(&box2d);
    bScene->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // ボールの落下
    for(auto & b : balls) {
        
        //ボールの値の更新kinectの値を入れる
        b->updateBall(ballPos.x, ballPos.y);
        
        // OSCアドレスを設定 Maxに送る場合に使うかも
//        ofxOscMessage msg;
//        msg.setAddress("/ballDown");
//        cout << "noteNum: " << noteNum << endl;
//        cout << "accelerationCount: " << b->accelerationCount << endl;
        
        //ここはkinectでは消してください
        if(b->accelerationCount >= 1){
//            msg.addIntArg(b->accelerationCount);
            // OSC送信
//            sender.sendMessage(msg);
            
            //シェイプの落下 --------------------
            //シーンクラスのupdateここはkinectでも必要
            bScene->update();
            
            //ボールの値をリセット
            b.get()->reset(); //ここはkinectでは消してください
        }
    }
    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ボールの描画
    for(auto & b : balls) {
        b->display();
    }
    
    //シーンクラスのdraw
    bScene->draw();
    
    //地面の描画　確認用
//    ofSetHexColor(0xFFFFFF);
//    groundLine.draw();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b') {
        balls.clear();
        auto b = std::make_shared<Ball>();
        b.get()->setupBall(ofGetWidth()/2, ofGetHeight()/2, &box2d);
        balls.push_back(b);
    }
    
    bScene->keyPressed(key);

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ }



