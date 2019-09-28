#include "../include/headerFile.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

//comment
    //mazo real
    createDeck();
    puts("");
    myMkdir("../outfiles/Drop");
    puts("");

    //mazo para test
    createTest("");
    puts("");

    myMkdir("../outfiles/testHand");
    puts("");

    Draw("../outfiles/Test", "../outfiles/testHand", 3);
    //test3("../outfiles/Test");

    return 0;
}