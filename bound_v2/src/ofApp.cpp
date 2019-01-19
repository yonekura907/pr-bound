#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowShape(1280, 800);
    ofSetFullscreen(true);
    ofBackgroundHex(0xFFFFFF);
    ofSetVerticalSync(true);
    //    ofSetLogLevel(OF_LOG_NOTICE);
    
    //OSC設定
    sender.setup(HOST,SEND_PORT);
    
    //Box2dの初期設定
    box2d.init();
    box2d.setGravity(0, 9.8);
    //    box2d.createBounds();
    box2d.setFPS(60.0);
    box2d.registerGrabbing(); //本番では外す　オブジェクトを掴めるように
    
    //シーンクラスの生成
    bScene = make_unique<BoundScene>(&box2d);
    bScene->setup();
    
    //ボールの生成
    auto b = std::make_shared<Ball>();
    b.get()->setupBall(ofGetWidth()/2, ofGetHeight()/2, &box2d);
    ballPos.set(ofGetWidth()/2,ofGetHeight()/2);
    balls.push_back(b);


    //see how many devices we have.
    ofxKinectV2 tmp;
    vector <ofxKinectV2::KinectDeviceInfo> deviceList = tmp.getDeviceList();
    
    //allocate for this many devices
    kinects.resize(deviceList.size());
    texDepth.resize(kinects.size());
    texRGB.resize(kinects.size());
    
    panel.setup("", "settings.xml", 10, 400);
    
    //Note you don't have to use ofxKinectV2 as a shared pointer, but if you want to have it in a vector ( ie: for multuple ) it needs to be.
    for(int d = 0; d < kinects.size(); d++){
        kinects[d] = shared_ptr <ofxKinectV2> (new ofxKinectV2());
        kinects[d]->open(deviceList[d].serial);
        panel.add(kinects[d]->params);
    }
    
    panel.loadFromFile("settings.xml");
    
    // rgb 1920, 1080
    // depth 512, 424
    displaySize.x = 512;
    displaySize.y = 424;
    
    colorImg.allocate(displaySize.x, displaySize.y);
    grayImage.allocate(displaySize.x, displaySize.y);
    grayBg.allocate(displaySize.x, displaySize.y);
    grayDiff.allocate(displaySize.x, displaySize.y);
    //背景の学習モードを真に
    bLearnBakground = true;
    //閾値を100に
    threshold = 100;
    
    //物体検出する面積の最小値、最大値
    boundingAreaMin = 4000;
    boundingAreaMax = 20000;
    
    //boundYの初期設定
    groundY = 1000;
    thresholdGroundY = 60;
    
    prePos = ofVec2f(0, 0);
    
    // boundをoff
    bound = false;
}


