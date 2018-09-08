var tape;

function setup() {
  var canvasw = windowWidth;
  var canvash = windowHeight;
  createCanvas(canvasw/3,canvash/2)
  tape = new inputTape();
}

function draw() {
  background(100);

  tape.display();
}

function inputTape() {
  this.size=7;
  this.display = function(){
    for (var i = 0; i < this.size; i++) {
      if (i%2==0) {
        fill('white')
      } else {
        fill('black')
      }
      rect(i*100/7,200,100,100);
    }
  }

}
