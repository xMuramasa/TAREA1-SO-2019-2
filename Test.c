#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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


/* Void check function
*   funcion : comprueba si se puede crear un archivo, en caso de ser asi lo crea y sino, lo avisa
*   prints  : si se crea la carpeta y cartas correctamente, lo avisa
*   retorna : nada
*/
void check(char* buffer){
    int cardNumber = open(buffer, O_CREAT|O_APPEND|O_RDWR);
    if(cardNumber < 0){
        printf("Error al crear archivo: %s\n", buffer);
    }
    else{
        close(cardNumber);
        printf("Se creo el archivo: %s\n", buffer);
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
    myMkdir("Deck");    // creacion directorio del mazo
    int cardNumber;

    for(i = 0;i < 4;i++){ //crea cartas de cada color

        strcpy(buffer,""); //crea cartas 0 
        sprintf(buffer, "Deck/%s_0.txt", cardNames[i]);
        check(buffer);
        
        
        strcpy(buffer,""); //crea cartas +4
        sprintf(buffer, "Deck/%s_+4_%d.txt", cardNames[4],i+1);
        check(buffer);
        

        strcpy(buffer,""); //crea cartas colores
        sprintf(buffer, "Deck/%s_CC_%d.txt", cardNames[4],i+1);
        check(buffer);
    

        for(j = 1; j < 3; j++){ //crea +2
            strcpy(buffer,"");
            sprintf(buffer, "Deck/%s_+2_%d.txt", cardNames[i],j);
            check(buffer);
        }

        for(j = 1; j < 3; j++){ //crea reverse
            strcpy(buffer,"");
            sprintf(buffer, "Deck/%s_R_%d.txt", cardNames[i],j);
            check(buffer);
        }

        for(j = 1; j < 3; j++){ //crea jump
            strcpy(buffer,"");
            sprintf(buffer, "Deck/%s_J_%d.txt", cardNames[i],j);
            check(buffer);
        }
        
        for(j = 1; j < 10; j++){ //crea cartas del 1 al 9 
            for ( k = 1; k < 3; k++){
                strcpy(buffer,"");
                sprintf(buffer, "Deck/%s_%d_%d.txt", cardNames[i], j, k);
                check(buffer);
            }
        }

        
        
    }   
}


int main(){

    createDeck();    

    return 0;
}

