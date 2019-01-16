#include "ofApp.h"

static bool shouldRemove(shared_ptr<ofxBox2dBaseShape>shape) {
    return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    
    colors[0].setHex(0xEDDE49);
    colors[1].setHex(0x4862B8);
    colors[2].setHex(0x82BC4B);
    colors[3].setHex(0x51C6D5);
    colors[4].setHex(0xEA4599);
    
    
    
    //OSC設定
    sender.setup(HOST,SEND_PORT);
 
    //Box2dの初期設定
    box2d.init();
    box2d.setGravity(0, 9.8);
    //    box2d.createBounds();
    
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    //Box2dの地面
    box2d.createGround(10, ofGetHeight()-1, ofGetWidth()-10, ofGetHeight()-1);
    groundLine.addVertex(10, ofGetHeight()-1);
    groundLine.addVertex( ofGetWidth()-10, ofGetHeight()-1);
    
    // サウンドファイルの読み込み
    for(int i=0; i<N_SOUNDS; i++) {
        sound[i].load("sfx/"+ofToString(i)+".mp3");
        sound[i].setMultiPlay(true);
        sound[i].setLoop(false);
    }
    
    //ボールの生成
    
    auto b = std::make_shared<Ball>();
    b.get()->setupBall(ofGetWidth()/2, ofGetHeight()/2, &box2d);
    ballPos.set(ofGetWidth()/2,ofGetHeight()/2);
//    b.get()->setPhysics(1.0, 0.5, 0.1);
//    b.get()->setup(box2d.getWorld(), ballPos.x, ballPos.y, b.get()->radius);
    balls.push_back(b);
}


//--------------------------------------------------------------
void ofApp::update(){
    
    // ボールの落下 ---------------------------- update
    for(auto & b : balls) {
        b->updateBall();
        // アドレスを設定
        msg.setAddress("/ballDown");
        noteNum = (int) ofMap(b->maxPosY,ofGetHeight(),0,9,0);
        msg.addIntArg(midiNum[noteNum]);
//        cout << "noteNum: " << noteNum << endl;
//        cout << "accelerationCount: " << b->accelerationCount << endl;
        
        if(b->accelerationCount >= 1){
            msg.addIntArg(b->accelerationCount);
            // OSC送信
            sender.sendMessage(msg);

            //シェイプの落下
//            setRect();
            setCircles();
//            setTriangles();
            
            //ボールの値をリセット
            b.get()->reset();
        }
    }

    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(colors[scene]);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    
//    switch (scene) {
//        case 0:
//
//            break;
//
//        default:
//            break;
//    }
    
    
    
    //ボールの描画
    for(auto & b : balls) {
        b->display();
    }
    //シェイプの描画
    for(auto & c : circles) {
        c->display();
    }
    for(auto & r : rects) {
        r->display();
    }
    for(auto & t : triangles) {
        t->display();
    }

    //地面の描画　不要
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
    if(key == 'c') {
        circles.clear();
    }
    if(key == 't') {
        triangles.clear();
    }
    if(key == 'r') {
        rects.clear();
    }
}


//--------------------------------------------------------------
void ofApp::setCircles(){
    
    scene = floor(ofRandom(0,5));
    
    cout << "start circle" << endl;
    int r = 200;
    ofVec2f startPos;
    ofVec2f pos;
    startPos.x = ofRandom(ofGetWidth()/2-400,ofGetWidth()/2+400);
    startPos.y = ofRandom(ofGetHeight()/4,(ofGetHeight()/4)*3);
    
    for (int i=0; i<24; i++) {
        
        
        pos.x = startPos.x + (r - i*6) * cos(ofDegToRad(i*15));
        pos.y = startPos.y + (r - i*6) * sin(ofDegToRad(i*15));
        
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        
        int cnt = 0;
        
        if(i % 2 ==0){
            cnt = 1;
        }
        
        c.get()->setupShape(&box2d, pos.x, pos.y, &colors[cnt], &sound[1]);
        
        circles.push_back(c);
        
    }
    ofRemove(circles, shouldRemove);
}


void ofApp::setRects(){
    ofVec2f pos;
    pos.x = ofGetWidth()/2;
    pos.y = 0;
    shared_ptr<RectShape> r = make_shared<RectShape>();
    r.get()->setupShape(&box2d, pos.x, pos.y, &colors[1], &sound[0]);
    
//    float angle = r.get()->getRotation();
//    r.get()->setFixedRotation(90);
//    cout << angle << endl;
    rects.push_back(r);
    ofRemove(rects, shouldRemove);
}



void ofApp::setTriangles(){
    
    cout << "setTriangles start" << endl;
    shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
    ofVec2f pos;
    pos.x = ofGetWidth()/2;
    pos.y = 0;
    
    t.get()->setupShape(&box2d, pos.x, pos.y, &colors[1], &sound[0]);

    triangles.push_back(t);
    ofRemove(triangles, shouldRemove);
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


//--------------------------------------------------------------
//void ofApp::contactStart(ofxBox2dContactArgs &e) {
//    if(e.a != NULL && e.b != NULL) {
//
//        // if we collide with the ground we do not
//        // want to play a sound. this is how you do that
//        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
//
//            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
//            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
//
//            if(aData) {
//                aData->bHit = true;
//                sound[aData->soundID].play();
//            }
//
//            if(bData) {
//                bData->bHit = true;
//                sound[bData->soundID].play();
//            }
//        }
//    }
//}

//--------------------------------------------------------------
//void ofApp::contactEnd(ofxBox2dContactArgs &e) {
//    if(e.a != NULL && e.b != NULL) {
//
//        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
//        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
//
//        if(aData) {
//            aData->bHit = false;
//        }
//
//        if(bData) {
//            bData->bHit = false;
//        }
//    }
//}
