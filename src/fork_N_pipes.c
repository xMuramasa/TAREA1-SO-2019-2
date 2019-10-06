// C program to demonstrate use of fork() and pipe()
// robado de geeksforgeeks, el martin fue
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    // se usan 4 pipes
    // el primero para el proceso padre
    // los que quedan para los procesos hijos

    int fd1[2]; // se usa para almacenar los mensajes 
    int fd2[2]; // se usa para almacenar los mensajes 
    int fd3[2]; // se usa para almacenar los mensajes 
    int fd4[2]; // se usa para almacenar los mensajes 

    char fixed_str[] = "\tlamao jaja saludos";
    char input_str[100];   // user input 
    pid_t p;               // pid 
    int processCount = 0;  //cantidad de procesos

    if (pipe(fd1) == -1 && pipe(fd2) == -1 && pipe(fd3) == -1 && pipe(fd4) == -1){
        fprintf(stderr, "Fallaron los pipes");
        return 1;
    }


    printf("Enter a string:\t");
    scanf("%s", input_str);

    do{      // <---------------- creacion de forks
        p = fork();
        processCount++;
    } while (p > 0 && processCount < 3);

    

    if (p < 0){

        fprintf(stderr, "fork Failed");
        return 1;
    
    }if (p > 0){ // Parent process
        printf("this da parent\n");

        char concat_str[100];

        close(fd1[0]); // Close reading end of first pipe

        // Write input string and close writing end of first
        // pipe.
        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);

        // Wait for child to send a string
        wait(NULL);
        close(fd2[1]); // Close writing end of second pipe

        // Read string from child, print it and close
        // reading end.
        read(fd2[0], concat_str, 100);
        printf("Concatenated string %s\n", concat_str);
        close(fd2[0]);

    }else{ // child process
        printf("this da child\n");
        close(fd1[1]); // Close writing end of first pipe

        // Read a string using first pipe
        char concat_str[100];
        read(fd1[0], concat_str, 100);

        // Concatenate a fixed string with it
        int k = strlen(concat_str);
        int i;
        for (i = 0; i < strlen(fixed_str); i++)
            concat_str[k++] = fixed_str[i];

        concat_str[k] = '\0'; // string ends with '\0'

        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);

        // Write concatenated string and close writing end
        write(fd2[1], concat_str, strlen(concat_str) + 1);
        close(fd2[1]);

        exit(0);
    }
}