//--------------------------------------------------------------
void ofApp::update(){
    //新規にフレームを取り込んだかを判定する変数
    bool bNewFrame = false;
    
    for(int d = 0; d < kinects.size(); d++){
        kinects[d]->update();
        if( kinects[d]->isFrameNew() ){
            bNewFrame = kinects[d]->isFrameNew();
        }
    }
    
    //新規のフレームの場合とりこみ実行
    if (bNewFrame){
        
        for(int d = 0; d < kinects.size(); d++){
            grayImage.setFromPixels(kinects[d]->getDepthPixels());
        }
        //新規に背景を記録する場合
        if (bLearnBakground == true){
            //現在の取り込んだグレースケールイメージを記憶
            grayBg = grayImage;
            //背景の記録をしないモードに戻す
            bLearnBakground = false;
        }
        //背景画像と現在の画像の差分の絶対値を取得
        grayDiff.absDiff(grayBg, grayImage);
        //差分画像を設定した閾値を境に二値化
        grayDiff.threshold(threshold);
        //二値化した差分画像から、輪郭を抽出する
        contourFinder.findContours(grayDiff, 20, (displaySize.x * displaySize.y), 1, false);
    }
    
    // キネクトからボールの座標取得
    for (int i=0; i < contourFinder.nBlobs; i++) {
        pos = contourFinder.blobs[i].boundingRect.getCenter();
        // 検出した領域の面積を計算
        boundingArea = contourFinder.blobs[i].boundingRect.width * contourFinder.blobs[i].boundingRect.height;
    }
    
    if(boundingArea > boundingAreaMin && boundingArea < boundingAreaMax){
        // ボールのy軸スピードを取得
        speedY = prePos.y - pos.y;
        // バウンドの検出(地面からthreshold分上 && y軸の上方向に動いた時)
        if(pos.y > (groundY - thresholdGroundY) && speedY > 0){
            bound = true;
//            cout << "バウンドしたよ, ";
        }else{
            bound = false;
        }
        // 現在のpos.yを1フレーム前のpos.yに保存する
        prePos.y = pos.y;
    }
    
    // ballPosの更新
    // depth 512, 424
    ballPos.x = ofMap(pos.x, 0, 512, 0, ofGetWidth());
    ballPos.y = ofMap(pos.y, 0, 424, 0, ofGetHeight());
    
    // ボールの落下
    for(auto & b : balls) {
        //ボールの値の更新kinectの値を入れる
        b->updateBall(ballPos.x, ballPos.y);
        // アドレスを設定
        //        ofxOscMessage msg;
        //        msg.setAddress("/ballDown");
        //        cout << "noteNum: " << noteNum << endl;
        //        cout << "accelerationCount: " << b->accelerationCount << endl;
        //ここはkinectでは消してください
//        if(b->accelerationCount >= 1){
            //            msg.addIntArg(b->accelerationCount);
            // OSC送信
            //            sender.sendMessage(msg);
            //シェイプの落下 --------------------
            //シーンクラスのupdateここはkinectでも必要
        if(bound){
            bScene->update();
        }    //ボールの値をリセット
//            b.get()->reset(); //ここはkinectでは消してください
//        }
    }
    box2d.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ボールの描画
//    if(boundingArea > boundingAreaMin && boundingArea < boundingAreaMax){
        for(auto & b : balls) {
            b->display();
        }
//    }
    
    //シーンクラスのdraw
    bScene->draw();
    
//    //取り込んだ画像を表示
//    ofDrawRectangle(0, 0, displaySize.x, displaySize.y);
//    //グレースケールに変換した画像を表示
//    grayImage.draw(displaySize.x + 20,0, displaySize.x, displaySize.y);
//    //    //学習した背景画像を表示
//    grayBg.draw(0,displaySize.y + 20, displaySize.x, displaySize.y);
//    //    //背景画像と現在の画像との差分を表示
//    grayDiff.draw(displaySize.x + 20,displaySize.y + 20, displaySize.x, displaySize.y);
    //抽出した輪郭線の情報を描画する
    if(boundingArea > boundingAreaMin && boundingArea < boundingAreaMax){
        contourFinder.draw(0, 0, displaySize.x, displaySize.y);
    }
    
    // finally, a report:
    ofSetHexColor(0xffffff);
    stringstream reportStr;
    reportStr << "thresholdGroundY " << thresholdGroundY << " (press: +/-)" << endl
    << "objectX " << pos.x << endl
    << "objectY " << pos.y << endl
    << "boundingArea： " << boundingArea;
    ofDrawBitmapString(reportStr.str(), 20, 600);
    
    panel.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ': //スペースキーで背景を学習モードに
            bLearnBakground = true;
            break;
        case '+': //[+]キーで地面の閾値のレベルを下側(最大255)
            thresholdGroundY ++;
            if (thresholdGroundY > 255) thresholdGroundY = 255;
            break;
        case '-': //[-]キーで地面の閾値の上側にする(最小0)
            thresholdGroundY --;
            if (thresholdGroundY < 0) thresholdGroundY = 0;
            break;
        case 'd': //[d]キーでボールと地面が設置したy座標をとる
            groundY = pos.y;
            break;
    }
    
    // Bを押すとボールが戻ってくる
    if(key == 'b') {
        balls.clear();
        auto b = std::make_shared<Ball>();
        b.get()->setupBall(ofGetWidth()/2, ofGetHeight()/2, &box2d);
        balls.push_back(b);
    }
    // Cを押すとシェイプがクリア
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
void ofApp::dragEvent(ofDragInfo dragInfo){}
