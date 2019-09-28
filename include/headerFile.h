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
void listDirectory(char *dName);
void test(char *dName);
void Draw(char *sourceDir, char *destDir, int randNumber);
void test3(char *dName);

#endif