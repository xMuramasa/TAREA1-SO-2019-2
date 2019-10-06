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

    DrawHand("../outfiles/Deck", "../outfiles/Jugador1");
    DrawHand("../outfiles/Deck", "../outfiles/Jugador2");
    DrawHand("../outfiles/Deck", "../outfiles/Jugador3");
    DrawHand("../outfiles/Deck", "../outfiles/Jugador4");
    puts("");

    return 0;
}