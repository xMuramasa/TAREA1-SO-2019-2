#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include"../include/headerFile.h"

#define MAXSIZE 108


//Variable con los colores de cartas
char* cardNames[50] = {"rojo","azul","amarillo","verde","negro"};

/* Void myRmdir function
*   funcion : remueve una carpeta
*   prints  : si se elimina la carpeta correctamente, lo avisa
*   retorna : nada
*/
void myRmdir(char* nombre_carpeta){

    int rm = rmdir(nombre_carpeta);

    if (rm == 0){
        printf("El directorio %s fue eliminado correctamente\n", nombre_carpeta);
    }else{
        printf("No se pudo eliminar el directorio %s correctamente\n", nombre_carpeta);
    }
}


/* Void myMkdir function
*   funcion : crea una carpeta
*   prints  : si se crea la carpeta correctamente, lo avisa
*   retorna : nada
*/
void myMkdir(char* nombre_carpeta){
    int mk = mkdir(nombre_carpeta, 0700);

    if (mk == 0){
        printf("El direcotrio %s fue creado correctamente.\n", nombre_carpeta);
    }else{
        printf("No se pudo crear el direcotrio %s correctamente.\n", nombre_carpeta);
    }
}


/* Void checkCreate function
*   funcion : comprueba si se puede crear un archivo, en caso de ser asi lo crea y sino, lo avisa
*   prints  : si se crea la carpeta y cartas correctamente, lo avisa
*   retorna : nada
*/
void checkCreate(char* buffer){
    int cardNumber = open(buffer, O_CREAT|O_APPEND|O_RDWR);
    if(cardNumber < 0){
        printf("Error al crear archivo: %s\n", buffer);
    }
    else{
        close(cardNumber);
        printf("Se creo el archivo: %s\n", buffer);
    }

}


/* Void checkMove function
*   funcion : comprueba si se movio un archivo correctamente,
*             cambia de carpeta en dicho caso o avisa que no puedelo avisa
*   prints  : avisa si se mueve un archivo correctamete
*   retorna : nada
*/
void checkMove(char* buffer){
    int cardNumber = open(buffer, O_CREAT|O_APPEND|O_RDWR);
    if(cardNumber < 0){
        printf("Error al mover archivo: %s\n", buffer);
    }
    else{
        close(cardNumber);
        printf("Se movio el archivo: %s\n", buffer);
    }

}


/* Void createDeck function
*   funcion : crea el mazo de cartas
*   prints  : si se crea la carpeta y cartas correctamente, lo avisa
*   retorna : nada
*/
void createDeck(){
    int i,j,k;
    char buffer[100];
    char buffer2[100];
    char buffer3[100];
    myMkdir("../outfiles/Deck");    // creacion directorio del mazo
    int cardNumber;

    for(i = 0;i < 4;i++){ //crea cartas de cada color

        strcpy(buffer,""); //crea cartas 0
        sprintf(buffer, "../outfiles/Deck/%s_0_1.txt", cardNames[i]);
        checkCreate(buffer);


        strcpy(buffer,""); //crea cartas +4
        sprintf(buffer, "../outfiles/Deck/%s_+4_%d.txt", cardNames[4],i+1);
        checkCreate(buffer);


        strcpy(buffer,""); //crea cartas colores
        sprintf(buffer, "../outfiles/Deck/%s_CC_%d.txt", cardNames[4],i+1);
        checkCreate(buffer);


        for(j = 1; j < 3; j++){ //crea +2
            strcpy(buffer,"");
            sprintf(buffer, "../outfiles/Deck/%s_+2_%d.txt", cardNames[i],j);
            checkCreate(buffer);
        }

        for(j = 1; j < 3; j++){ //crea reverse
            strcpy(buffer,"");
            sprintf(buffer, "../outfiles/Deck/%s_R_%d.txt", cardNames[i],j);
            checkCreate(buffer);
        }

        for(j = 1; j < 3; j++){ //crea jump
            strcpy(buffer,"");
            sprintf(buffer, "../outfiles/Deck/%s_J_%d.txt", cardNames[i],j);
            checkCreate(buffer);
        }

        for(j = 1; j < 10; j++){ //crea cartas del 1 al 9
            for ( k = 1; k < 3; k++){
                strcpy(buffer,"");
                sprintf(buffer, "../outfiles/Deck/%s_%d_%d.txt", cardNames[i], j, k);
                checkCreate(buffer);
            }
        }
    }
}


