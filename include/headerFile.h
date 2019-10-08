#ifndef HEADER_FILE
#define HEADER_FILE

void myRmdir(char *nombre_carpeta);
void myMkdir(char *nombre_carpeta);
void checkCreate(char *buffer);
void checkMove(char *buffer);
void createDeck();
void myRemoveFile(char *fileName, char *fileSrc);
void moveFileToFolder(char *fileName, char *fileSrc, char *fileDest);
void createTest();
void test(char *dName);
int printHand(char *dName, int type);
void draw(char *sourceDir, char *destDir, int randNumber);
void drawHand(char *sourceDir, char *destDir);
void test3(char *dName);
int selection(int lower, int upper);
char** cardName(char *sourceDir, int cardNumber);
char* play(char *sourceDir, char *destDir);

#endif
//