#include "../include/front.h"
//#include "../../back/src/hangman.c"

char letterGrid[MAX_LETTERS]; // array of letter input //
int letterIndex = 0;         // index of letter enter //
char currentLetter = '\0'; 
char nameGrid[MAX_USERNAME];
int nameIndex = 0;

int resetAll() {
    letterGrid[MAX_LETTERS] = '\0';
    letterIndex = 0;
    currentLetter = '\0';

    return 0;
}

int showLetter() { 

    const int fontSize = 25;
    const int startX[] = {395, 440, 495, 550, 600};
    const int startY = 85;
    const int spacingY = 35; 

    for (int i = 0; i < letterIndex; i++) {
        
        int posX = startX[i % 5];                 
        int posY = startY + (i / 5) * spacingY;  
        DrawText(TextFormat("%c", letterGrid[i]), posX, posY, fontSize, BLACK); // it draw the letter with space in an area //
    }
    return 0;
}
int showLetterReset() { 

    const int fontSize = 25;
    const int startX[] = {395, 440, 495, 550, 600};
    const int startY = 85;
    const int spacingY = 35; 

    for (int i = 0; i < letterIndex; i++) {
        
        int posX = startX[i % 5];                 
        int posY = startY + (i / 5) * spacingY;  
        DrawText(TextFormat("%c", letterGrid[i]), posX, posY, fontSize, WHITE); // it draw the letter with space in an area //
    }
    return 0;
}

int checkInput(bool mouseOnText, Rectangle textBox, int *framesCounter, char *word, char *letterGuess) {
    int countHangman = -1; // Default to -1 (no input processed)
    int countLetter = 0;
    *letterGuess = '\0';
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed(); // Convert character input into ASCII
        if ((key >= 65) && (key <= 90)) { // Check for uppercase letters
            currentLetter = (char)key;
        }

        if (IsKeyPressed(KEY_ENTER) && letterIndex < MAX_LETTERS && currentLetter != '\0') {
            // Check if the letter has already been entered
            for (int i = 0; i < letterIndex; i++) { 
                if (currentLetter == letterGrid[i]) countLetter++;
            }

            // If the letter has not been entered before
            if (countLetter == 0) {
                letterGrid[letterIndex] = currentLetter; // Store the letter
                letterIndex++;
                *letterGuess = currentLetter; // Update guessed letter
                currentLetter = '\0'; // Reset current letter
                letterGrid[letterIndex] = '\0'; // Maintain null termination

                // Check if the guessed letter is in the word
                countHangman = readLetter(word, *letterGuess); // 0: Found, 1: Not Found
            }
        }
    }

    // Return countHangman, but only process guesses if the input was valid
    return countHangman;
}


int drawTextBox(bool mouseOnText, Rectangle textBox, int *framesCounter) {

    DrawRectangleRec(textBox, BLACK);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);

    if (currentLetter != '\0') {
        DrawText(TextFormat("%c", currentLetter), (int)textBox.x + 10, (int)textBox.y + 10, 30, WHITE);
    }
    if (mouseOnText)
    {
        if (((*framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 5 + MeasureText(&currentLetter, 25), (int)textBox.y + 10, 35, WHITE);
    }

    return 0;
}

int showDashesEasyMode(char *word) {

    const int fontSize = 35;
    const int startX[] = {200, 274, 348, 422, 495};

    for (int i = 0; i < strlen(word); i++) {
        
        int posX = startX[i % 5];                 
        int posY = 360;  
        DrawText(TextFormat("%c", word[i]), posX, posY, fontSize, BLACK); 
    }

    return 0;
}

int showDashesMediumMode(char *word) {

    const int fontSize = 35;
    const int startX[] = {200, 259, 318, 377, 436, 495};

    for (int i = 0; i < strlen(word); i++) {
        
        int posX = startX[i % 6];                 
        int posY = 360;  
        DrawText(TextFormat("%c", word[i]), posX, posY, fontSize, BLACK); 
    }

    return 0;
}

int showDashesHardMode(char *word) { // to show the world when a letter is discover //

    const int fontSize = 35;
    const int startX[] = {200, 249, 298, 347, 396, 445, 494};

    for (int i = 0; i < strlen(word); i++) { 
        
        int posX = startX[i % 7];                 
        int posY = 360;  
        DrawText(TextFormat("%c", word[i]), posX, posY, fontSize, BLACK);
    }

    return 0;
}

int displayRemainingAttempts(int remainingAttemps) {
    DrawText(TextFormat("Remaining : %d", remainingAttemps), 480, 320, 25, BLACK);
    return 0;
}

int displayWinMessage() {
    DrawText("Congratulation, you found the word!", 130, 35, 25, BLACK);
    return 0;
}

int displayLooseMessage() {
    DrawText("Unfortunately, you didn't find the word!", 130, 35, 25, BLACK);
    return 0;
}

char* checkInputNameClassic(bool mouseOnText, Rectangle textBox, GameState *currentState) {

    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true; // if we put the mouse on the textbox //
    else mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();
        if ((key >= 33) && (key <= 126)) { 
            nameGrid[nameIndex] = (char)key; 
            nameGrid[nameIndex+1] = '\0';
            nameIndex++;
        }

        if (IsKeyPressed(KEY_ENTER) && nameIndex < MAX_USERNAME) *currentState = STATE_CLASSIC;

        if (IsKeyPressed(KEY_BACKSPACE)) {
            nameIndex --;
            nameGrid[nameIndex] = '\0';
            if (nameIndex < 0) nameIndex = 0;
        }
    }

    return nameGrid;
}

char* checkInputNameClock(bool mouseOnText, Rectangle textBox, GameState *currentState) {

    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true; // if we put the mouse on the textbox //
    else mouseOnText = false;

    if (mouseOnText) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();
        if ((key >= 33) && (key <= 126)) { 
            nameGrid[nameIndex] = (char)key; 
            nameGrid[nameIndex+1] = '\0';
            nameIndex++;
        }

        if (IsKeyPressed(KEY_ENTER) && nameIndex < MAX_USERNAME) *currentState = STATE_CLOCK;

        if (IsKeyPressed(KEY_BACKSPACE)) {
            nameIndex --;
            nameGrid[nameIndex] = '\0';
            if (nameIndex < 0) nameIndex = 0;
        }
    }

    return nameGrid;
}

int drawTextBoxName(bool mouseOnText, Rectangle textBox, int framesCounter) {

    Color clear = {255, 255, 255, 0};
    DrawRectangleRec(textBox, clear);

    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, WHITE);

    DrawText("Enter your username below : ", 160, 150, 25, WHITE);
    DrawText(nameGrid, (int)textBox.x + 10, (int)textBox.y + 10, 30, WHITE);

    if (mouseOnText)
    {
        if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 5 + MeasureText(nameGrid, 25), (int)textBox.y + 10, 35, WHITE);
    }

    return 0;
}
