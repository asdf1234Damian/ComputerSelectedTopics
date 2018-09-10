var currentTape;
var currentPos;
var stack;
var running=false;
function displayTape(tape,start) {
  document.getElementById("mid").innerHTML= "";
  for (var i = start; i <start+9 && i<tape.length; i++) {
    if (i==start) {
      document.getElementById("mid").innerHTML+= "<div class=\"el grey\">"+tape[i]+"</div>";
    }else{
      if (tape[i]=="1") {
      document.getElementById("mid").innerHTML+= "<div class=\"el black\">"+tape[i]+"</div>";
      }else{
      document.getElementById("mid").innerHTML+= "<div class=\"el white\">"+tape[i]+"</div>";
      }
    }
  }
  document.getElementById("result").innerHTML=tape;
}

function addTape() {
  currentTape=document.getElementById('inputtape').value;
  currentPos=0;
  displayTape(currentTape,currentPos);
  document.getElementById("turing").disabled=false;
  document.getElementById("inputtape").value="";
}

function moveRight(tape,start) {
  anime({
    targets: '.el',
    translateX:{
      value:'+=80',
      duration:1500
    }, complete (anim){
      currentPos+=1;
      displayTape(currentTape,currentPos);
    }
  });
}

function moveLeft(tape,start) {
  anime({
    targets: '.el',
    translateX:{
      value:'-=80',
      duration:1500
    },
    complete: function(anim){
      currentPos-=1;
      displayTape(currentTape,currentPos);
    }
  });
}

function automata(currentTape,currentPos) {
  if(currentTape[currentPos]==0){
    if (stack=) {

    }
  }
}

function startMachine() {
  document.getElementById('inputtape').disabled=true;
  document.getElementById('turing').disabled=true;
  document.getElementById('sendbtn').disabled=true;

}

function stopMachine() {
  document.getElementById('inputtape').disabled=false;
  document.getElementById('turing').disabled=false;
  document.getElementById('sendbtn').disabled=false;
}
