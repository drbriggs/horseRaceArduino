#define TO_LANES    2
#define GAME_LIGHTS 13
#define GAME_BUTTON 12
#define FROM_LANE1  7
#define FROM_LANE2  8
#define FROM_LANE3  9
#define LED_LANE1   3
#define LED_LANE2   5
#define LED_LANE3   6



void setup() {
  Serial.begin(9600);
  // Configure Control Pin and set it low
  pinMode(TO_LANES, OUTPUT);
  digitalWrite(TO_LANES, LOW);
  Serial.println("Set TO_LANES Low");
  // Configure pins to read game status from lane nanos
  pinMode(FROM_LANE1, INPUT);
  pinMode(FROM_LANE2, INPUT);
  pinMode(FROM_LANE3, INPUT);
  // Configure pins for game controls
  pinMode(GAME_BUTTON, INPUT_PULLUP);
  pinMode(GAME_LIGHTS, OUTPUT);
  digitalWrite(GAME_LIGHTS, LOW);
  // Configure Lane Winner Lights
  pinMode(LED_LANE1, OUTPUT);
  pinMode(LED_LANE2, OUTPUT);
  pinMode(LED_LANE3, OUTPUT);
  
  flashLed(3);
}

int gameState = LOW;
int newButtonVal;
int oldButtonVal = 1; 
int isWinner = 0;

void loop() {
  // Check the game play button state
  newButtonVal = digitalRead(GAME_BUTTON);
  // If the game is not currently running
  if (gameState == LOW){
    // If the button was pressed start the game
    if (oldButtonVal == 1 && newButtonVal == 0){
      gameState = HIGH;
      digitalWrite(GAME_LIGHTS, HIGH);
      isWinner = 0;
    }
  } else { // The game is currently running
    //Check for a winner
    if (digitalRead(FROM_LANE1) == HIGH){
      //Player 1 WON!! Turn on Lane LED
      // TODO: is there anything else to do for the winner?
      digitalWrite(LED_LANE1, HIGH);
      isWinner = 1;
    }
    if (digitalRead(FROM_LANE2) == HIGH){
      //Player 2 WON!! Turn on Lane LED
      // TODO: is there anything else to do for the winner?
      digitalWrite(LED_LANE2, HIGH);
      isWinner = 2;
    }
    if (digitalRead(FROM_LANE3) == HIGH){
      //Player 3 WON!! Turn on Lane LED
      // TODO: is there anything else to do for the winner?
      digitalWrite(LED_LANE3, HIGH);
      isWinner = 3;
    }
    // If someone won, send signal to reset the game
    if (isWinner > 0) {
      //Is there something to do here about who won?
      //Turn the game off
      gameState = LOW;
    }
  }
  oldButtonVal = newButtonVal;
}

void setWinner(int winnerLane) {
  
}

void flashLed(int numFlash) {
  for (int i = 0; i < numFlash; i++) { 
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
    delay(250);
  }
}
