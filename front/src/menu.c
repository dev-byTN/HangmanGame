#include "../include/front.h"

int showMainWindow() { // it shows the main window ( page 1) //

    Rectangle launching = {225, 320, 220, 50};

    DrawRectangleRec(launching, BLACK);

    DrawText("WELCOME TO", 120, 120, 32, BLACK);
    DrawText("THE", 180, 160, 32, BLACK);
    DrawText("HANGMAN GAME", 95, 200, 32, BLACK);
    DrawText("Tristan Ngounou & Guillaume Stelniceanu", 80, 270, 15, BLACK);
    DrawText("PRESS !", 265, 332, 35, WHITE);

    return 0;
}


int showChoiceGameMode() { // it shows the wondow of the selection of the game ( page 2) //

    Rectangle selection = {180, 150, 290, 50};
    Rectangle classicGame = {100, 300, 150, 50};
    Rectangle clock = {350, 300, 250, 50};

    DrawRectangleRec(selection,BLACK);
    DrawRectangleRec(classicGame, BLACK);
    DrawRectangleRec(clock, BLACK);

    DrawText("Choose a game", 200, 160, 35, WHITE);
    DrawText("Classic", 125, 310, 25, WHITE);
    DrawText("Against the clock", 370, 310, 25, WHITE);

    return 0;
}
