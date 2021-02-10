#include <Wire.h>
#include <LiquidCrystal_I2C.h>



LiquidCrystal_I2C lcd(0x27, 20, 4);
int teamOneScore, teamTwoScore, wordIndex, timerSeconds = 0;
String selectedCategory = "";

//constant setting to control timer countdown
int TIMERSETSECONDS = 20;

//boolean variable to start the timer back up at N seconds
bool timerStart = true;

//variable that starts the game loop when set to true
bool playing = false;

//list of different categories
char *categories[] = {"General", "The Office", "Michigan", "Politics"};
int categoryIndex = 0;

//initialize arraylist categories of words
//probably need to use a different arraylist type
char *testCat[] = {"Spilled Chilli", "George Foreman", "Benihana", "Pretzel Day", "Parkour", "Merger", "Niagara Falls", "All-Inclusive", "Baby back ribs", "Beet Farmer", "Cornell University", "Candles"};
char *cat2[] = {"Michigan", "California", "Texas", "Twins"};
char *cat3[] = {"Bonfires", "Waterslide", "Tacos", "Steak", "Meijer", "Nancy Pelosi"};

char currentWord, previousWord, currentCategory, previousCategory;

char *currentCat[] = {};

  int nextButton = 2;
  int enterButton = 3;




void setup() {
  // put your setup code here, to run once:
  pinMode(nextButton, INPUT);
  digitalWrite(nextButton, HIGH);
  pinMode(enterButton, INPUT);
  digitalWrite(enterButton, HIGH);

//used to randomly select words from categorical lists of words
randomSeed(analogRead(0));

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Austin's CatchPhrase");
  lcd.setCursor(4,2);
  lcd.print("Press Enter");
  //stopped working for some reason
  waitForEnter();
  //prevents HIGH status of enter button from prematmurely breaking selectCategory loop
  delay(300);

//setting previousCategory to "start" ensures it does not equal the currentWord
  //and prevent drawScreen from executing
  previousCategory = "start";
  selectCategory();
  delay(300);

//eventually playing and select word will need to be move to main loop
  playing = true;
  //setting previousWord to "start" ensures it does not equal the currentWord
  //and prevent drawScreen from executing
  previousWord = "start";
  selectWord();
}

//the beginning of a timer that will have to run with the gameplay in serial
//TODO: get timer working in main loop, add beeps that increase in speed the
//closer timer gets to 0
void timer() {
  timerSeconds = TIMERSETSECONDS;
  while (timerStart) {
    delay(1000);
    timerSeconds--;
    if (timerSeconds == 0) {
      timerStart = false;
    }
  }
}


//method that checks scores of both teams, if team reaches 7 points
//that team is the winner
void checkScores() {
  if (teamOneScore == 7) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Team one wins!");
    //run game end music
    //set playing value back to false
    playing = false;
  }
  if (teamTwoScore == 7) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Team two wins!");
    //run game end music
    //set playing value back to false
    playing = false;
  }
}

//method that clears screen and prompts user to select team
//that won round, adds point to corresponding time
void whoWonRound() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Who won this round?");
  lcd.setCursor(0,1);
  lcd.print("Press enter when");
  lcd.setCursor(0,2);
  lcd.print("team shown");
  bool decided = false;
  while (!decided) {
    lcd.setCursor(0,3);
    int team = 1;
    lcd.print("Team1");
    if (digitalRead(nextButton) == LOW) {
      int team = 2;
      lcd.print("Team2");
    }
    if (digitalRead(enterButton) == LOW) {
      if (team == 1) {
        teamOneScore++;
      }
      if (team == 2) {
        teamTwoScore++;
      }
    }
  }
}

//this draws all the text on the display
void drawScreen() {
  //need to make it only clear display if any values changed
  if (previousWord != currentWord || previousCategory != currentCategory) {
    lcd.clear();
    showCategory();
    showScores();
    //only show current word if users are playing the game
    if (playing) {
      showCurrentWord();
    }


    ResetPreviousValues();
  }

}

void selectCategory() {
  bool selected = false;
  while (!selected) {
    if (digitalRead(nextButton) == LOW) {
      previousCategory = char (categories[categoryIndex]);
      categoryIndex++;
      //wrap category index back to 0 if it gets larger than size of list
      if (categoryIndex > sizeof(categories)) {
        categoryIndex = 0;
      }
      currentCategory = categories[categoryIndex];
    }
    drawScreen();
    delay(100);
    if (digitalRead(enterButton) == LOW) {
      selected == true;
      break;
    }
  }
}

//this resets the previous variable values to match the current values
//so that the drawScreen method wont continue to clear and redraw
//will probably need to add scores, category, etc
void ResetPreviousValues() {
  previousWord = currentWord;
  previousCategory = currentCategory;
}

void waitForEnter() {
  while (digitalRead(enterButton) == HIGH) {
    //nothing happens
  }
}

//a random variable will need to eventually be used to choose words randomly
//from the arraylist of the chosen category.
void nextWord() {
  wordIndex = random(sizeof(testCat));
  currentWord = char (testCat[wordIndex]);

  // delete currentWord (wordIndex)
  for (int i = wordIndex; i < (sizeof(testCat)); ++i)
    testCat[i] = testCat[i + 1]; // copy next element left
    showCurrentWord();

}

//method that prints the team scores on the bottom of the screen
void showScores() {
  lcd.setCursor(0,3);
  lcd.print("Team1: " + String(teamOneScore));
  lcd.setCursor(11,3);
  lcd.print("Team2: " + String(teamTwoScore));
}

//method that displays the current word
void showCurrentWord() {
  lcd.setCursor(0, 2);
  lcd.print("              ");
  lcd.setCursor(0, 2);
  lcd.print(String (testCat[wordIndex]));
}

//method that shows the current select category (which is also an array list)
void showCategory() {
    lcd.setCursor(0,1);
    lcd.print("Category: " + String (categories[categoryIndex]));
}


//temporarily being used for simplicity reasons instead of the
//nextwork method because I haven't figured out arraylists and random
//in c++ yet
void selectWord() {
  bool selected = false;
  while (!selected) {
    if (digitalRead(nextButton) == LOW) {
      previousWord = char (testCat[wordIndex]);
      wordIndex++;
      currentWord = testCat[wordIndex];
    }
    drawScreen();
    delay(100);
    if (digitalRead(enterButton) == LOW) {
      selected == true;
    }
  }
}




void chooseCategory() {
//let the user cycle through categories (names of different array lists)
// and then select the category and make it active by copying it to current array list
}



//going to have to use the loop for actual game play so that the timer will work at the same time
void loop()
{
  //start timer


  //selectWord();

  //when timer hits 0
  //whoWonRound;


}
