#include "../include/headerFile.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

//comment
    //mazo real
    createDeck();
    puts("");
    myMkdir("../outfiles/Drop");        //creacion del mazo de drop
    myMkdir("../outfiles/Jugador1");    //creacion del mazo del jugador 1
    myMkdir("../outfiles/Jugador2");    //creacion del mazo del jugador 2
    myMkdir("../outfiles/Jugador3");    //creacion del mazo del jugador 3
    myMkdir("../outfiles/Jugador4");    //creacion del mazo del jugador 4
    puts("");

    drawHand("../outfiles/Deck", "../outfiles/Jugador1");
    //drawHand("../outfiles/Deck", "../outfiles/Jugador2");
    //drawHand("../outfiles/Deck", "../outfiles/Jugador3");
    //drawHand("../outfiles/Deck", "../outfiles/Jugador4");
    puts("");
    moveFileToFolder("amarillo_+2_1.txt", "../outfiles/Deck", "../outfiles/Drop");
    //printHand("../outfiles/Jugador1", 1);
    //printf("\n************** DROP **************\n");
    //printHand("../outfiles/Drop", 0);
    //printf("************** DROP **************\n");

    char(**carta) = cardName("../outfiles/Drop", 1);
    printf("lul\n");
    printf("%s %s %s   \n", carta[0], carta[1], carta[2]);
    for (int i = 0; i < 3; i++)
    {
        free(carta[i]);
    }
    
    free(carta);


    return 0;
}