#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pixel{
  int red, green, blue;
};
struct Picture{
  int breite, hoehe;
  int max_helligkeit;
  struct Pixel *leinwand;
};
void read_pic(struct Picture *, char *path);
void write_pic(struct Picture, char *path);
char *build_str(struct Pixel *);
int ilen(int);

int main(int argc, char *argv[]){
  if (argc <= 2){
    printf("Nicht genug Argumente.\n");
    return 1;
  }

  struct Picture *ptr = malloc(sizeof(struct Picture));
  if (ptr == NULL){
    perror("malloc");
    return 1;
  }
  read_pic(ptr, argv[1]);
  write_pic(*ptr, argv[2]);

  return 0;
}

void read_pic(struct Picture *picture, char *path){
  struct Pixel *tmp = picture->leinwand;
  FILE *file = fopen(path, "r");
  char c = fgetc(file);
  picture->breite = 0;
  while (c != ' '){
    picture->breite *= 10;
    picture->breite += (int)c;
    c = fgetc(file);
  }
  c = fgetc(file);
  picture->hoehe = 0;
  while (c != '\n'){
    picture->hoehe *= 10;
    picture->hoehe += (int)c;
    c = fgetc(file);
  }
  c = fgetc(file);
  picture->max_helligkeit = 0;
  while (c != '\n'){
    picture->max_helligkeit *= 10;
    picture->max_helligkeit += (int)c;
    c = fgetc(file);
  }
  picture->leinwand = malloc(picture->hoehe * picture->breite * sizeof(struct Pixel));

  for (int i = 0; i < picture->hoehe; i++){//Zeilen
    for (int j = 0; j < picture->breite; j++){//Reihen
      //rot:
      picture->leinwand->red = 0;
      for (int k = 0; k < 3; k++){
        c = fgetc(file);
        if (c != ' '){
            picture->leinwand->red *= 10;
            picture->leinwand->red += (int)c;
        }
      }
      fgetc(file);//für ' '
      //grün:
      picture->leinwand->green = 0;
      for (int k = 0; k < 3; k++){
        c = fgetc(file);
        if (c != ' '){
            picture->leinwand->green *= 10;
            picture->leinwand->green += (int)c;
        }
      }
      fgetc(file);//für ' '
      //blau:
      picture->leinwand->blue = 0;
      for (int k = 0; k < 3; k++){
        c = fgetc(file);
        if (c != ' '){
            picture->leinwand->blue *= 10;
            picture->leinwand->blue += (int)c;
        }
      }
      c = fgetc(file);
      for (int k = 0; k < 3 && c==' '; k++){
        c = fgetc(file);
      }
      (picture->leinwand)++;
    }
  }
  fclose(file);
  picture->leinwand = tmp;
}

void write_pic(struct Picture picture, char *path){
  struct Pixel *tmp = picture.leinwand;
  FILE *file = fopen(path, "w");
  int eUzZeile = ilen(picture.hoehe)+1+ilen(picture.breite)+1 + ilen(picture.max_helligkeit)+1;//Anzahl der chars in der ersten und zweiten Zeile
  char *ret = malloc(eUzZeile + picture.hoehe*(11+(picture.breite-1)*14+1) + 1);

  //erste, zweite Zeile:
  sprintf(ret, "%d %d\n%d", picture.breite, picture.hoehe, picture.max_helligkeit);
  ret += eUzZeile-1;
  //Matrix schreiben
  for (int i = 0; i < picture.hoehe; i++){//Zeilen
    strcat(ret, "\n");
    ret++;
    for (int j = 0; j < picture.breite; j++){//Reihen
      if (j != 0){
        strcat(ret, "   ");
        ret += 3;
      }
      strcat(ret, build_str(picture.leinwand));
      picture.leinwand++;
      ret += 11;
    }
    strcat(ret, "\n");
    picture.leinwand++;
    ret++;
  }
  picture.leinwand = tmp;
  fclose(file);
}

int ilen(int num){
  int ret = 0;
  for (; num >= 10; ret++){
    num /= 10;
  }
  return ret;
}

char *build_str(struct Pixel *pxl){
  char *ret = malloc(12);
  strcpy(ret, "           \0");
  ret += 4-ilen(pxl->red);
  sprintf(ret, "%d", pxl->red);
  ret += ilen(pxl->red);
  ret += 4-ilen(pxl->green);
  sprintf(ret, "%d", pxl->green);
  ret += ilen(pxl->green);
  ret += 4-ilen(pxl->blue);
  sprintf(ret, "%d", pxl->blue);
  ret += ilen(pxl->blue);
  return ret;
}

/*Bsp.:
# Ein Farbbild der Größe 3 × 2 Pixel, maximaler Helligkeit 255.
# Darauf folgen die RGB-Tripel.
3 2
255
255   0   0     0 255   0     0   0 255
255 255   0   255 255 255     0   0   0*/
