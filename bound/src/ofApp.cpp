#include "ofApp.h"

static bool shouldRemove(shared_ptr<ofxBox2dBaseShape>shape) {
    return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
}

//--------------------------------------------------------------

int lastBangTime;

bool isPlay = false;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    
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
//            setPloy();
            
            //ボールの値をリセット
            b.get()->reset();
        }
        
        
    }

    
    
    
    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ボールの描画
    for(auto & b : balls) {
//        b->draw();
        b->display();
    }

    for(auto & c : circles) {
//        c->display();
        c->draw();
    }
//    for(auto & r : rects) {
//        r->display();
//    }
//    for(auto & p : polies) {
//        ofSetHexColor(0x738f6c);
//        p->draw();
//    }

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
    if(key == 'p') {
        polies.clear();
    }
    if(key == 'r') {
        rects.clear();
    }
}


//--------------------------------------------------------------
void ofApp::setCircles(){
    cout << "start circle" << endl;
    int r = 200;

    for (int i=0; i<24; i++) {
        
        ofVec2f pos;
        pos.x = ofGetWidth()/2 + r * cos(ofDegToRad(i*15));
        pos.y = ofGetHeight()/2 + r * sin(ofDegToRad(i*15));
        
        shared_ptr<ofxBox2dCircle> c = make_shared<ofxBox2dCircle>();
        c.get()->setPhysics(1.0, 0.5, 0.1);
        c.get()->setup(box2d.getWorld(), pos.x, pos.y, 10);
        circles.push_back(c);
        
    }
    ofRemove(circles, shouldRemove);
}


void ofApp::setRect(){
//    if(ofGetFrameNum() % 10  == 0){
        shared_ptr<RectShape> r = make_shared<RectShape>();
        r.get()->setupRectShape(&box2d, &sound[0]);
        rects.push_back(r);
        ofRemove(rects, shouldRemove);
//    }
    
}



void ofApp::setPloy(){
    if((int)ofRandom(0, 1) == 0) {
        shared_ptr<ofxBox2dPolygon> p = make_shared<ofxBox2dPolygon>();
        ofVec2f p_pos;
        p_pos.x = (balls.back().get()->pos.x)+ofRandom(-200, 200);
        p_pos.y = -10;
        float r = ofRandom(10, 40);
        float rsin30 = r * sin(M_PI / 6.0);
        float rcos30 = r * cos(M_PI / 6.0);
        
//        p.get()->addVertex(p_pos.x - rsin30, p_pos.y - rcos30);
//        p.get()->addVertex(p_pos.x - r, p_pos.y);
//        p.get()->addVertex(p_pos.x - rsin30, p_pos.y + rcos30);
        
        
        float theta = ofDegToRad(ofRandom(0,360));
        
        int cornerCount = 24;
        for (int i = 0; i < cornerCount; i++) {
            p.get()->addVertex(p_pos.x + r * cos(ofDegToRad(360*i/cornerCount)), p_pos.y + r * sin(ofDegToRad(360*i/cornerCount)));
        }
        p.get()->close();
        p.get()->setPhysics(1.0, 0.4, 0.2);
        p.get()->create(box2d.getWorld());
        polies.push_back(p);
    }
    ofRemove(polies, shouldRemove);
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
