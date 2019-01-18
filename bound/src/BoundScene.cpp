//
//  BoundScene.cpp
//  bound
//
//  Created by yonekuraakio on 2019/01/18.
//

#include "BoundScene.hpp"

static bool shouldRemove(shared_ptr<ofxBox2dBaseShape>shape) {
    return !ofRectangle(0, -400, ofGetWidth(), ofGetHeight()+400).inside(shape->getPosition());
}

template<class T> void shuffle(T ary[],int size){
    for(int i=0;i<size;i++){
        int j = rand()%size;
        T t = ary[i];
        ary[i] = ary[j];
        ary[j] = t;
    }
}

BoundScene::BoundScene(ofxBox2d *world){
    cout << world << endl;
    box2d = world;
    
}

void BoundScene::setup(){
    //カラーの登録
    colors[0].setHex(0xEA4599); //ピンク
    colors[1].setHex(0xEDA149); //オレンジ
    colors[2].setHex(0xEDDE49); //イエロー2
    colors[3].setHex(0x82BC4B); //グリーン
    colors[4].setHex(0x51C6D5); //ターコイズ
    colors[5].setHex(0x5470D0); //ブルー
    
    
//    bgColor[0].setHex(0xEEEEEE);
//    bgColor[1].setHex(0xE6F2FF);
//    bgColor[2].setHex(0xFDEFC2);
    
    // JSON読み込み ----------------------------
    string file = "dots.json";
    bool success = json.open(file);
    if (!success){
        cout << "Failed to parse JSON" << endl;
    }

    //シェイプの描画範囲
    shapeMinArea.x = 50;
    shapeMinArea.y = 50;
    shapeMaxArea.x = ofGetWidth()-50;
    shapeMaxArea.y = ofGetHeight()/2;

//    // サウンドファイルの読み込み
//    for(int i=0; i<N_SOUNDS; i++) {
//        sound[i].load("sfx/"+ofToString(i)+".mp3");
//        sound[i].setMultiPlay(true);
//        sound[i].setLoop(false);
//    }
}


void BoundScene::update(){
    //シェイプの落下
    setScene();
}

void BoundScene::draw(){
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
}


