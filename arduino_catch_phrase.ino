#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);
int teamOneScore, teamTwoScore, wordIndex, timerSeconds = 0;
String selectedCategory = "";

//constant setting to control timer countdown
TIMERSETSECONDS = 30;

bool timerStart = true;

//initialize arraylist categories of words
//probably need to use a different arraylist type
char *testCat[] = {"Hello World", "Ass to Mouth", "Dog", "Wizz Palace", "Canada", "Hooters", "Nancy Pelosi"};
char *cat2[] = {"Michigan", "California", "Texas", "Twins"};
char *cat3[] = {"Bonfires", "Waterslide", "Tacos", "Steak", "Meijer", "Nancy Pelosi"};

String currentWord, previousWord;

char *currentCat[] = {};

int nextButton = 2;
int enterButton = 3;



void setup() {
    // put your setup code here, to run once:
    pinMode(nextButton, INPUT);
    digitalWrite(nextButton, HIGH);
    pinMode(enterButton, INPUT);
    digitalWrite(enterButton, HIGH);

    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Austin's CatchPhrase");
    lcd.setCursor(4,2);
    lcd.print("Press Enter");

    randomSeed(analogRead(0));

    waitForEnter();
    selectWord();
}

void timer() {
    seconds = TIMERSETSECONDS;
    while (timerStart) {
        delay(1000);
        seconds--;
        if (seconds == 0) {
            timerStart = false
        }
    }
}

void drawScreen() {
    //need to make it only clear display if any values changed
    if (previousWord != currentWord) {
        lcd.clear();
        showCategory();
        showScores();
        showCurrentWord();

        //this resets the previous variable values to match the current values
        //so that the drawScreen method wont continue to clear and redraw
        //will probably need to add scores, category, etc
        ResetPreviousValues();
    }

}

void ResetPreviousValues() {
    previousWord = currentWord;
}

void waitForEnter() {
    while (digitalRead(enterButton) == HIGH) {
        //nothing happens
    }
}

void nextWord() {
    wordIndex = random(sizeof(testCat));
    currentWord = String (testCat[wordIndex]);

    // delete currentWord (wordIndex)
    for (int i = wordIndex; i < (sizeof(testCat)); ++i)
        testCat[i] = testCat[i + 1]; // copy next element left
    showCurrentWord();

}

void showScores() {
    lcd.setCursor(0,3);
    lcd.print("Team1: " + String(teamOneScore));
    lcd.setCursor(11,3);
    lcd.print("Team2: " + String(teamTwoScore));
}

void showCurrentWord() {
    lcd.setCursor(0, 2);
    lcd.print("              ");
    lcd.setCursor(0, 2);
    lcd.print(String (testCat[wordIndex]));
}

void showCategory() {
    lcd.setCursor(0,1);
    lcd.print("Category: Countries");
}

void selectWord() {
    bool selected = false;
    while (!selected) {
        if (digitalRead(nextButton) == LOW) {
            previousWord = String (testCat[wordIndex]);
            wordIndex++;
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



void loop()
{
    //teamTwoScore = 3;
    //howCategory();
    //nextWord();
    //showScores();


    //selectWord();


}
