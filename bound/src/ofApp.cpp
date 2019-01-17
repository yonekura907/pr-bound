#include "ofApp.h"

static bool shouldRemove(shared_ptr<ofxBox2dBaseShape>shape) {
    return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofBackgroundHex(0xfdefc2);
    
    string file = "dots.json";
    bool success = json.open(file);
    if (success){
        cout << json.getRawString() << endl;
    } else {
        cout << "Failed to parse JSON" << endl;
    }
//        string bg = json["colors"][0]["bg"].asString();
    
    colors[0].setHex(0xEDDE49);
    colors[1].setHex(0x4862B8);
    colors[2].setHex(0x82BC4B);
    colors[3].setHex(0x51C6D5);
    colors[4].setHex(0xEA4599);
    
    
    //シェイプの描画範囲
    shapeMinArea.x = 50;
    shapeMinArea.y = 50;
    shapeMaxArea.x = ofGetWidth()-50;
    shapeMaxArea.y = ofGetHeight()/3 * 2;
    
    
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
            setScene();
            //ボールの値をリセット
            b.get()->reset();
        }
    }
    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofSetColor(0xfdefc2);
//    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
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

void ofApp::setScene(){
    scene = (int)ofRandom(1,6);
//    cout << "scnen" << scene << endl;
        switch (scene) {
            case 1:
                sc01();
                break;
            case 2:
                sc02();
                break;
            case 3:
                sc03();
                break;
            case 4:
                sc04();
                break;
            case 5:
                sc05();
                break;
    
            default:
                break;
        }
}



void ofApp::sc01(){
    shared_ptr<RectShape> r = make_shared<RectShape>();
    r.get()->setupShape(&box2d, ofRandom(shapeMinArea.x,shapeMaxArea.x), ofRandom(shapeMinArea.y,shapeMaxArea.y), ofRandom(50,150), &colors[1], &sound[0]);
    rects.push_back(r);
    ofRemove(rects, shouldRemove);
    
    shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
    t.get()->setupShape(&box2d, ofRandom(shapeMinArea.x,shapeMaxArea.x), ofRandom(shapeMinArea.y,shapeMaxArea.y), ofRandom(50,150), 3, &colors[1], &sound[0]);
    triangles.push_back(t);
    ofRemove(triangles, shouldRemove);
    
    shared_ptr<CircleShape> c = make_shared<CircleShape>();
    c.get()->setupShape(&box2d, ofRandom(shapeMinArea.x,shapeMaxArea.x), ofRandom(shapeMinArea.y,shapeMaxArea.y), ofRandom(20,80), &colors[2], &sound[1]);
    circles.push_back(c);
    ofRemove(circles, shouldRemove);
}

void ofApp::sc02(){
    float splitNum = width/7;
    shared_ptr<RectShape> r1 = make_shared<RectShape>();
    r1.get()->setupShape(&box2d, width/2 - splitNum*3, 50, 10, &colors[1], &sound[0]);
    rects.push_back(r1);
    shared_ptr<RectShape> r2 = make_shared<RectShape>();
    r2.get()->setupShape(&box2d, width/2 - splitNum*2 , 50, 20, &colors[1], &sound[0]);
    rects.push_back(r2);
    shared_ptr<RectShape> r3 = make_shared<RectShape>();
    r3.get()->setupShape(&box2d, width/2 - splitNum, 50, 40, &colors[1], &sound[0]);
    rects.push_back(r3);
    shared_ptr<RectShape> r4 = make_shared<RectShape>();
    r4.get()->setupShape(&box2d, width/2 , 50, 80, &colors[1], &sound[0]);
    rects.push_back(r4);
    shared_ptr<RectShape> r5 = make_shared<RectShape>();
    r5.get()->setupShape(&box2d, width/2 + splitNum, 50, 120, &colors[1], &sound[0]);
    rects.push_back(r5);
    shared_ptr<RectShape> r6 = make_shared<RectShape>();
    r6.get()->setupShape(&box2d, width/2 + splitNum*2 , 50, 160, &colors[1], &sound[0]);
    rects.push_back(r6);
    shared_ptr<RectShape> r7 = make_shared<RectShape>();
    r7.get()->setupShape(&box2d, width/2 + splitNum*3, 50, 200, &colors[1], &sound[0]);
    rects.push_back(r7);
    ofRemove(rects, shouldRemove);
}

