function getRandomArbitrary(min, max) {
    return Math.random() * (max - min) + min;
}

function setup() {
    createCanvas(500, 500);
    frameRate(20);
}

let count = 0;
let startColor = 'FF0000';
let endColor = '00FF00';

let dR = (parseInt(endColor[0] + endColor[1], 16) - parseInt(startColor[0] + startColor[1], 16))/count;
let dG = (parseInt(endColor[2] + endColor[3], 16) - parseInt(startColor[2] + startColor[3], 16))/count;
let dB = (parseInt(endColor[4] + endColor[5], 16) - parseInt(startColor[4] + startColor[5], 16))/count;

function inputDraw(currCount) {
    count = currCount;

    dR = (parseInt(endColor[0] + endColor[1], 16) - parseInt(startColor[0] + startColor[1], 16)) / count;
    dG = (parseInt(endColor[2] + endColor[3], 16) - parseInt(startColor[2] + startColor[3], 16)) / count;
    dB = (parseInt(endColor[4] + endColor[5], 16) - parseInt(startColor[4] + startColor[5], 16)) / count;

}

function draw() {
    strokeWeight(0);
    if (count == 0) {
        clear();
        return;
    }

    let r = 250, range = r / count;
    for (let i = 0; i < count; i++) {
        fill(parseInt(startColor[0] + startColor[1], 16) + dR * i, parseInt(startColor[2] + startColor[3], 16) + dG * i, parseInt(startColor[4] + startColor[5], 16) + dB * i);
        circle(250, 250, r);
        r -= range;
    }
}