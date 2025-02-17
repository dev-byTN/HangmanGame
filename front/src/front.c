#include "../include/front.h"
#include "menu.c"
#include "settings.c"
#include "game.c"


int main() {

    InitWindow (670, 400, "Hangman Project 3A"); // Open raylib window //
 
    InitAudioDevice(); // To initialize audio device //
    Music music = LoadMusicStream("../ressource/clockSound.mp3");
    PlayMusicStream(music);

    Texture2D hangmanImages[TOTAL_IMAGES];
    Texture2D textureB = LoadTexture("../ressource/bg.png"); // To load the main background image //
    Texture2D textureH = LoadTexture("../ressource/homee.png"); // To load the home IMAGE //
    Texture textureB2 = LoadTexture("../ressource/game.png");// To load the game background //
    Texture2D textureS = LoadTexture("../ressource/settings.png");// To load the setting IMAGE //
    Texture2D textureN = LoadTexture("../ressource/next.png"); // To load the next button in game window //
    hangmanImages[0] = LoadTexture("../ressource/hangman1.png");
    hangmanImages[1] = LoadTexture("../ressource/hangman2.png");
    hangmanImages[2] = LoadTexture("../ressource/hangman3.png");
    hangmanImages[3] = LoadTexture("../ressource/hangman4.png");
    hangmanImages[4] = LoadTexture("../ressource/hangman5.png");
    hangmanImages[5] = LoadTexture("../ressource/hangman6.png");
    hangmanImages[6] = LoadTexture("../ressource/hangman7.png");

    textureB.height = 400;
    textureB.width = 670; 
    textureB2.height = 400;
    textureB2.width = 670;
    textureS.height = 60;
    textureS.width = 60;
    textureH.height = 40;
    textureH.width = 40;
    textureN.width = 40;
    textureN.height = 40;

    Rectangle settingRect = {580, 20, 60, 60}; // To initialize the differents rectangle //
    Rectangle launchingRect = {225, 320, 220, 50};
    Rectangle homeButton = {580, 20, 60, 60};
    Rectangle classicGame = {100, 300, 150, 50};
    Rectangle clock = {350, 300, 250, 50};
    Rectangle nextButton = {50, 30, 60, 60};
    Rectangle textboxInput = {550, 350, 100, 40};
    Rectangle inputName = {200, 200, 250, 60};
    Rectangle transparent = {0,0, 670, 400};

    Color TRANSPARENT = {0,0,0,150};

    GameState currentState = STATE_MENU; // To initialize the game state //
    Vector2 mousePosition;

    bool mouseOnText = false;

    List *myList = initialisationList(); // Very important the call of the linked stack function this one is the initilisation of the List //
    createDoubleLinkedStack(myList, NB_GAME_MODE); // Here the creation of the linked stack //

    int difficulty = 0;
    int theme = 0;
    int language = 0;
    int countHangman = 0;
    int countError = 0;
    int framesCounter = 0;
    int tryRemaining = 6;
    int checkMessage = 0;
    int seconds = 59;
    int minutes = 1;
    
    char filename[100];
    char *randomWord;
    char *dashes;
    char *dashWord;
    char *userName;
    char letterGuess;

    time_t timer = time(NULL);
    time_t countDown;

    while (!WindowShouldClose()){ // The main loop who stop when the user close the window //

        BeginDrawing();
            
            GameState nextState = NONE; 
            if (currentState == STATE_MENU) { // checking the state . Here if the state == main page 

                DrawTexture(textureB, 0,0,WHITE); //  Drawing the background
                DrawTexture(textureS, 580, 20, BLACK); // Drawing the setting image //
                showMainWindow(); // Call of the main window function //

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // If we click //
                    mousePosition = GetMousePosition();
                    if (CheckCollisionPointRec(mousePosition, settingRect)) { // Click on the setting image //
                        currentState = STATE_SETTING; // current state = setting window. It means that we changing window //
                    }
                    else if (CheckCollisionPointRec(mousePosition, launchingRect)) { // If we click on the rectangle to start to play we changin window as well //
                        currentState = STATE_CHOICE_MODE;
                    }
                }
            }

            else if (currentState == STATE_SETTING) { // Event on the setting window //
                DrawTexture(textureB, 0, 0, WHITE);
                DrawTexture(textureH, 580, 20, BLACK);
                showSettingWindow();
                selectionSetting(myList, &difficulty, &theme, &language); // call of the linked stack function //

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    mousePosition = GetMousePosition();
                    if (CheckCollisionPointRec(mousePosition, homeButton)) {
                        currentState = STATE_MENU;
                    }
                }
            }

            else if ( currentState == STATE_CHOICE_MODE) { // Event on the game mode page //
                DrawTexture(textureB, 0, 0, WHITE);
                DrawTexture(textureS, 580, 20, BLACK);
                showChoiceGameMode();

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // If we click on the rectangle "classic mode " //
                    mousePosition = GetMousePosition();
                    if (CheckCollisionPointRec(mousePosition, classicGame)) {
                        currentState = STATE_NAME_SELECTION_CLASSIC;
                    }
                    else if (CheckCollisionPointRec(mousePosition, settingRect)) {
                        currentState = STATE_SETTING;
                    }
                    else if (CheckCollisionPointRec(mousePosition, clock)) {
                        currentState = STATE_NAME_SELECTION_CLOCK;
                    }
                }
            }

            else if ( currentState == STATE_NAME_SELECTION_CLASSIC) {
                DrawTexture(textureB2, 0, 0, WHITE);
                DrawRectangleRec(transparent, TRANSPARENT);
                userName = checkInputNameClassic(mouseOnText, inputName, &currentState);
                drawTextBoxName(mouseOnText, inputName, framesCounter);
            }
            else if ( currentState == STATE_NAME_SELECTION_CLOCK) {
                DrawTexture(textureB2, 0, 0, WHITE);
                DrawRectangleRec(transparent, TRANSPARENT);
                userName = checkInputNameClock(mouseOnText, inputName, &currentState);
                drawTextBoxName(mouseOnText, inputName, framesCounter);
            }

            else if ( currentState == STATE_CLASSIC) { // In the classic window //
                DrawTexture(textureB2, 0, 0, WHITE);
                DrawTexture(textureH, 580, 20, BLACK);
                DrawTexture(textureN, 50, 30, BLACK);
                drawTextBox(mouseOnText, textboxInput, &framesCounter);

                if (tryRemaining == 6) {
                    generate_filename(filename, difficulty, theme, language);
                    FILE *file = fopen(filename, "r");
                    if (file == NULL) perror("Error opening file");
                    srand(time(NULL));
                    randomWord = chooseWordRandom(file);
                    dashes = replaceWithDashes(randomWord);
                    fclose(file);
                }

                countError = checkInput(mouseOnText, textboxInput, &framesCounter, randomWord, &letterGuess); // countError = 1 : the letter enter is not in the word //
                showLetter(); // display the letters enter in a backboard //
                displayRemainingAttempts(tryRemaining);

                if (countError == 1) { // If the letter incorrect //
                    dashWord = showHiddenWord(randomWord, letterGuess, dashes);
                    countHangman = (countHangman+ 1) % TOTAL_IMAGES;
                    tryRemaining --;
                    checkMessage = 0;
                }
                else {
                    dashWord = showHiddenWord(randomWord, letterGuess, dashes);
                    if ( difficulty == 0 ) showDashesEasyMode(dashWord);
                    else if ( difficulty == 1 ) showDashesMediumMode(dashWord);
                    else showDashesHardMode(dashWord);
                }
                
                hangmanImages[countHangman].height = 350;
                hangmanImages[countHangman].width = 170;
                DrawTexture(hangmanImages[countHangman], 0,50, WHITE);

                if (strcmp(randomWord, dashes) == 0) {
                    tryRemaining = 6;
                    countHangman = 0;
                    checkMessage = 1;
                    resetAll();
                }
                if (tryRemaining == 0) {
                    tryRemaining = 6;
                    countHangman = 0;
                    checkMessage = -1;
                    resetAll();
                }
                if (checkMessage == 1) displayWinMessage();
                else if (checkMessage == -1) displayLooseMessage();
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    mousePosition = GetMousePosition();
                    if (CheckCollisionPointRec(mousePosition, homeButton)) {
                        currentState = STATE_MENU;
                    }
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    mousePosition = GetMousePosition();
                    if (CheckCollisionPointRec(mousePosition, nextButton)) {
                        tryRemaining = 6;
                        countHangman = 0;
                        resetAll();
                    }
                }
            }

            else if ( currentState == STATE_CLOCK) { // in the against the clock window //

                countDown = time(NULL); 
                UpdateMusicStream(music);
                DrawTexture(textureB2, 0, 0, WHITE);
                DrawTexture(textureH, 580, 20, BLACK);
                drawTextBox(mouseOnText, textboxInput, &framesCounter);

                if (countDown - timer >= 1) {
                    seconds--;
                    timer = countDown; // Reset startTime to the current time //

                    if (seconds < 0) {
                        seconds = 59; // Reset seconds //
                        minutes--; // Decrement minutes //
                    }
                }
                if (minutes == 0 && seconds == 0) break;
                char timerText[20];
                sprintf(timerText, "%02d:%02d", minutes, seconds);
                DrawText(timerText, 300 - MeasureText(timerText, 40) / 2, 250, 40, BLACK);
                
                if (tryRemaining == 6) {
                    generate_filename(filename, difficulty, theme, language);
                    FILE *file = fopen(filename, "r");
                    if (file == NULL) perror("Error opening file");
                    srand(time(NULL));
                    randomWord = chooseWordRandom(file);
                    dashes = replaceWithDashes(randomWord);
                    fclose(file);
                }

                countError = checkInput(mouseOnText, textboxInput, &framesCounter, randomWord, &letterGuess); 
                showLetter(); 
                displayRemainingAttempts(tryRemaining);

                if (countError == 1) {
                    dashWord = showHiddenWord(randomWord, letterGuess, dashes);
                    countHangman = (countHangman+ 1) % TOTAL_IMAGES;
                    tryRemaining --;
                    checkMessage = 0;
                }
                else {
                    dashWord = showHiddenWord(randomWord, letterGuess, dashes);
                    if ( difficulty == 0 ) showDashesEasyMode(dashWord);
                    else if ( difficulty == 1 ) showDashesMediumMode(dashWord);
                    else showDashesHardMode(dashWord);
                }
                
                hangmanImages[countHangman].height = 350;
                hangmanImages[countHangman].width = 170;
                DrawTexture(hangmanImages[countHangman], 0,50, WHITE);

                if (strcmp(randomWord, dashes) == 0) {
                    tryRemaining = 6;
                    countHangman = 0;
                    checkMessage = 1;
                    resetAll();
                }
                if (tryRemaining == 0) {
                    tryRemaining = 6;
                    countHangman = 0;
                    checkMessage = -1;
                    resetAll();
                }
                if (checkMessage == 1) displayWinMessage();
                else if (checkMessage == -1) displayLooseMessage();

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    mousePosition = GetMousePosition();
                    if (CheckCollisionPointRec(mousePosition, homeButton)) {
                        currentState = STATE_MENU;
                    }
                } 
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    mousePosition = GetMousePosition();
                    if (CheckCollisionPointRec(mousePosition, nextButton)) {
                        tryRemaining = 6;
                        countHangman = 0;
                        resetAll();
                    }
                }
            }
            if (nextState != NONE) { 
                currentState = nextState;
            }
            
        EndDrawing();
    }

    // Unloading of every image, texture, music and the window //
    freeList(myList);
    free(randomWord);
    free(dashWord);
    saveUserAndPoint(userName, getScore());
    UnloadMusicStream(music);
    UnloadTexture(textureB);
    UnloadTexture(textureS);
    UnloadTexture(textureH);
    UnloadTexture(textureB2);
    UnloadTexture(textureN);
    for (int i = 0; i < TOTAL_IMAGES; i++) {
        UnloadTexture(hangmanImages[i]);
    }
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}