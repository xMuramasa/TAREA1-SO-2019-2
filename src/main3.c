// C program to demonstrate use of fork() and pipe()
// robado de geeksforgeeks, muramasa se lo robo
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include "../include/headerFile.h"

int normal(int p, char *recibo, char *entrego, int *fd01, int *fd10, int *fd02, int *fd20, int *fd03, int *fd30);
int reverse(int p, char *recibo, char *entrego, int *fd01, int *fd10, int *fd02, int *fd20, int *fd03, int *fd30);
int checkFlux(char *flux);
//cambio
int main(){
    // se usan 4 pipes
    // el primero para el proceso padre
    // los que quedan para los procesos hijos

    int fd01[2]; // msg de padre a h1
    int fd10[2]; // msg de h1 a padre
    int fd02[2]; // msg de padre a h2
    int fd20[2]; // msg de h2 a padre
    int fd03[2]; // msg de padre a h3
    int fd30[2]; // msg de h3 a padre
    int i, hijo1, hijo2, hijo3;
    int win = 1;

    int flux = 0; //flujo del juego

    char recibo[2];
    char entrego[2];

    char input_str[100]; // user input
    pid_t p;             // pid

    if (pipe(fd01) == -1 || pipe(fd10) == -1 || pipe(fd02) == -1 || pipe(fd20) == -1 || pipe(fd03) == -1 || pipe(fd30) == -1)
    {
        fprintf(stderr, "Fallaron los pipes");
        return 1;
    }

    //comment
    //mazo real
    createGame();

    int fam[4];
    fam[0] = getpid();
    hijo1 = fork();
    if (hijo1 > 0)
    {
        fam[1] = hijo1;
        hijo2 = fork();
        if (hijo2 > 0)
        {
            fam[2] = hijo2;
            hijo3 = fork();
            if (hijo3 > 0)
            {
                fam[3] = hijo3;
            }
            else
                fam[3] = getpid();
        }
        else
        {
            fam[3] = -1;
            fam[2] = getpid();
        }
    }
    else
    {
        fam[2] = fam[3] = -1;
        fam[1] = getpid();
    }

    p = getpid();

    if (p == fam[0]){ //escribir vn fd01 y leer cn fd30
        while (win){
            switch (flux){
            case 0:
                flux = normal(p, recibo, entrego, fd01, fd10, fd02, fd20, fd03, fd30);
                break;
            case 1:
                flux = reverse(p, recibo, entrego, fd01, fd10, fd02, fd20, fd03, fd30);
                break;
            default:
                break;
            }
        }
    }
    //proceso hijo 1
    if (p == fam[1]){
        while (win){
            close(fd01[1]);
            while (read(fd01[0], recibo, 20) < 0){
            }
            printf("\nPROCESO H1\n");
            strcpy(entrego, play("../outfiles/Jugador2", "../outfiles/Drop"));

            close(fd10[0]);
            write(fd10[1], entrego, 20);
        }
    }

    //proceso hijo 2
    if (p == fam[2]){
        while (win){
            close(fd02[1]);
            while (read(fd02[0], recibo, 20) < 0){
            }
            printf("\nPROCESO H2\n");
            strcpy(entrego, play("../outfiles/Jugador3", "../outfiles/Drop"));

            close(fd20[0]);
            write(fd20[1], entrego, 20);
        }
    }

    //proceso hijo 3
    if (p == fam[3]){
        while (win){
            close(fd03[1]);
            while (read(fd03[0], recibo, 30) < 0) {
            }
            printf("\nPROCESO H3\n");
            strcpy(entrego, play("../outfiles/Jugador4", "../outfiles/Drop"));

            close(fd30[0]);
            write(fd30[1], entrego, 20);
        }
    }
}

int normal(int p, char *recibo, char *entrego, int *fd01, int *fd10, int *fd02, int *fd20, int *fd03, int *fd30){

    int flux = 0;

    //interaccion hijo 1
    close(fd01[0]); // close read fd01
    if (strcmp(recibo, "j") != 0){
        flux = checkFlux(recibo);
        if (!flux){
            printf("\nPROCESO PADRE\n");
            strcpy(entrego, play("../outfiles/Jugador1", "../outfiles/Drop"));
        }else
            return flux;
    }else{
        strcpy(recibo, "a");
    }

    if (strcmp(entrego, "j") != 0){
        flux = checkFlux(entrego);
        if (!flux){
            write(fd01[1], entrego, 20);
            close(fd10[1]); //close write fd10
            while (read(fd10[0], recibo, 20) < 0){
            }
        }
        else
            return flux;
    }
    
    //interaccion hijo 2
    if (strcmp(recibo, "j") != 0){
        flux = checkFlux(recibo);
        if(!flux){
            strcpy(entrego, recibo);
            close(fd02[0]); // close read fd02
            write(fd02[1], entrego, 20);
            close(fd20[1]); //close write fd20
            while (read(fd20[0], recibo, 20) < 0){
            }
        }else return flux;
    }
    else{
        strcpy(recibo, "a");
    }

    //interaccion hijo 3
    if (strcmp(recibo, "j") != 0){
        flux = checkFlux(recibo);
        if (!flux){
            strcpy(entrego, recibo);
            close(fd03[0]); // close read fd03
            write(fd03[1], entrego, 20);
            close(fd30[1]); //close write fd30
            while (read(fd30[0], recibo, 20) < 0){
            }
        }else return flux;
    }
    else
        strcpy(recibo, "a");

    return flux;
}

int reverse(int p, char *recibo, char *entrego, int *fd01, int *fd10, int *fd02, int *fd20, int *fd03, int *fd30)
{

    int flux = 1;

    //interaccion hijo 1
    close(fd01[0]); // close read fd01
    if (strcmp(recibo, "j") != 0)
    {
        flux = checkFlux(recibo);
        if (!flux)
        {
            printf("\nPROCESO PADRE\n");
            strcpy(entrego, play("../outfiles/Jugador1", "../outfiles/Drop"));
        }
        else
            return flux;
    }
    else
    {
        strcpy(recibo, "a");
    }

    //interaccion hijo 3
    if (strcmp(recibo, "j") != 0)
    {
        flux = checkFlux(recibo);
        if (!flux)
        {
            strcpy(entrego, recibo);
            close(fd03[0]); // close read fd03
            write(fd03[1], entrego, 20);
            close(fd30[1]); //close write fd30
            while (read(fd30[0], recibo, 20) < 0)
            {
            }
        }
        else
            return flux;
    }
    else
        strcpy(recibo, "a");

    //interaccion hijo 2
    if (strcmp(recibo, "j") != 0)
    {
        flux = checkFlux(recibo);
        if (!flux)
        {
            strcpy(entrego, recibo);
            close(fd02[0]); // close read fd02
            write(fd02[1], entrego, 20);
            close(fd20[1]); //close write fd20
            while (read(fd20[0], recibo, 20) < 0)
            {
            }
        }
        else
            return flux;
    }
    else
    {
        strcpy(recibo, "a");
    }

    if (strcmp(entrego, "j") != 0)
    {
        flux = checkFlux(entrego);
        if (!flux)
        {
            write(fd01[1], entrego, 20);
            close(fd10[1]); //close write fd10
            while (read(fd10[0], recibo, 20) < 0)
            {
            }
        }
        else
            return flux;
    }

    return flux;
}

int checkFlux(char *flux){
    int lamao;
    lamao = strcmp(flux, "r") ? 0 : 1;
    return lamao;
}