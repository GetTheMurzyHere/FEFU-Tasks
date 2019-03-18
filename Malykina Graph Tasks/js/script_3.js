function setup() {
    createCanvas(500, 500);
}

function draw() {
    const sizeCoef = 100;
    ellipse(250, 250, 4 * sizeCoef, 3 * sizeCoef);
    line(0, 250, 500, 250);
    line(250, 500, 250, 0);
    textSize(22);
    text('y', 255, 15);
    text('x', 482, 245);
    noLoop();
}