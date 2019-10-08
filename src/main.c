// C program to demonstrate use of fork() and pipe()
// robado de geeksforgeeks, el martin fue
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include "../include/headerFile.h"

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
    int i, hijo1, hijo2, hijo3;
    int win = 1;

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
    createDeck();
    puts("");
    myMkdir("../outfiles/Drop");     //creacion del mazo de drop
    myMkdir("../outfiles/Jugador1"); //creacion del mazo del jugador 1
    myMkdir("../outfiles/Jugador2"); //creacion del mazo del jugador 2
    myMkdir("../outfiles/Jugador3"); //creacion del mazo del jugador 3
    myMkdir("../outfiles/Jugador4"); //creacion del mazo del jugador 4
    puts("");

    drawHand("../outfiles/Deck", "../outfiles/Jugador1");
    drawHand("../outfiles/Deck", "../outfiles/Jugador2");
    drawHand("../outfiles/Deck", "../outfiles/Jugador3");
    drawHand("../outfiles/Deck", "../outfiles/Jugador4");
    puts("");

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
    /*  if(p == fam[0]) printf("padre\n");
        if(p == fam[1]) printf("hijo1\n");
        if(p == fam[2]) printf("hijo2\n");
        if(p == fam[3]) printf("hijo3\n");  */
    p = getpid();

    if (p == fam[0])
    { //escribir vn fd01 y leer cn fd30
        while (win)
        {
            printf("proceso padre\n");
            strcpy(recibo, "");
            strcpy(entrego, "");

            //interaccion hijo 1
            close(fd01[0]); // close read fd01
            strcpy(entrego, play("../outfiles/Jugador1", "../outfiles/Drop"));
            write(fd01[1], entrego, 20);

            close(fd10[1]); //close write fd10
            while (read(fd10[0], recibo, 20) < 0)
            {
            }

            //interaccion hijo 2
            strcpy(entrego, recibo);
            close(fd02[0]); // close read fd02
            write(fd02[1], entrego, 20);

            close(fd20[1]); //close write fd20
            while (read(fd20[0], recibo, 20) < 0)
            {
            }

            //interaccion hijo 3
            strcpy(entrego, recibo);
            close(fd03[0]); // close read fd03
            write(fd03[1], entrego, 20);

            close(fd30[1]); //close write fd30
            while (read(fd30[0], recibo, 20) < 0)
            {
            }
        }
    }
    //proceso hijo 1
    if (p == fam[1])
    {
        while (win)
        {
            strcpy(recibo, "");
            strcpy(entrego, "");

            close(fd01[1]);
            while (read(fd01[0], recibo, 20) < 0)
            {
            }
            printf("proceso h1\n");
            strcpy(entrego, play("../outfiles/Jugador2", "../outfiles/Drop"));

            close(fd10[0]);
            write(fd10[1], entrego, 20);
        }
    }
    if (p == fam[2])
    {
        while (win)
        {
            strcpy(recibo, "");
            strcpy(entrego, "");

            close(fd02[1]);
            while (read(fd02[0], recibo, 20) < 0)
            {
            }
            printf("proceso h2\n");
            strcpy(entrego, play("../outfiles/Jugador3", "../outfiles/Drop"));

            close(fd20[0]);
            write(fd20[1], entrego, 20);
        }
    }

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
            printf("proceso h3\n");
            strcpy(entrego, play("../outfiles/Jugador4", "../outfiles/Drop"));

            close(fd30[0]);
            write(fd30[1], entrego, 20);
        }
    }
}
