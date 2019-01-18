
let typeNum = 34;
function setup(){
    createCanvas(windowWidth, windowHeight);
    background(0);
    let url = 'js/dots.json';
    loadJSON(url, drawJSON);
}

function draw() {
    background(0);
    
    display();
}

function drawJSON(data) {
    // Get the magnitude and name of the earthquake out of the loaded JSON
    console.log(data.alphabets[0].pos.length);

    let alphabet = data.alphabets[typeNum];
    display(alphabet);
}   

function display(alphabet){
    for (let i = 0; i < alphabet.pos.length; i++) {
        fill(255, 0, 0);
        ellipse(alphabet.pos[i].x / 2, alphabet.pos[i].y / 2, 24, 24);
    }
}



// function setCanvas(aCharArr){
//     setTimeout(() => {
//         flags.canvas = true;
//     }, 400);

//     for (var i = 0; i < aCharArr.length; i++) {
//         dotsObj.char[i] = aCharArr[i];
//         sendObj.char[i] = aCharArr[i];
//         //インスタンスの生成
//         // typeArr[i] = new Sequencer(aCharArr[i],i);
//         // typeArr[i].setup();
//         dotsObj.typeArr[i] = new Sequencer(aCharArr[i],i);
//         dotsObj.typeArr[i].init();

//         dotsObj.width[i] = dotsObj.typeArr[i].getPos();
//         dotsObj.pos.push(dotsObj.width[i] + dotsObj.pos[i]);
//         dotsObj.totalWidth += dotsObj.width[i];

//         console.log(dotsObj.typeArr[i].send());
//         // $('#defaultCanvas0').attr('width',dotsObj.totalWidth).attr('height',winH*2).css('width',dotsObj.totalWidth/2).css('height',winH);
//         sendObj.typeArr[i] = dotsObj.typeArr[i].send();
//     }

// }





