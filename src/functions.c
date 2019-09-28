#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
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
        sprintf(buffer, "../outfiles/Deck/%s_0.txt", cardNames[i]);
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
    chdir("..");
}


/* Void moveFileToFolder function
*   funcion : mueve un archivo de una carpeta origen a un destino
*   retorna : nada
*/
void moveFileToFolder(char* fileName, char* fileSrc, char* fileDest){
    char buffer[100] = "";
    int copy;
    myRemoveFile(fileName, fileSrc);
    sprintf(buffer, "../outfiles/%s/%s",fileDest,fileName);
    checkMove(buffer);
}

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
            printf("%s\n", dir->d_name);
            
        }
        closedir(d);
    }
}

void test(char* dName){
    srand(time(NULL));
    int r,k;
    int i = 0; //cartas que se sacan
    int c = 0;

    DIR *d;
    char buffer[50]; 
    struct dirent *dir;
    d = opendir(dName);
    if (d){
        while ((dir = readdir(d)) != NULL){
            strcpy(buffer,"");
            strcpy(buffer,dir->d_name);

            r = rand() % (8 - c);

            if(i == r){
                printf("Se mueve %s\n",buffer);
                i = 0;
                c++;
            }
            
            for (k = 0; k < r; k ++){
               dir = readdir(d);
               strcpy(buffer,"");
               strcpy(buffer,dir->d_name);
               if (strcmp(buffer, ".") == 0){
                   k--;
               }
               else if (strcmp(buffer, ".") == 0){
                   k--;
               }
            }
            printf("%s\n",buffer);
            i++;
        }
        closedir(d);
    }
}


void Draw(char* dName, int r){
    int i = 0;
    DIR *d; 
    char buffer[50]; 
    struct dirent *dir;
    d = opendir(dName);
    if (d){
        while ((dir = readdir(d)) != NULL && i < r){
            if(strcmp(buffer, ".") != 0 && strcmp(buffer, "..") != 0){
                strcpy(buffer,"");
                strcpy(buffer,dir->d_name);
                i++;

            }
        }
        closedir(d);
    }
    moveFileToFolder(buffer,"Test","testHand");
}

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
                moveFileToFolder(buffer,"Test","testHand");
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

