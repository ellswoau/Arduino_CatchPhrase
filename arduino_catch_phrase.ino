#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);
int teamOneScore, teamTwoScore, wordIndex = 0;
String selectedCategory = "";

//initialize arraylist categories of words
//probably need to use a different arraylist type
char *testCat[] = {"Hello", "World", "Dog", "Wizz Palace", "Canada", "Hooters"};
char *cat2[] = {"Michigan", "California", "Texas", "Twins"};
char *cat3[] = {"Bonfires", "Waterslide", "Tacos", "Steak", "Meijer", "Nancy Pelosi"};

String currentWord;

char *currentCat[] = {};


void setup() {
    // put your setup code here, to run once:
    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Austin's CatchPhrase");
    showCategory();
    showScores();

    randomSeed(analogRead(0));
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
    lcd.print(currentWord);
}

void showCategory() {
    lcd.setCursor(0,1);
    lcd.print("Category: Countries");
}





void chooseCategory() {
//let the user cycle through categories (names of different array lists)
// and then select the category and make it active by copying it to current array list
}



void loop()
{
    teamTwoScore = 3;
    showCategory();
    nextWord();
    showScores();


    //start counter
    nextWord();
    lcd.setCursor(4, 2);
    lcd.print("Whiz Palace");

}
