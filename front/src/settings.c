#include "../../back/src/hangman.c"
#include "../include/front.h"   

int showSettingWindow() { // shows the window of setting. You can acces to this window when you at the page 1 and page 2 //

    Rectangle back = {35, 80, 600, 300};
    Rectangle setting = {235, 20, 200, 50};
    Rectangle backDark1 = {45, 100, 580, 80};
    Rectangle backDark2 = {45, 190, 580, 80};
    Rectangle backDark3 = {45, 280, 580, 80};
    Rectangle minus1 = {350, 130, 30, 10};
    Rectangle minus2 = {350, 220, 30, 10};
    Rectangle minus3 = {350, 310, 30, 10};
    Rectangle plus1a = {550, 130, 30, 10};
    Rectangle plus2a = {550, 220, 30, 10};
    Rectangle plus3a = {550, 310, 30, 10};
    Rectangle plus1b = {560, 120, 10, 30};
    Rectangle plus2b = {560, 210, 10, 30};
    Rectangle plus3b = {560, 300, 10, 30};
    
    Color transparent = {130,130,130, 180};
    Color transparent2 = {0,0,0, 80};

    // Differents rectangle seen in the window //

    DrawRectangleRec(back, transparent);
    DrawRectangleRec(setting, transparent);
    DrawRectangleRec(backDark1, transparent2);
    DrawRectangleRec(backDark2, transparent2);
    DrawRectangleRec(backDark3, transparent2);
    DrawRectangleRec(minus1, WHITE);
    DrawRectangleRec(minus2, WHITE);
    DrawRectangleRec(minus3, WHITE);
    DrawRectangleRec(plus1a, WHITE);
    DrawRectangleRec(plus1b, WHITE);
    DrawRectangleRec(plus2a, WHITE);
    DrawRectangleRec(plus2b, WHITE);
    DrawRectangleRec(plus3a, WHITE);
    DrawRectangleRec(plus3b, WHITE);

    // The texts seen in the window // 

    DrawText("SETTING", 250, 32, 35, WHITE);
    DrawText("Language", 55, 120, 35, WHITE);
    DrawText("Difficulty", 55, 210, 35, WHITE);
    DrawText("Topic", 55, 300, 35, WHITE);

    return 0;
}

int selectionSetting(List *list, int *difficulty, int *theme, int *language) {  // The function who allow us to change the difficulty.. With the double linked stack in the back src file //

    static int countLanguage = 0;
    static int countLevel = 0;
    static int countTopic = 0;

    Rectangle minus1 = {340, 130, 40, 20};
    Rectangle minus2 = {340, 220, 40, 20};
    Rectangle minus3 = {340, 310, 40, 20};

    Rectangle plus1 = {540, 120, 40, 30};
    Rectangle plus2 = {540, 210, 40, 30};
    Rectangle plus3 = {540, 300, 40, 30};

    Vector2 mousePosition;

    DrawText(displayLanguageAtIndex(list,countLanguage), 430, 130, 20, WHITE); // the text is gather by the displayLanguage function in the back //
    DrawText(displayDifficultyAtIndex(list,countLevel), 430, 220, 20, WHITE);
    DrawText(displayThemeAtIndex(list,countTopic), 429, 310, 20, WHITE);

    // to check the counter state. ( it allways goes to 0 to 2 for example HARD level = 2 if we click on right again, it become EASY = 0) //
    if ( countLanguage > 2 ) countLanguage = 0;
    if ( countTopic > 2 ) countTopic = 0;
    if ( countLevel > 2 ) countLevel = 0;
    if ( countLanguage < 0 ) countLanguage = 2;
    if ( countTopic < 0 ) countTopic = 2;
    if ( countLevel < 0 ) countLevel = 2;

    // if we click on the left triangle ( going backward ) //

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {  // if we click with the left mouse //
        mousePosition = GetMousePosition();
        if (CheckCollisionPointRec(mousePosition, minus1)) { // if the click is on the rectangle minus1 //
            countLanguage -= 1; // we decrement the count Language //
        }
        else if (CheckCollisionPointRec(mousePosition, minus2)) {
            countLevel -=1;
        }
        else if (CheckCollisionPointRec(mousePosition, minus3)) {
            countTopic -=1;
        }
        // if we click on the right triangle ( going forward ) //
        else if (CheckCollisionPointRec(mousePosition, plus1)) {
            countLanguage +=1;
        }
        else if (CheckCollisionPointRec(mousePosition, plus2)) {
            countLevel +=1;
        }
        else if (CheckCollisionPointRec(mousePosition, plus3)) {
            countTopic +=1;
        }
    }
   
    *difficulty = countLevel; // Is to return the difficulty, theme, language because in C language we cannot return mutliple variable so we use pointers //
    *theme = countTopic;
    *language = countLanguage;

    return 0;
}