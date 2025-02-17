#include <stdio.h>
#include <stdlib.h>

void saveInfo () {

    FILE *file = fopen("../../back/ressource/scoreBoard.dat", "a");
    char word;
    int pointt;

    if (file == NULL) exit (EXIT_FAILURE);

    while ( fscanf(file,"%c %d", &word,&pointt)) {
        printf("cc\n");
    }

    fclose(file);

}

int main() {

    saveInfo();
}