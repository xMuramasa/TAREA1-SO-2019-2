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

void createDeck(){
    int i,j,k;
    char buffer[100];
    myMkdir("Deck");
    int filedesc; //= open("Deck/testfile.txt", O_CREAT|O_APPEND|O_RDWR);

    for(i = 0;i < 4;i++){ //crea cartas 0 de cada color
        
        strcpy(buffer,"");
        sprintf(buffer, "Deck/%s_0.txt", cardNames[i]);
        
        filedesc = open(buffer, O_CREAT|O_APPEND|O_RDWR);
        if(filedesc < 0){
            printf("Error al crear archivo: %s\n", buffer);
        }
        else{
            close(filedesc);
            printf("Se creo el archivo: %s\n", buffer);
        }
        
        for(j = 1; j < 10; j++){ //crea cartas del 1 al 9 de cada color
            for ( k = 1; k < 3; k++){
                strcpy(buffer,"");
                sprintf(buffer, "Deck/%s_%d_%d.txt", cardNames[i], j, k);
                filedesc = open(buffer, O_CREAT|O_APPEND|O_RDWR);
                if(filedesc < 0){
                    printf("Error al crear archivo: %s\n", buffer);
                }
                else{
                    close(filedesc);
                    printf("Se creo el archivo: %s\n", buffer);
                }
            }
        }
}
}


int main(){

    createDeck();    

    return 0;
}