/* Void myRemoveFile function
*   funcion : elimina un archivo con un directorio origen (src)
*   prints  : avisa si puede eliminar correctamente un archivo o no
*   retorna : nada
*/
void myRemoveFile(char* fileName, char* fileSrc){
    int status;
    chdir(fileSrc);
    status = remove(fileName);
    if (status == 0)
        printf("El archivo %s ha sido eliminado correctamente.\n", fileName);
    else{
        printf("No se pudo eliminar el archivo %s correctamente.\n", fileName);
    }
}


/* Void moveFileToFolder function
*   funcion : mueve un archivo de una carpeta origen a un destino
*   retorna : nada
*/
void moveFileToFolder(char* fileName, char* fileSrc, char* fileDest){
    char buffer[100] = "";
    int copy;
    myRemoveFile(fileName, fileSrc);
    chdir("..");
    sprintf(buffer, "%s/%s", fileDest, fileName);
    checkMove(buffer);
}


//igual que create deck, pero crea un directorio de prueba
void createTest(){
    int i;
    char buffer[100];
    myMkdir("../outfiles/Test");    // creacion directorio del mazo
    int cardNumber;

    for(i = 0;i < 4;i++){ //crea cartas de cada color

        strcpy(buffer,""); //crea cartas 0
        sprintf(buffer, "../outfiles/Test/%s_0.txt", cardNames[i]);
        checkCreate(buffer);

        strcpy(buffer,""); //crea cartas +4
        sprintf(buffer, "../outfiles/Test/%s_+4_%d.txt", cardNames[4],i+1);
        checkCreate(buffer);
    }
}


/* Void listDirectory function
*   funcion : muestra el listado de files de un directorio
*   prints  : si se crea la carpeta y cartas correctamente, lo avisa
*   retorna : nada
*/
void listDirectory(char* dName){
    DIR *d;
    struct dirent *dir;
    d = opendir(dName);
    if (d){
        while ((dir = readdir(d)) != NULL){
            if(dir->d_name != "." && dir->d_name != "..")
                printf("%s\n", dir->d_name);
            
        }
        closedir(d);
    }
}


/* Void listDirectory function
*   funcion : muestra el listado de files de un directorio
*   prints  : printea un box para la eleccion de la mano del jugador
*/
void printHand(char *dName){
    DIR *d;
    struct dirent *dir;
    d = opendir(dName);
    char (*buffer)[50] = malloc(2*sizeof(char*));
    int index = 0;

    printf("************ MI MANO ************\n");
    if (d){
        while ((dir = readdir(d)) != NULL){
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                    sscanf(dir->d_name, "%[^_]_%[^_]_%[^_]", buffer[0], buffer[1], buffer[2]);
                    printf("*\t[%d] %s %s\t\t*\n", index, buffer[0], buffer[1]);
                    index++; 
            }
        }
        closedir(d);
    }
    printf("*********************************\n");
    free(buffer);
    }

/* Void draw function
*   funcion : saca un archivo en la posicion randNumber y lo coloca en la carpeta especificada
*   prints  : avisa si logra mover la carta de posicion
*   retorna : nada
*/
void draw(char *sourceDir, char *destDir, int randNumber){
    int i = 0;
    DIR *d; 
    char buffer[50]; 
    struct dirent *dir;
    d = opendir(sourceDir);
    if (d){
        while ((dir = readdir(d)) != NULL && i < randNumber)
        {
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                strcpy(buffer,"");
                strcpy(buffer,dir->d_name);
                //printf("%s\n",buffer);
                i++;
            }
        }
        closedir(d);
    }
    moveFileToFolder(buffer, sourceDir, destDir);
}


