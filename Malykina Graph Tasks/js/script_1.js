function getRandomArbitrary(min, max) {
    return Math.random() * (max - min) + min;
}

function setup() {
    createCanvas(500, 500);
    frameRate(20);
}


let count = 0;

function inputDraw(currCount) {
    count = currCount;
}

function draw() {
    strokeWeight(5);
    clear();
    if (count == 0) {
        clear();
        line(0, 25, 500, 25);
        line(150, 475, 350, 475);
        return;
    }

    if (count == 1) {
        stroke(getRandomArbitrary(1, 255), getRandomArbitrary(1, 255), getRandomArbitrary(1, 255));
        line(250, 25, 250, 475);
        stroke(getRandomArbitrary(0, 0, 0));
        line(0, 25, 500, 25);
        line(150, 475, 350, 475);
        return;
    }

    var x1, x2, rangeX1, rangeX2;
    x1 = 0; x2 = 150;
    rangeX1 = 500 / (count - 1);
    rangeX2 = 200 / (count - 1);

    for (var i = 0; i < count; i++) {
        if (i == 0 || i == count - 1) {
            stroke(0, 0, 0);
        }
        else {
            stroke(getRandomArbitrary(1, 255), getRandomArbitrary(1, 255), getRandomArbitrary(1, 255));
        }
        line(x1, 25, x2, 475);
        x1 += rangeX1;
        x2 += rangeX2;
    }

    stroke(0, 0, 0);
    line(0, 25, 500, 25);
    line(150, 475, 350, 475);
}