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
    sprintf(buffer, "%s/%s", fileDest, fileName);
    checkMove(buffer);
}


/* Void printHand function
*   funcion : muestra el listado de files de un directorio
*   prints  : si se crea la carpeta y cartas correctamente, lo avisa
*   retorna : nada
*/
void printHand(char *dName, int type){
    int index = 0;
    int i;
    
    DIR *d;
    struct dirent *dir;
    d = opendir(dName);
    
    char (**buffer) = malloc(3*sizeof(char*));
    for (i = 0; i < 3; i++){
        buffer[i] = malloc(50 * sizeof(char *));
    }

    if (type) printf("\n************* MI MANO *************\n");
    if (d){
        while ((dir = readdir(d)) != NULL){
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                sscanf(dir->d_name, "%[^_]_%[^_]_%[^.txt]", buffer[0], buffer[1], buffer[2]);
                printf("*\t[%d] %s %s %s\n", index+1, buffer[0], buffer[1], buffer[2]);
                index++; 
            }
        }
        if (type) printf("***********************************\n");
        closedir(d);
    }

    for (int i = 0; i < 3; i++){
        free(buffer[i]);
    }
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
char** cardName(char *sourceDir, int cardNumber){
    DIR *d;
    struct dirent *dir;
	d = opendir(sourceDir);
    int i ;
    int index = 0;
    puts("malloc");
    char(**values) = malloc(3 * sizeof(char *));
    for (i = 0; i < 3; i++){
        puts("formalloc");
        values[i] = malloc(50 * sizeof(char*));
    }
    puts("aftermalloc");

    if (d){
        while ((dir = readdir(d)) != NULL && index <= cardNumber){
            puts("while");
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                sscanf(dir->d_name, "%[^_]_%[^_]_%[^.txt]", values[0], values[1], values[2]);
                puts("scanf");
                index++;
            }
        }
        closedir(d);
    }
    puts("outwhile");
    return values;
}


/* Void selection function
*   funcion : hace que el usuario ingrese un input correctamente
*   retorna : la seleccion
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



int cardInHand(char* sourceDir){
    DIR *d;
    struct dirent *dir;
    d = opendir(sourceDir);
    int hand = 0;
    if (d){
        while ((dir = readdir(d)) != NULL){
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
				hand++; 
            }
        }
        closedir(d);
    }
	return hand;  
}

/* Void play function
*   funcion : juega una carta en Drop
*   prints  : muestra la carta en juego.
*   retorna : nada
*/
void play(char *sourceDir, char *destDir){
	int input,handSize;
    int flag = 1;
    char (**cartaIn);
	char (**cartaOut);
    char buffer1[50];
    char buffer2[50];


    while(flag){
        
        printHand("../outfiles/Jugador1", 1);
        printf("\nDROP ******************** DROP\n");
        printHand("../outfiles/Drop", 0);
        printf("DROP ******************** DROP\n\n");
        //input = selection(0,8);  // selecion de carta del jugador
        
        strcpy(buffer1, "");
        strcpy(buffer2, "");
        
        handSize = cardInHand(sourceDir);
        input = selection(0,handSize);
        printf("xd\n");
        cartaIn = cardName(sourceDir,input);
        printf("xdaa\n");
        cartaOut = cardName(destDir, input);
        printf("xds\n");

        // carta[0] = color, carta[1]=tipo, carta[3]=copia
        //sprintf(var1+var2,format, var1, var1);
		
        sprintf(buffer1, "%s_%s_%s.txt",cartaIn[0], cartaIn[1], cartaIn[2]);
		printf("%s\n",buffer1);
		sprintf(buffer2, "%s_%s_%s.txt",cartaOut[0], cartaOut[1], cartaOut[2]);
		printf("%s\n",buffer2);
        
        printf("REMOVE %s %s \n",buffer1,destDir);
        printf("MOVE %s %s %s \n",buffer2,sourceDir,destDir);

        myRemoveFile(buffer2, destDir);
        moveFileToFolder(buffer1, sourceDir, destDir);

        /* 
        if (strcmp(cartaIn[0], cartaOut[0]) == 0 || strcmp(cartaIn[1], cartaOut[1]) == 0){
            myRemoveFile(buffer2,destDir);
			moveFileToFolder(buffer1,sourceDir,destDir);
        }*/
        for (int i = 0; i < 3; i++){
            free(cartaIn[i]);
            free(cartaOut[i]);
        }
        free(cartaIn);
        free(cartaOut);
    }

}