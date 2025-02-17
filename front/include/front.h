#include <stdio.h>
#include "raylib.h"

#ifndef FRONT_H_INCLUDED
#define FRONT_H_INCLUDED

#define MAX_LETTERS 26
#define MAX_USERNAME 12
#define TOTAL_IMAGES 7

int showMainWindow();
int showSettingWindow();
int showChoiceGameMode();
int showLetter();
int resetAll();
int checkInput(bool mouseOnText, Rectangle textBox, int *framesCounter, char *word, char *letterGuess);
int drawTextBox(bool mouseOnText, Rectangle textBox, int *framesCounter);
int drawTextBoxName(bool mouseOnText, Rectangle textBox, int framesCounter);
int displayLooseMessage();
int displayWinMessage();
int displayRemainingAttempts(int remainingAttemps);
int showDashesHardMode(char *word);
int showDashesMediumMode(char *word);
int showDashesEasyMode(char *word);


#endif
