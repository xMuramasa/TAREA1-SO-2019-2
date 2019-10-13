#ifndef HEADER_FILE
#define HEADER_FILE
void createGame();

void myRmdir(char *nombre_carpeta);
void myMkdir(char *nombre_carpeta);

void myRemoveFile(char *fileName, char *fileSrc);

void checkCreate(char *buffer);
void createDeck();

void createTest();

void moveFileToFolder(char *fileName, char *fileSrc, char *fileDest);
void checkMove(char *buffer);

int printHand(char *dName, int type);

void draw(char *sourceDir, char *destDir, int randNumber);
void drawX(char *sourceDir, char *destDir, int x);
void drawHand(char *sourceDir, char *destDir);

int selection(int lower, int upper);

char** cardName(char *sourceDir, int cardNumber);
int cardInHand(char *sourceDir);

char *play(char *sourceDir, char *destDir);

#endif
    //