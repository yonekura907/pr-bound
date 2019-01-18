// Sequencerクラス

class Sequencer {
    constructor(aTypeChar, aTypeCount) {
        this.typeChar = aTypeChar;
        this.typeAlphabetCount;
        this.typeWidth;
        this.trX;
        this.posVec = [];
        this.dist = [];
        this.isClick = [];
        this.typeCount = aTypeCount; // 何文字目か
        this.loopCount = 0; // ループカウント
        this.sqArrLength; //アルファベットの中にあるドットの数
        this.radius = 40;
        this.sqArr = [];
        this.speedVec = []; // 速度を保存
        this.env; //
        this.osc;
        this.sustainTime;
        this.isFall = [];
    }

    init(){
        // 選んだアルファベットがaplhabetの何番目か調べる
        for (var i = 0; i < window.alphabet.length; i++) {
            if(window.alphabet[i].string == this.typeChar){
                this.typeAlphabetCount = i;
            }
        }

        // ドットの数を保存
        this.sqArrLength = window.alphabet[this.typeAlphabetCount].pos.length;


        for (var i = 0; i < this.sqArrLength; i++) {
            this.sqArr[i] = 0;
            this.isClick[i] = false;
            this.isFall[i] = false;
        }

        this.setup();

    }

    send(){
        return this.sqArr;
    }


    setup(){
        // 選んだアルファベットがaplhabetの何番目か調べる
        // for (var i = 0; i < window.alphabet.length; i++) {
        //     if(window.alphabet[i].string == this.typeChar){
        //         this.typeAlphabetCount = i;
        //     }
        // }

        // 何文字目かでX座標をずらす
        this.trX = dotsObj.pos[this.typeCount];


        // ドットの数を保存
        // this.sqArrLength = window.alphabet[this.typeAlphabetCount].pos.length;


        for (var i = 0; i < this.sqArrLength; i++) {
            this.posVec[i] = new p5.Vector();
            this.posVec[i].x = (window.alphabet[this.typeAlphabetCount].pos[i].x + this.trX) /2;
            this.posVec[i].y = window.alphabet[this.typeAlphabetCount].pos[i].y/2;
            // this.sqArr[i] = 0;
            // this.isClick[i] = false;
            // this.isFall[i] = false;
            this.speedVec[i] = new p5.Vector();
            this.speedVec[i].x = Math.floor(random(-10, 10));
            this.speedVec[i].y = Math.floor(random(-10, 10));
            this.speedVec[i].z = Math.floor(random(-10, 10));
        }

        this.oscillator();

    }

    update(){
        if(frameCount % 12 ===0){
            this.loopCount++;
        }

        if(this.loopCount >= this.sqArrLength){
            this.loopCount=0;
        }

        for (var i = 0; i < this.sqArrLength; i++) {

            if(this.sqArr[this.loopCount] !==0){
                this.env.play(this.osc, 0, this.sustainTime);// 再生
            }


            if (this.isFall[i]) {
                this.posVec[i].x += this.speedVec[i].x;
                this.posVec[i].y += this.speedVec[i].y;
                this.posVec[i].z += this.speedVec[i].z;
            }
        }



    }


    draw(){
        fill(150, 150, 150);
        for (var i = 0; i < this.sqArrLength; i++) {
            noStroke();
            if(this.sqArr[i] == 1){
                // fill(255, 150, 0);
                fill(window.colorData[i].r, window.colorData[i].g, window.colorData[i].b);
            } else {
                fill(200,100);
            }
            ellipse(this.posVec[i].x, this.posVec[i].y, this.radius, this.radius);

            if(i == this.loopCount){
                fill(178,100);
                ellipse(this.posVec[i].x, this.posVec[i].y, this.radius+10, this.radius+10);
            }
        }
    }


    tap(aX, aY){
        for (var i = 0; i < this.sqArrLength; i++) {
            this.dist[i] = dist(this.posVec[i].x, this.posVec[i].y, aX, aY);
            // タップの領域を指定、元の座標が2倍なので半径の半分にしている
            if (this.dist[i] <= this.radius/2) {

                this.isClick[i] = !this.isClick[i];

                if(this.isClick[i]){
                    this.sqArr[i] = 1;
                } else {
                    this.sqArr[i] = 0;
                }
            }
        }
        // console.log(this.sqArr);
    }


    fall(){
        console.log('fall !!!!!!!!!');
        for (var i = 0; i < this.sqArrLength; i++) {
            this.isFall[i] = true;

        }
    }

    getPos(){
        // 文字の幅
        this.typeWidth = window.alphabet[this.typeAlphabetCount].width;
        return this.typeWidth;
    }

    oscillator(){
        //オシレーターの生成
        var freqValue = midiToFreq(scaleArray[this.typeCount]);

        // エンベロープの設定
        var attackTime = 0.001; // 最大音に到達する時間
        var attackLevel = 0.9; // 最大レベル
        var decayTime = 0.3; // 持続音に達する時間
        var susPercent = 0.2; // 持続レベル
        this.sustainTime = 0.1; // 音を持続する時間
        var releaseTime = 0.5; // 音が消えるまでの時間
        var releaseLevel = 0; // 消えるレベル


        // オシレーターの生成
        this.osc = new p5.Oscillator('sine');
        this.osc.amp(0);
        this.osc.start();
        this.osc.freq(freqValue);

        this.env = new p5.Env();
        this.env.setADSR(attackTime, decayTime, susPercent, releaseTime);
        this.env.setRange(attackLevel, releaseLevel);
    }



};