void BoundScene::keyPressed(int key){
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
void BoundScene::setScene(){
//    sc07();
    //シーンをランダムで選ぶ
    scene = (int)ofRandom(1,6);
    cout << "scnen" << scene << endl;
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

//--------------------------------------------------------------

void BoundScene::sc01(){
    shuffle<int>(sNum,6);
    int colorNum0 = sNum[0];
    int colorNum1 = sNum[1];
    int colorNum2 = sNum[2];
    int colorNum3 = sNum[3];
    int colorNum4 = sNum[4];

    ofVec2f pos0;
    pos0.set(0,50);
    int h = 7;
    for (int i=0; i<json["alphabets"][h]["pos"].size(); i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        ofVec2f pos;
        pos.x = json["alphabets"][h]["pos"][i]["x"].asInt();
        pos.y = json["alphabets"][h]["pos"][i]["y"].asInt();
        t.get()->setupShape(box2d, pos0.x + pos.x/2, pos0.y + pos.y/2, 24, 5, &colors[colorNum0], &sound[0]);
        triangles.push_back(t);
    }
    ofVec2f pos1;
    pos1.set(pos0.x + json["alphabets"][h]["width"].asInt()/2-30,50);
    int e = 4;
    for (int i=0; i<json["alphabets"][e]["pos"].size(); i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        ofVec2f pos;
        pos.x = json["alphabets"][e]["pos"][i]["x"].asInt();
        pos.y = json["alphabets"][e]["pos"][i]["y"].asInt();
        t.get()->setupShape(box2d, pos1.x + pos.x/2, pos1.y + pos.y/2, 24, 4, &colors[colorNum1], &sound[0]);
        triangles.push_back(t);
    }
    ofVec2f pos2;
    pos2.set(pos1.x + json["alphabets"][e]["width"].asInt()/2-30,50);
    int l = 11;
    for (int i=0; i<json["alphabets"][l]["pos"].size(); i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        ofVec2f pos;
        pos.x = json["alphabets"][l]["pos"][i]["x"].asInt();
        pos.y = json["alphabets"][l]["pos"][i]["y"].asInt();
        t.get()->setupShape(box2d, pos2.x + pos.x/2, pos1.y + pos.y/2, 24, 3, &colors[colorNum2], &sound[0]);
        triangles.push_back(t);
    }
    ofVec2f pos3;
    pos3.set(pos2.x + json["alphabets"][l]["width"].asInt()/2-30,50);
    for (int i=0; i<json["alphabets"][l]["pos"].size(); i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        ofVec2f pos;
        pos.x = json["alphabets"][l]["pos"][i]["x"].asInt();
        pos.y = json["alphabets"][l]["pos"][i]["y"].asInt();
        t.get()->setupShape(box2d, pos3.x + pos.x/2, pos1.y + pos.y/2, 24, 3, &colors[colorNum3], &sound[0]);
        triangles.push_back(t);
    }
    ofVec2f pos4;
    pos4.set(pos3.x + json["alphabets"][l]["width"].asInt()/2-30,50);
    int o = 14;
    for (int i=0; i<json["alphabets"][o]["pos"].size(); i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        ofVec2f pos;
        pos.x = json["alphabets"][o]["pos"][i]["x"].asInt();
        pos.y = json["alphabets"][o]["pos"][i]["y"].asInt();
        t.get()->setupShape(box2d, pos4.x + pos.x/2, pos1.y + pos.y/2, 24, 5, &colors[colorNum4], &sound[0]);
        triangles.push_back(t);
    }
}

void BoundScene::sc02(){
    // 四角形が並ぶ -----------------------
    shuffle<int>(sNum,6);
    int colorNum0 = sNum[1];
    int colorNum1 = sNum[2];
    float splitNum = ofGetWidth()/7;
    shared_ptr<RectShape> r1 = make_shared<RectShape>();
    r1.get()->setupShape(box2d, ofGetWidth()/2 - splitNum*3, 50, 10, &colors[colorNum0], &sound[0]);
    rects.push_back(r1);
    shared_ptr<RectShape> r2 = make_shared<RectShape>();
    r2.get()->setupShape(box2d, ofGetWidth()/2 - splitNum*2 , 50, 20, &colors[colorNum1], &sound[0]);
    rects.push_back(r2);
    shared_ptr<RectShape> r3 = make_shared<RectShape>();
    r3.get()->setupShape(box2d, ofGetWidth()/2 - splitNum, 50, 40, &colors[colorNum0], &sound[0]);
    rects.push_back(r3);
    shared_ptr<RectShape> r4 = make_shared<RectShape>();
    r4.get()->setupShape(box2d, ofGetWidth()/2 , 50, 80, &colors[colorNum1], &sound[0]);
    rects.push_back(r4);
    shared_ptr<RectShape> r5 = make_shared<RectShape>();
    r5.get()->setupShape(box2d, ofGetWidth()/2 + splitNum, 50, 120, &colors[colorNum0], &sound[0]);
    rects.push_back(r5);
    shared_ptr<RectShape> r6 = make_shared<RectShape>();
    r6.get()->setupShape(box2d, ofGetWidth()/2 + splitNum*2 , 50, 160, &colors[colorNum1], &sound[0]);
    rects.push_back(r6);
    shared_ptr<RectShape> r7 = make_shared<RectShape>();
    r7.get()->setupShape(box2d, ofGetWidth()/2 + splitNum*3, 50, 200, &colors[colorNum0], &sound[0]);
    rects.push_back(r7);
    ofRemove(rects, shouldRemove);
}

void BoundScene::sc03(){
    //三角旗-----------------------
    shuffle<int>(sNum,6);
    int colorNum0 = sNum[1];
    int colorNum1 = sNum[2];
    ofVec2f startPos;
    ofVec2f pos;
    startPos.x = ofRandom(shapeMinArea.x+100,shapeMaxArea.x-100);
    startPos.y = ofRandom(shapeMinArea.y,shapeMaxArea.y-300);
    int tr = 32;
    int trm = tr*2;
    for (int i=0; i<5; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(box2d, startPos.x, startPos.y + trm * i, tr, 3, &colors[colorNum0], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<4; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(box2d, startPos.x + trm, startPos.y + trm * i + trm/2, tr, 3, &colors[colorNum1], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<3; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(box2d, startPos.x + trm*2, startPos.y + trm * i + trm, tr, 3, &colors[colorNum0], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<2; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(box2d, startPos.x + trm*3, startPos.y + trm * i + trm*3/2, tr, 3, &colors[colorNum1], &sound[0]);
        triangles.push_back(t);
    }
    for (int i=0; i<1; i++) {
        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
        t.get()->setupShape(box2d, startPos.x + trm*4, startPos.y + trm * i + trm*4/2, tr, 3, &colors[colorNum0], &sound[0]);
        triangles.push_back(t);
    }
    ofRemove(triangles, shouldRemove);
}

void BoundScene::sc04(){
    // サークル -------------------------------------------
    shuffle<int>(sNum,6);
    int colorNum0 = sNum[1];
    int colorNum1 = sNum[2];
    int colorNum2 = sNum[3];
    int r1 = 180;
    int r2 = 120;
    int r3 = 60;
    ofVec2f startPos;
    ofVec2f pos;
    startPos.x = ofRandom(shapeMinArea.x+100,shapeMaxArea.x-100);
    startPos.y = ofRandom(shapeMinArea.y+100,shapeMaxArea.y-100);
    for (int i=0; i<24; i++) {
        pos.x = startPos.x + r1 * cos(ofDegToRad(i*15));
        pos.y = startPos.y + r1 * sin(ofDegToRad(i*15));
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        c.get()->setupShape(box2d, pos.x, pos.y,16, &colors[colorNum0], &sound[1]);
        circles.push_back(c);
    }
    for (int i=0; i<18; i++) {
        pos.x = startPos.x + r2 * cos(ofDegToRad(i*20));
        pos.y = startPos.y + r2 * sin(ofDegToRad(i*20));
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        c.get()->setupShape(box2d, pos.x, pos.y,16, &colors[colorNum1], &sound[1]);
        circles.push_back(c);
    }
    for (int i=0; i<9; i++) {
        pos.x = startPos.x + r3 * cos(ofDegToRad(i*40));
        pos.y = startPos.y + r3 * sin(ofDegToRad(i*40));
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        c.get()->setupShape(box2d, pos.x, pos.y,16, &colors[colorNum2], &sound[1]);
        circles.push_back(c);
    }
    ofRemove(circles, shouldRemove);
}

void BoundScene::sc05(){
    // ウェーブ -------------------------------------------
    shuffle<int>(sNum,6);
    int colorNum, cRadius;
    int r = 140;
    int theta = (int)ofRandom(0,60);
    ofVec2f pos;
    for (int i=0; i<40; i++) {
        pos.x = i*36 - 8;
        pos.y =  r * sin(ofDegToRad(theta+i*16)) + 200;
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        int cnt = 0;
        if(i % 3 == 0){
            colorNum = sNum[1];
            cRadius = 8;
        } else if(i % 3 == 1){
            colorNum = sNum[2];
            cRadius = 12;
        } else {
            colorNum = sNum[3];
            cRadius = 16;
        }
        c.get()->setupShape(box2d, pos.x, pos.y, cRadius, &colors[colorNum], &sound[1]);
        circles.push_back(c);
    }
    ofRemove(circles, shouldRemove);
}

void BoundScene::sc06(){
    // 3つのシェイプ -------------------------------------------
    shuffle<int>(sNum,6);
    int colorNum0 = sNum[1];
    int colorNum1 = sNum[2];
    int colorNum2 = sNum[3];
    shared_ptr<TrianglePolyShape> t1 = make_shared<TrianglePolyShape>();
    t1.get()->setupShape(box2d, ofRandom(shapeMinArea.x,shapeMaxArea.x), ofRandom(shapeMinArea.y,shapeMaxArea.y), ofRandom(150,300), 4, &colors[colorNum0], &sound[0]);
    triangles.push_back(t1);
    shared_ptr<TrianglePolyShape> t2 = make_shared<TrianglePolyShape>();
    t2.get()->setupShape(box2d, ofRandom(shapeMinArea.x,shapeMaxArea.x), ofRandom(shapeMinArea.y,shapeMaxArea.y), ofRandom(150,300), 3, &colors[colorNum1], &sound[0]);
    triangles.push_back(t2);
    shared_ptr<TrianglePolyShape> t3 = make_shared<TrianglePolyShape>();
    t3.get()->setupShape(box2d, ofRandom(shapeMinArea.x,shapeMaxArea.x), ofRandom(shapeMinArea.y,shapeMaxArea.y), ofRandom(150,300), 5, &colors[colorNum2], &sound[0]);
    triangles.push_back(t3);
    ofRemove(triangles, shouldRemove);

}

    
    
void BoundScene::sc07(){
    int colorNum = ofRandom(0, sizeof(colors));
    int dotLength = json["alphabets"][0]["pos"].size();
    for (int i=0; i<dotLength; i++) {
        shared_ptr<CircleShape> c = make_shared<CircleShape>();
        ofVec2f pos;
        pos.x = json["alphabets"][0]["pos"][i]["x"].asInt();
        pos.y = json["alphabets"][0]["pos"][i]["y"].asInt();
        c.get()->setupShape(box2d, pos.x/2, pos.y/2, 16, &colors[colorNum], &sound[1]);
        c.get()->setData(new SoundData());
        //        SoundData * sd = (SoundData*)c.get()->getData();
        //        sd->soundID = ofRandom(0, N_SOUNDS);
        //        sd->bHit    = false;
        circles.push_back(c);
    }
}

void BoundScene::sc08(){
//    shuffle<int>(sNum,6);
//    int colorNum0 = sNum[0];
//    int colorNum1 = sNum[1];
//    int colorNum2 = sNum[2];
//    int colorNum3 = sNum[3];
//    int colorNum4 = sNum[4];
//
//    ofVec2f pos0;
//    pos0.set(0,50);
//    int b = 1;
//    for (int i=0; i<json["alphabets"][b]["pos"].size(); i++) {
//        shared_ptr<CircleShape> t = make_shared<CircleShape>();
//        ofVec2f pos;
//        pos.x = json["alphabets"][b]["pos"][i]["x"].asInt();
//        pos.y = json["alphabets"][b]["pos"][i]["y"].asInt();
//        t.get()->setupShape(&box2d, pos0.x + pos.x/2, pos0.y + pos.y/2, 24, &colors[colorNum0], &sound[0]);
//        circles.push_back(t);
//    }
//    ofVec2f pos1;
//    pos1.set(pos0.x + json["alphabets"][b]["width"].asInt()/2-30,50);
//    int o = 14;
//    for (int i=0; i<json["alphabets"][o]["pos"].size(); i++) {
//        shared_ptr<CircleShape> t = make_shared<CircleShape>();
//        ofVec2f pos;
//        pos.x = json["alphabets"][o]["pos"][i]["x"].asInt();
//        pos.y = json["alphabets"][o]["pos"][i]["y"].asInt();
//        t.get()->setupShape(&box2d, pos1.x + pos.x/2, pos1.y + pos.y/2, 24, &colors[colorNum1], &sound[0]);
//        circles.push_back(t);
//    }
//    ofVec2f pos2;
//    pos2.set(pos2.x + json["alphabets"][o]["width"].asInt()/2-30,50);
//    int u = 21;
//    for (int i=0; i<json["alphabets"][u]["pos"].size(); i++) {
//        shared_ptr<CircleShape> t = make_shared<CircleShape>();
//        ofVec2f pos;
//        pos.x = json["alphabets"][u]["pos"][i]["x"].asInt();
//        pos.y = json["alphabets"][u]["pos"][i]["y"].asInt();
//        t.get()->setupShape(&box2d, pos2.x + pos.x/2, pos1.y + pos.y/2, 24, &colors[colorNum2], &sound[0]);
//        circles.push_back(t);
//    }
    //    ofVec2f pos3;
    //    pos3.set(pos2.x + json["alphabets"][u]["width"].asInt()/2-30,50);
    //    int n = 15;
    //    for (int i=0; i<json["alphabets"][n]["pos"].size(); i++) {
    //        shared_ptr<CircleShape> t = make_shared<CircleShape>();
    //        ofVec2f pos;
    //        pos.x = json["alphabets"][n]["pos"][i]["x"].asInt();
    //        pos.y = json["alphabets"][n]["pos"][i]["y"].asInt();
    //        t.get()->setupShape(&box2d, pos3.x + pos.x/2, pos1.y + pos.y/2, 24, &colors[colorNum3], &sound[0]);
    //        circles.push_back(t);
    //    }
    //    ofVec2f pos4;
    //    pos4.set(pos3.x + json["alphabets"][n]["width"].asInt()/2-30,50);
    //    int d = 14;
    //    for (int i=0; i<json["alphabets"][d]["pos"].size(); i++) {
    //        shared_ptr<CircleShape> t = make_shared<CircleShape>();
    //        ofVec2f pos;
    //        pos.x = json["alphabets"][d]["pos"][i]["x"].asInt();
    //        pos.y = json["alphabets"][d]["pos"][i]["y"].asInt();
    //        t.get()->setupShape(&box2d, pos4.x + pos.x/2, pos1.y + pos.y/2, 24, &colors[colorNum4], &sound[0]);
    //        circles.push_back(t);
    //    }
}
    
void BoundScene::sc09(){
    
}



//void BoundScene::sc10(){
//    //三角旗-----------------------
//    shuffle<int>(sNum,6);
//    int colorNum0 = sNum[1];
//    int colorNum1 = sNum[2];
//    ofVec2f startPos;
//    ofVec2f pos;
//    startPos.x = ofRandom(shapeMinArea.x+100, shapeMaxArea.x-100);
//    startPos.y = ofRandom(shapeMinArea.y, shapeMaxArea.y);
//    int tr = 32;
//    int trm = tr*2.2;
//
//
//    for (int i=0; i<2; i++) {
//        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
//        t.get()->setupShape(&box2d, (startPos.x + trm * i) + 96, startPos.y - trm - 96, tr, 4, &colors[colorNum0], &sound[0]);
//        triangles.push_back(t);
//    }
//    for (int i=0; i<3; i++) {
//        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
//        t.get()->setupShape(&box2d, (startPos.x + trm * i) + 64, startPos.y - trm - 40, tr, 4, &colors[colorNum0], &sound[0]);
//        triangles.push_back(t);
//    }
//    for (int i=0; i<4; i++) {
//        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
//        t.get()->setupShape(&box2d, (startPos.x + trm * i) + 32, startPos.y - trm + 16, tr, 4, &colors[colorNum0], &sound[0]);
//        triangles.push_back(t);
//    }
//    for (int i=0; i<5; i++) {
//        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
//        t.get()->setupShape(&box2d, startPos.x + trm * i, startPos.y, tr, 4, &colors[colorNum0], &sound[0]);
//        triangles.push_back(t);
//    }
//    for (int i=0; i<4; i++) {
//        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
//        t.get()->setupShape(&box2d, (startPos.x + trm * i) + 32, startPos.y + trm - 16, tr, 4, &colors[colorNum0], &sound[0]);
//        triangles.push_back(t);
//    }
//    for (int i=0; i<3; i++) {
//        shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
//        t.get()->setupShape(&box2d, (startPos.x + trm * i) + 64, startPos.y + trm + 40, tr, 4, &colors[colorNum0], &sound[0]);
//        triangles.push_back(t);
//    }
//}

//
//void ofApp::setCircles(){
////    cout << "start circle" << endl;
//    int r = 200;
//    ofVec2f startPos;
//    ofVec2f pos;
//    startPos.x = ofRandom(ofGetWidth()/2-400,ofGetWidth()/2+400);
//    startPos.y = ofRandom(ofGetHeight()/4,(ofGetHeight()/4)*3);
//    for (int i=0; i<24; i++) {
//        pos.x = startPos.x + (r - i*6) * cos(ofDegToRad(i*15));
//        pos.y = startPos.y + (r - i*6) * sin(ofDegToRad(i*15));
//        shared_ptr<CircleShape> c = make_shared<CircleShape>();
//        int cnt = 0;
//        if(i % 2 ==0){
//            cnt = 1;
//        }
//        c.get()->setupShape(&box2d, pos.x, pos.y,16, &colors[cnt], &sound[1]);
//        circles.push_back(c);
//    }
//    ofRemove(circles, shouldRemove);
//}
//void ofApp::setRects(){
//    ofVec2f pos;
//    pos.x = ofGetWidth()/2;
//    pos.y = 0;
//    shared_ptr<RectShape> r = make_shared<RectShape>();
//    r.get()->setupShape(&box2d, pos.x, pos.y, 16, &colors[1], &sound[0]);
//    rects.push_back(r);
//    ofRemove(rects, shouldRemove);
//}
//
//void ofApp::setTriangles(){
//    //    shared_ptr<TrianglePolyShape> t = make_shared<TrianglePolyShape>();
//    //    t.get()->setupShape(&box2d, pos.x, pos.y, &colors[1], &sound[0]);
//    //    triangles.push_back(t);
//    //    ofRemove(triangles, shouldRemove);
//}


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
