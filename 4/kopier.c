#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc <= 2){
        printf("Nicht genug Argumente.\n");
        return 1;
    }else if(strcmp(argv[1], argv[2]) == 0){
        printf("Die Quell- und Zieladressen sind identisch.");
        return 0;
    }

    FILE *inp, *outp;
    inp = fopen(argv[1], "r");
    outp = fopen(argv[2], "w");
    if (inp==NULL || outp==NULL){
        printf("Fehler bei den Dateinamen.\n");
        return 1;
    }
    
    char c[BUFSIZ];
    size_t i = fread(c, sizeof c[0], sizeof c, inp);
    while (i != 0){
        fwrite(c, sizeof c[1], i, outp);
        i = fread(c, sizeof c[0], sizeof c, inp);
    }

    fclose(inp);
    fclose(outp);

    printf("Datei kopiert.\n");
    return 0;
}