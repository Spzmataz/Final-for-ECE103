#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

int switchpin = 7;
int leftbutton = 4;
int rightbutton = 5;
bool gamestart = false;
bool moveright = false;
bool moveleft = false;
int charpos = 0;
int gamestate = 0;
bool victory = false;

void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  attachInterrupt(digitalPinToInterrupt(switchpin), game, RISING);
  attachInterrupt(digitalPinToInterrupt(leftbutton), left, FALLING);
  attachInterrupt(digitalPinToInterrupt(rightbutton), right, FALLING);
}

void game(){
  gamestart = true;
}
void left(){
  colorOne(charpos,0,0,0);
  charpos--;
  colorOne(charpos,255,165,0);
  delay(25);
  if (charpos >= 10){
    charpos = 0;
  }
  else if(charpos < 0){
    charpos = 10;
  }
  
}
void right(){
  colorOne(charpos,0,0,0);
  charpos++;
  colorOne(charpos,255,165,0);
  delay(25);
  if (charpos >= 10){
    charpos = 0;
  }
  else if(charpos < 0){
    charpos = 10;
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  if(gamestart == true){

    //set up for the game
    for (int i = 0; i < 5; i++){
      colorAll(255,255,255);
      delay(250);
      colorAll(0,0,0);
      delay(250);
    }
    colorAll(0,0,0);
    colorOne(charpos,255,165,0);

    //scoring and gamestuff 
    delay(1000);
    Serial.println("Game is beginning");
    int level = 1;
    bool gameover = false;
    Serial.println(gamestate);
    //correct or incorrect


    Serial.println(level);
    levels(level);

    while(gameover != true){
      
    if (gamestate == 1){
      victory = false;
      gameover = true;
    }
    else if(gamestate == 2){
      level++;
      gamestate = 0;
      Serial.println(level);
      levels(level);
    }

    if (victory == true){
      Serial.println("Good job you won! +5 to final score");
      for (int i = 0; i < 5; i++){
        colorAll(0,0,0);
        delay(250);
        colorAll(0,255,0);
        delay(250);
      }
      level = level + 5;
      gameover = true;
    }
    if (gameover == true){
      Serial.println("you're score was: ");
      Serial.print(level);
      gamestart = false;
    }
    }
  }

    

}

int gamefunc(int timer, int rLow, int rHigh, int chara){
  int pointer = random(rLow,rHigh);
  colorOne(pointer,255,255,255);
  Serial.println("Working!");
  int time = (10-timer);
  while(time >= 0){ 
    chara = charpos;
    Serial.println("you have: ");
    Serial.print(time);
    Serial.println(" Seconds left");
    time--;
    delay(1000);
    if (chara == pointer){
      Serial.println("success");
      return 2;
    }
  }
  Serial.println("failed");
  return 1;
}

void levels(int level){
  switch (level){
    case 1: gamestate = gamefunc(0,3,8,charpos); break;
    case 2: gamestate = gamefunc(0,2,8,charpos); break;
    case 3: gamestate = gamefunc(0,1,10,charpos); break;
    case 4: gamestate = gamefunc(1,1,10,charpos); break;
    case 5: gamestate = gamefunc(2,1,10,charpos); break;
    case 6: gamestate = gamefunc(3,1,10,charpos); break;
    case 7: gamestate = gamefunc(4,1,10,charpos); break;
    case 8: gamestate = gamefunc(5,1,10,charpos); break;
    case 9: gamestate = gamefunc(6,1,10,charpos); break;
    default: victory = true; break;
  }
}

void colorAll(float red, float green, float blue) {
  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i, red, green, blue); 
  }
  
}
void colorOne(int index, float red, float green, float blue) {
  CircuitPlayground.setPixelColor(index, red, green, blue); 

}