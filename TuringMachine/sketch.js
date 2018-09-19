var currentTape;
var currentPos = 0;
var currentState;
var stack;
var printing=false;
var running=false;

function displayTape() {
  console.log("Displaying("+currentTape.join("")+","+currentPos+")");
  document.getElementById("mid").innerHTML= "";
  for (var i = 0; i<currentTape.length; i++) {
    if (i==currentPos) {
      document.getElementById("mid").innerHTML+= "<div class=\"el grey\">"+currentTape[i]+"</div>";
    }else{
      if (currentTape[i]=="1") {
        document.getElementById("mid").innerHTML+= "<div class=\"el black\">"+currentTape[i]+"</div>";
      }else{
        document.getElementById("mid").innerHTML+= "<div class=\"el white\">"+currentTape[i]+"</div>";
      }
    }
  }
  document.getElementById("result").innerHTML=currentTape.join("");
}


function addTape() {
  console.log("Moving input to tape");
  currentTape=document.getElementById('inputtape').value.split("");
  currentPos=0;
  displayTape();
  document.getElementById("turing").disabled=false;
  document.getElementById("inputtape").value="";
}

function moveRight() {
  console.log("MovingRight");
  anime({
    targets: '.el',
    translateX:{
      value:'-=80',
      duration:1500
    }, complete (anim){

    }
  });
  currentPos =currentPos+ 1;
  //displayTape();
}


function stopMachine() {
  console.log("The Turing Machine stopped");
  document.getElementById('inputtape').disabled=false;
  document.getElementById('turing').disabled=false;
  document.getElementById('sendbtn').disabled=false;
  document.getElementById("result").innerHTML="The result is: "+currentTape.join("");
}

function Turing(){
  if (currentPos >=currentTape.length) {
      for (var i = 0; i < stack.length; i++) {
        currentTape.splice(currentPos,0,1);
        stack.pop();
        moveRight();
      }
      displayTape();
      return stopMachine();
  }
  switch (currentState) {
    case 0://Start
    if (currentTape[currentPos]=='0') {
      moveRight();
      Turing();
    }else{
      stack.push(1);
      currentState=1;
      console.log("stack:"+stack);
      moveRight();
      Turing();
    }
    break;

    case 1:
    if (currentTape[currentPos]=='0') {
      for (var i = 0; i < stack.length; i++) {
        currentTape.splice(currentPos,0,1);
        stack.pop();
        currentPos++;
      }
      stack=["z"]
      currentState=0;
      moveRight();
      Turing();
    }else{
      stack.push(1);
      console.log("stack:"+stack);
      moveRight();
      Turing();
    }
    break;
  }
}

function startMachine() {
  document.getElementById('inputtape').disabled=true;
  document.getElementById('turing').disabled=true;
  document.getElementById('sendbtn').disabled=true;
  stack=["z"]
  currentState=0;
  Turing();
}
