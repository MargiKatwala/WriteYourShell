/*
 CS 361 - Project 3
 Write a Shell program
 Margi Katwala
 mkatwa3
 676885503
 Due Date : 3/2/18
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

//Two functions to handle the sigal
void sigint_handler(int sigint){
    if(sigint==SIGINT)
    {
        char msg[] = "Signal SIGINT handled.\n";
        write(1, msg, sizeof(msg));

    }

    exit(0);
}
void sigstp_handler(int sigstp){
    if(sigstp == SIGTSTP){
        char msg[] = "Signal SIGSTP handled.\n";
        write(1, msg, sizeof(msg));
    }
    exit(0);//exits the program
}
int main()
{   //variables
    char input[500];
    char *args[20];
    //signal Handler
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigstp_handler);

   // int var1=0;

    do{
        printf("361> ");//standar input
        fgets(input, 500, stdin);//gets the line
        input[strcspn(input, "\n")] = 0;
        char *word = strtok(input, " ");//seprates the wrod

//        while(word !=NULL){
//          line[var1]=(int)word;
//          word = strtok(line, " ");
//          var1++;
//        }
        //check to exit the program

        if(strcmp(input, "exit") == 0)
        {
            exit(0);
        }


        //starts to check the commands
        char *new_file = (char *)malloc(sizeof(char) * 50);
        int i = 0;
        int size = 0;
        int io_redirect; // variable to redirect
        do{

            if((strcmp(word, ">") == 0))
            {
                io_redirect = 1;
                word = strtok(NULL, " ");
                strcpy(new_file, word);
                word = strtok(NULL, " ");
            }
            else if((strcmp(word, ">>") == 0))
            {
                io_redirect = 2;
                word = strtok(NULL, " ");
                strcpy(new_file, word);
                word = strtok(NULL, " ");
            }
            else if((strcmp(word, "<") == 0))
            {
                io_redirect= 3;
                word = strtok(NULL, " ");
                strcpy(new_file, word);
                word = strtok(NULL, " ");
            }

            else
            {   //new file copy over
                args[i] = (char *)malloc(sizeof(char) * 100);
                size++;
                strcpy(args[i], word);
                word = strtok(NULL, " ");
                i = i + 1;
            }

            args[i] = (char *)malloc(sizeof(char) * 100);
            args[i] = NULL;

        }while(word);//while the word is inputed
        //after the word is inputed
        int pid = fork();

        if(pid !=0){
            int status;
            wait(&status);

        }
        else

        {
            int line;
            if(io_redirect == 1)
            {
                line = open(new_file, O_WRONLY|O_CREAT|O_TRUNC, S_IROTH);
                dup2(line, 1);
            }
            else if(io_redirect == 2)
            {
                line = open(new_file, O_APPEND|O_CREAT|O_WRONLY, S_IROTH);
                dup2(line, 2);
            }
          else
            {
                //redirects if its 3
                line = open(new_file, O_RDONLY, S_IROTH);
                dup2(line, 3);
            }
            
            //statments to print
            printf("PID: %d\n", getpid());
            printf("Exit: 0\n");
            execvp(args[0], args);
            exit(0);

        }

    }while(input);
    return 0;
}


