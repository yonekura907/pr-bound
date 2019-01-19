//
//  Ground.hpp
//  bound
//
//  Created by yonekuraakio on 2019/01/19.
//

#ifndef Ground_hpp
#define Ground_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxBox2d.h"


class Ground{
public:
    
    Ground(ofxBox2d *world);
    
    void setup();
    void update();
    void draw();
    //地面の描画　確認用
    
    ofxBox2d *box2d;
    ofPolyline groundLine;
};

#endif /* Ground_hpp */
