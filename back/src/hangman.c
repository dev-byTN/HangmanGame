#include "../include/hangman.h"

const char *level[] = {"easy", "medium", "hard"};
const char *themes[] = {"General", "Sport", "Country"};
const char *languages[] = {"English", "French", "Spanish"};

int actualScore = 0;

void generate_filename(char *filename, int difficulty, int theme, int language){

    sprintf(filename, "../../back/ressource/%s%s%s.txt", level[difficulty], languages[language], themes[theme]);
}

List *initialisationList()
{
    List *list = malloc(sizeof(*list));
    if (list == NULL)exit(EXIT_FAILURE);
    
    list->first = NULL;
    list->last = NULL;
    list->nbValue = 0;

    return list;
}

int createDoubleLinkedStack(List *list, int nb)
{
    FILE *fileLanguage = fopen("../../back/ressource/language.txt", "r");
    FILE *fileLevel = fopen("../../back/ressource/level.txt", "r");
    FILE *fileTheme = fopen("../../back/ressource/theme.txt", "r");

    if (list == NULL) exit(EXIT_FAILURE);
    if (fileLanguage == NULL || fileLevel == NULL || fileTheme == NULL) exit(EXIT_FAILURE);

    for (int i = 0; i < nb; i++) {

        Setting *value = malloc(sizeof *value);
        if (value == NULL) exit(EXIT_FAILURE);

        fscanf(fileLanguage, "%s", value->stringLanguage);
        fscanf(fileLevel, "%s", value->stringLevel);
        fscanf(fileTheme, "%s", value->stringTheme);
        value->previous = NULL;
        if (list->first == NULL)
        {
            value->next = NULL;
            list->first = value;
            list->last = value;
        }
        else
        {
            list->first->previous = value;
            value->next = list->first;
            list->first = value;
        }
        list->nbValue++;
    }
    
    fclose(fileLanguage);
    fclose(fileLevel);
    fclose(fileTheme);

    return 0;
}

void displayDoubleLinkedStack(List *list) {

    Setting *settingValue = list->first;
    if (list == NULL) exit(EXIT_FAILURE);

    while(settingValue->next != NULL) {

        settingValue = settingValue->next;
    }

    Setting *settingValue2 = settingValue;
    while ( settingValue2!= NULL) {

        printf("%s ", settingValue2->stringLanguage);
        printf("%s ", settingValue2->stringLevel);
        printf("%s ", settingValue2->stringTheme);
        printf("\n");
        settingValue2 = settingValue2->previous;
    }
}

char *displayThemeAtIndex(List *list, int index) {

    int count = 0;

    if (list == NULL) exit(EXIT_FAILURE);

    Setting *setting = list->first;
    while( setting->next != NULL) {
        setting = setting->next;
    }

    Setting *setting2 = setting;
    while(setting2 != NULL) {

        if (count == index) {
            return setting2->stringTheme;
            break;
        }
        setting2 = setting2->previous;
        count ++;
    }
    return 0;
}

char *displayLanguageAtIndex(List *list, int index) {

    int count = 0;

    if (list == NULL) exit(EXIT_FAILURE);
    Setting *setting = list->first;

    while( setting->next != NULL) {
        setting = setting->next;
    }

    Setting *setting2 = setting;
    while(setting2 != NULL) {

        if (count == index) {
            return setting2->stringLanguage;
            break;
        }
        setting2 = setting2->previous;
        count ++;
    }
    return 0;
}

char *displayDifficultyAtIndex(List *list, int index) {

    int count = 0;

    if (list == NULL) exit(EXIT_FAILURE);
    Setting *setting = list->first;

    while( setting->next != NULL) {
        setting = setting->next;
    }

    Setting *setting2 = setting;
    while(setting2 != NULL) {

        if (count == index) {
            return setting2->stringLevel;
            break;
        }
        setting2 = setting2->previous;
        count ++;
    }
    return 0;
}

int freeList(List *list) {

    if (list == NULL) exit(EXIT_FAILURE);

    Setting *current = list->first;
    Setting *nextNode;

    while (current != NULL) {
        nextNode = current->next; 
        free(current);             
        current = nextNode;         
    }

    list->first = NULL;
    list->last = NULL;
    list->nbValue = 0; 

    return 0;
}

char* replaceWithDashes(const char* word) {
    if ( word == NULL) return 0; // debug

    int length = strlen(word); 
    char* dashes = (char*)malloc((length + 1) * sizeof(char)); // askip ca fait une liste vide de la bonne longueur
    if (dashes == NULL) return NULL;
    for (int i = 0; i < length; i++) {
        dashes[i] = '_'; // creer une liste en fonction de l'entrer si le mot fait 5 lettre : 5 tirets
    }
    dashes[length] = '\0';
    return dashes;
}

char* replaceWithDashesRight(const char* word, char *dashes, char letter) {
    if ( word == NULL) return 0; // debug
    if (dashes == NULL) return NULL;

    for ( int i = 0; i < strlen(word); i ++ ){
        if ( word[i] == letter) dashes[i] = letter;
    }
    return dashes;
}

char* chooseWordRandom(FILE *file) {
    char array[5][100];
    for (int i = 0; i<5 ; i ++){
        fscanf(file,"%99s",array[i]); 
    }
    int randomIndex = rand() % 5;
    char* words = malloc(strlen(array[randomIndex]) + 1);
    strcpy(words, array[randomIndex]); // choisit un mot aleatoirement de la liste
    return words;
}

char* showHiddenWord(char* word, char letterGuessed, char dash[]){
    int length = strlen(word); // Obtenir la longueur du mot
    for (int i = 0; i < length; i++) {
        if (letterGuessed == word[i]){
            dash[i] = letterGuessed;    // ajoute la lettre dans la liste de tiret
        }
        
    }
    return dash;
}

int addPointAfterGuessRight(int count){
    int point = 0;
    point += 50 + count; 

    return point;
}

int readLetter(char* word, char letter){
    if ( word == NULL ) return 0;
    int foundLetter = 0;

    if(isalpha(letter)){ // verifie que l'entrer c bien une lettre et pas un chiffre ou autre
        letter = toupper(letter);
         for (int i = 0; i < strlen(word); i++) {
            if (word[i] == letter) {  // Si la lettre est présente dans le mot
                foundLetter = 1;  // Marquer comme trouvée
                break;  // Sortir de la boucle dès qu'une occurrence est trouvée
            }
        }
        if (foundLetter) {
            actualScore = addPointAfterGuessRight(actualScore);
            return 0;
        }
        else return 1;
    
    } 
    else return 0;
}

int saveUserAndPoint( char* userName, int point) {
    
    FILE *file = fopen("../../back/ressource/scoreBoard.dat", "a");
    if ( file == NULL) exit(EXIT_FAILURE);

    fprintf(file, "%s ", userName);
    fprintf(file, " %d\n", point);

    fclose(file);
    return 0;
}

int getScore() { return actualScore;}