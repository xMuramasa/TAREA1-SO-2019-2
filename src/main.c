// C program to demonstrate use of fork() and pipe()
// robado de geeksforgeeks, el martin fue
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include "../include/headerFile.h"
//cambio
int main()
{
    // se usan 4 pipes
    // el primero para el proceso padre
    // los que quedan para los procesos hijos

    int fd01[2]; // msg de padre a h1
    int fd10[2]; // msg de h1 a padre
    int fd02[2]; // msg de padre a h2
    int fd20[2]; // msg de h2 a padre
    int fd03[2]; // msg de padre a h3
    int fd30[2]; // msg de h3 a padre
    int i, hijo1, hijo2, hijo3; // contrador (i) y variables de pid
    int win = 1;        //condicion de termino

    char entrego[2];    // string de mensajes entregdos
    char recibo[2];     // string de mensajes recibidos

    pid_t p;             // pid

    // comprobacion de creacion de pipes
    if (pipe(fd01) == -1 || pipe(fd10) == -1 || pipe(fd02) == -1 || pipe(fd20) == -1 || pipe(fd03) == -1 || pipe(fd30) == -1)
    {
        fprintf(stderr, "Fallaron los pipes");
        return 1;
    }

    //creación del juego
    createGame();
    
    // creacion de procesos hijos 
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

    // get pid por cada proceso
    p = getpid();

    if (p == fam[0])
    {
        while (win)
        {
            puts("\n\n\n");
            printf("\n\tTURNO DEL JUGADOR 1\n");

            //+++++++++++++++++++++++++++++++++++++++++++++turno j1+++++++++++++++++++++++++++++++++++++++++++++
            close(fd01[0]); // close read fd01
            //+2
            if (strcmp(recibo, "d") == 0)
            {
                drawX("../outfiles/Deck", "../outfiles/Jugador1", 2);
                strcpy(entrego, "a");
            }
            //+4
            else if (strcmp(recibo, "c") == 0)
            {
                drawX("../outfiles/Deck", "../outfiles/Jugador1", 4);
                strcpy(entrego, "a");
            }
            //jump
            else if (strcmp(recibo, "j") == 0)
            {
                strcpy(entrego, "a");
            }
            //cualquier carta
            else
            {
                strcpy(entrego, play("../outfiles/Jugador1", "../outfiles/Drop"));
            }

            //UNO
            if (cardInHand("../outfiles/Jugador1") == 1)
            {
                printf("JUGADOR 1 : ¡¡¡ UNO !!!\n");
                puts("");
            }
            //gana
            if (cardInHand("../outfiles/Jugador1") == 0)
            {
                printf("JUGADOR 1 : ¡¡¡ GANA !!!\n");
                puts("");
                break;
            }

            //+++++++++++++++++++++++++++++++++++++++++++++turno j2+++++++++++++++++++++++++++++++++++++++++++++
            //+2
            if (strcmp(entrego, "d") == 0)
            {
                drawX("../outfiles/Deck", "../outfiles/Jugador2", 2);
                strcpy(recibo, "a");
            }
            //+4
            else if (strcmp(entrego, "c") == 0)
            {
                drawX("../outfiles/Deck", "../outfiles/Jugador2", 4);
                strcpy(entrego, "a");
            }
            //jump
            else if (strcmp(entrego, "j") == 0)
            {
                strcpy(recibo, "a");
            }
            //cualquier carta
            else
            {
                write(fd01[1], entrego, 20);
                close(fd10[1]); //close write fd10
                //recibe jugada j2
                while (read(fd10[0], recibo, 20) < 0)
                {
                }
            }
            //UNO
            if (cardInHand("../outfiles/Jugador2") == 1)
            {
                printf("JUGADOR 2 : ¡¡¡ UNO !!!\n");
                puts("");
            }
            //gana
            if (cardInHand("../outfiles/Jugador2") == 0)
            {
                printf("JUGADOR 2 : ¡¡¡ GANA !!!\n");
                puts("");
                break;
            }

            //+++++++++++++++++++++++++++++++++++++++++++++turno j3+++++++++++++++++++++++++++++++++++++++++++++
            //+2
            if (strcmp(recibo, "d") == 0)
            {
                drawX("../outfiles/Deck", "../outfiles/Jugador3", 2);
                strcpy(entrego, "a");
            }
            //+4
            else if (strcmp(entrego, "c") == 0)
            {
                drawX("../outfiles/Deck", "../outfiles/Jugador3", 4);
                strcpy(entrego, "a");
            }
            //jump
            else if (strcmp(recibo, "j") == 0)
            {
                strcpy(recibo, "a");
            }
            //cualquier carta
            else
            {
                strcpy(entrego, recibo);
                close(fd02[0]); // close read fd02
                write(fd02[1], entrego, 20);
                close(fd20[1]); //close write fd20
                while (read(fd20[0], recibo, 20) < 0)
                {
                }
            }
            //UNO
            if (cardInHand("../outfiles/Jugador3") == 1)
            {
                printf("JUGADOR 3 : ¡¡¡ UNO !!!\n");
                puts("");
            }
            //gana
            if (cardInHand("../outfiles/Jugador3") == 0)
            {
                printf("JUGADOR 3: ¡¡¡ GANA !!!\n");
                puts("");
                break;
            }

            /*
            //+++++++++++++++++++++++++++++++++++++++++++++turno j4+++++++++++++++++++++++++++++++++++++++++++++
            //+2
            if (strcmp(recibo, "d") == 0){
                drawX("../outfiles/Deck", "../outfiles/Jugador4", 2);
                strcpy(entrego, "a");
            }
            //+4
            else if (strcmp(entrego, "c") == 0){
                drawX("../outfiles/Deck", "../outfiles/Jugador4", 4);
                strcpy(entrego, "a");
            }
            //jump
            else if (strcmp(recibo, "j") == 0){
                strcpy(recibo, "a");
            }
            //cualquier carta
            else{
                strcpy(entrego, recibo);
                close(fd03[0]); // close read fd02
                write(fd03[1], entrego, 20);
                close(fd30[1]); //close write fd20
                while (read(fd30[0], recibo, 20) < 0)
                {
                }
            }
            //UNO
            if (cardInHand("../outfiles/Jugador4") == 1)
            {
                printf("JUGADOR 4 : ¡¡¡ UNO !!!\n");
                puts("");
            }
            //gana
            if (cardInHand("../outfiles/Jugador4") == 0)
            {
                printf("JUGADOR 4 : ¡¡¡ GANA !!!\n");
                puts("");
                break;
            }
            */
        }
    }
    //proceso hijo 1
    if (p == fam[1])
    {
        while (win)
        {
            close(fd01[1]);
            while (read(fd01[0], recibo, 20) < 0)
            {
            }
            puts("\n\n\n");
            printf("\n\tTURNO JUGADOR 2\n");
            strcpy(entrego, play("../outfiles/Jugador2", "../outfiles/Drop"));

            close(fd10[0]);
            write(fd10[1], entrego, 20);
        }
    }
    //proceso hijo 2
    if (p == fam[2])
    {
        while (win)
        {
            close(fd02[1]);
            while (read(fd02[0], recibo, 20) < 0)
            {
            }
            puts("\n\n\n");
            printf("\n\tTURNO JUGADOR 3\n");
            strcpy(entrego, play("../outfiles/Jugador3", "../outfiles/Drop"));

            close(fd20[0]);
            write(fd20[1], entrego, 20);
        }
    }
    //proceso hijo 3
    if (p == fam[3])
    {
        while (win)
        {
            strcpy(recibo, "");
            strcpy(entrego, "");

            close(fd03[1]);
            while (read(fd03[0], recibo, 20) < 0)
            {
            }
            puts("\n\n\n");
            printf("\n\tTURNO JUGADOR 4\n");
            strcpy(entrego, play("../outfiles/Jugador4", "../outfiles/Drop"));

            close(fd30[0]);
            write(fd30[1], entrego, 20);
        }
    }
}