/* Void drawHand function
*   funcion : saca 7 cartas al azar y los mueve de carpeta
*   prints  : avisa si logra mover las cartas de posicion
*   retorna : nada
*/
void drawHand(char *sourceDir, char *destDir){
    int randomNumber = 0;
    int moved = 0;
    //random() % j;
    while(moved < 7){

        randomNumber = random() % (108-2);
        if(randomNumber < 108){
            draw(sourceDir, destDir, randomNumber);
            moved++;
        }
    }
}


/* Void cardName function
*   funcion : asign los datos de una carta al arreglo values
*   prints  : nada
*   retorna : nada
*/
void cardName(char *sourceDir, char* values, int cardNumber){
    int i = 0;
    DIR *d;
    char buffer[50];
    struct dirent *dir;
    d = opendir(sourceDir);
    if (d){
        while ((dir = readdir(d)) != NULL && i < cardNumber){
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                strcpy(buffer, "");
                strcpy(buffer, dir->d_name);
                i++;
            }
        }
        closedir(d);
    }
    sscanf(buffer, "%s_%s.txt", &values[0], &values[1]);
}

/* Void select function
*   funcion : hace que el usuario ingrese un input correctamente
*   retorna : nada
*/
int selection(int lower, int upper){
    int selection;
    printf("Ingrese seleccion:\t");
    char s[128];

    while (1){
        scanf("%s", s);
        if (sscanf(s, "%d", &selection) != 1){
            printf("Seleccion invalida.\nPor favor ingrese un numero:\t");
        }
        else if(selection < lower || selection > upper){
            printf("Seleccion invalida.\nPor favor ingrese un numero dentro del rango:\t");
        }else{
            break;
        }
    }
    return selection;
}

/* Void play function
*   funcion : juega una carta en Drop
*   prints  : muestra la carta en juego.
*   retorna : nada
*
void play(char *sourceDir, char *destDir){

    int flag = 1;
    char (*carta)[50] = (char*)malloc(3*sizeof(char));

    printf("CARTA EN JUEGO:\t"); //muestra carta en juego
    listDiestra mano del jugador
    printHand(destDir);
    int input = selection(1,8);

    while(flag){
        scanf("%d",input);
        cardName(sourceDir,carta,input);
        

    }

    free(carta);
}
*/
//Estas funciones son un meme
void test3(char* dName){
    DIR *d = opendir(dName);
    char buffer[50];
    struct dirent *dir;
    int j,k;
    int randPrev;
    int i = 0;

    int rNumber;
    int flag = 0;

    if(d){
        while ((dir = readdir(d)) != NULL){
            for (i = 0; i < rNumber; i++){
                dir = readdir(d);
                strcpy(buffer,"");
                strcpy(buffer,dir->d_name);
            }
            if(strcmp(buffer, ".") != 0 && strcmp(buffer, "..") != 0){
                moveFileToFolder(buffer, "../outfiles/Test", "../outfiles/testHand");
                j = 8-k;
                while (j != 0 && flag != 0){
                    randPrev = rNumber;
                    rNumber = random() % j;
                    if(rNumber > randPrev){
                        flag = 1;
                        break;
                    }
                }
                flag = 0;
                d = opendir(dName);
                k++;
            }
        }
        closedir(d);
    }
}

void test(char *dName){
    srand(time(NULL));
    int r, k;
    int i = 0; //cartas que se sacan
    int c = 0;

    DIR *d;
    char buffer[50];
    struct dirent *dir;
    d = opendir(dName);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        
        {
            strcpy(buffer, "");
            strcpy(buffer, dir->d_name);

            r = rand() % (8 - c);

            if (i == r)
            {
                printf("Se mueve %s\n", buffer);
                i = 0;
                c++;
            }

            for (k = 0; k < r; k++)
            {
                dir = readdir(d);
                strcpy(buffer, "");
                strcpy(buffer, dir->d_name);
                if (strcmp(buffer, ".") == 0)
                {
                    k--;
                }
                else if (strcmp(buffer, ".") == 0)
                {
                    k--;
                }
            }
            printf("%s\n", buffer);
            i++;
        }
        closedir(d);
    }
}