void ofApp::sc03(){
    ofVec2f startPos;
    ofVec2f pos;
    startPos.x = ofRandom(shapeMinArea.x+100,shapeMaxArea.x-100);
    startPos.y = ofRandom(shapeMinArea.y+100,shapeMaxArea.y-100);
    int tr = 32;
    int trm = tr*2;
    for (int i=0; i<5; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(&box2d, startPos.x, startPos.y + trm * i, tr, 3, &colors[0], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<4; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(&box2d, startPos.x + trm, startPos.y + trm * i + trm/2, tr, 3, &colors[1], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<3; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(&box2d, startPos.x + trm*2, startPos.y + trm * i + trm, tr, 3, &colors[0], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<2; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(&box2d, startPos.x + trm*3, startPos.y + trm * i + trm*3/2, tr, 3, &colors[1], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<1; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(&box2d, startPos.x + trm*4, startPos.y + trm * i + trm*4/2, tr, 3, &colors[0], &sound[0]);
        triangles.push_back(t);
    }
    ofRemove(triangles, shouldRemove);
}

void ofApp::sc04(){
    int r = floor(ofRandom(120,200));
    ofVec2f startPos;
    ofVec2f pos;
    startPos.x = ofRandom(shapeMinArea.x+100,shapeMaxArea.x-100);
    startPos.y = ofRandom(shapeMinArea.y+100,shapeMaxArea.y-100);
    for (int i=0; i<36; i++) {
        pos.x = startPos.x + r * cos(ofDegToRad(i*10));
        pos.y = startPos.y + r * sin(ofDegToRad(i*10));
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        int cnt = 0;
        if(i % 2 ==0){
            cnt = 1;
        }
        c.get()->setupShape(&box2d, pos.x, pos.y,16, &colors[cnt], &sound[1]);
        circles.push_back(c);
    }
    ofRemove(circles, shouldRemove);
}

void ofApp::sc05(){
    int r = 140;
    int theta = (int)ofRandom(0,60);
    ofVec2f pos;
    for (int i=0; i<40; i++) {
        pos.x = i*36 - 18;
        pos.y =  r * sin(ofDegToRad(theta+i*16)) + 100;
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        int cnt = 0;
        if(i % 2 ==0){
            cnt = 1;
        }
        int cr;
        if(cnt == 1){
            cr = 24;
        } else {
            cr = 12;
        }
        c.get()->setupShape(&box2d, pos.x, pos.y, cr, &colors[cnt], &sound[1]);
        circles.push_back(c);
    }
    ofRemove(circles, shouldRemove);
}



void ofApp::setCircles(){
//    cout << "start circle" << endl;
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
        c.get()->setupShape(&box2d, pos.x, pos.y,16, &colors[cnt], &sound[1]);
        circles.push_back(c);
    }
    ofRemove(circles, shouldRemove);
}
void ofApp::setRects(){
    ofVec2f pos;
    pos.x = ofGetWidth()/2;
    pos.y = 0;
    shared_ptr<RectShape> r = make_shared<RectShape>();
    r.get()->setupShape(&box2d, pos.x, pos.y, 16, &colors[1], &sound[0]);
    rects.push_back(r);
    ofRemove(rects, shouldRemove);
}

void ofApp::setTriangles(){
    //    shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
    //    t.get()->setupShape(&box2d, pos.x, pos.y, &colors[1], &sound[0]);
    //    triangles.push_back(t);
    //    ofRemove(triangles, shouldRemove);
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
