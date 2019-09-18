#include <stdio.h>
#include <string.h>
#include <dirent.h>


void welcome();
void getString();
void printArguments(char ** arr);
void execute(char **arr);
void getDir();
int chectInput();
int controller();
void crossRoad();
void changeDirectory();

#define MAXARGUMENTS 10


char *(ptr1)[MAXARGUMENTS]; //This pointer array is used for holding the reference to the arguments.
int numberOfArguments;

int status;


int main() {
    welcome();
    while(1) {

        printf("What do you command\n");
        getString();
        fflush(stdin);
        crossRoad();
        //execute(ptr1);

    }
    return 0;
}





void welcome()
    {
        printf("Wlcome to this miniShell\n");
        printf("These are the commands\n");
        printf("if you want to execute a file type EX: ./Hello\n Type [dir] if you will see whats in the directory(Put new line after 'dir'\n ");

    }

/*
 * Getting the inputstring and processes it so it can be used for arguments later on.
 */

void getString(){

        char ** abc = ptr1;
        int i, j = 0, k = 0;
        char str[100] ;
        static char str1[10][20];

       fgets(str,100,stdin); //input from user

        for (i = 0; str[i]!= '\n'; i++) //loopin througt the input string, splits the inputstring into arguments.
        {

            if (str[i]==' ')
            {
                str1[k][j] = '\0';
                k++;
                j = 0;
            }else
                {
                str1[k][j] = str[i];j++;
                }
        }
        str1[k][j] = '\0';



        //Der lægges een til for at få alle argumenter med.
        numberOfArguments = k+1;

    int y = 0;
    for(y; y<numberOfArguments;y++) {

        ptr1[y]=str1[y];
    }
    ptr1[numberOfArguments]=NULL;


        printf("Number of arguments %d", numberOfArguments);
}



/*
 * If the request is to open af file a childprocess have to be made.
 * The execute method checks the command that have been typed, and disides if it will create a child process.
 */

void execute(char **arr) {

    int pid = fork();

    printf("PID %d", pid);
    if (pid == 0) {   //The child process is running

        execvp(arr[1], arr);
        //execvp(argv[1], argv);

    } else if (pid < 0) { //If child process could not be created
        perror("Der er sket en fejl ");
    } else {
        waitpid(-1, &status, 0); //0 menas that it will wait for any child process to terminale}
    }
}


/*
 * Opens the current directory and prints all the files.
 */

void getDir(){

        DIR *dp;
        struct dirent *ep;
        dp = opendir ("./");

        if (dp != NULL)
        {
            while (ep = readdir (dp))  //readdir overrides the previus data created by readir.
                puts (ep->d_name);

            closedir (dp);
        }
        else
            perror ("Couldn't open the directory");
}



void changeDirectory(){
printf("Change directory\n");

}


void crossRoad(){
printf("CrossRoad is running\n");


 switch(controller()){
        case 0:execute(ptr1);
        break;

     case 1: changeDirectory();
         break;

         case 2:getDir();
         break;
 }



}


int controller(){


    char *indput[] = {"exe", "cd","dir"};

    for(int i = 0; i<4;i++){

        printf("ptr1 %s/ indput: %s\n",ptr1[0],indput[i] );
        int res = strcmp(ptr1[0],indput[i]);

        if(res==0){

            printf("I is: %d\n",i);
            return i;

        }
    }

    return -1;
}


/*Checks if the command is dir'*/
/*
int chectInput(){

        char input[] = {"dir"};
        //printf("%s first argument\n",ptr1[0]);

        fflush(stdout); //So it will print to console further on

        int res = strcmp(ptr1[0],input);

        if(res == 0) {
                return 1;
        }
    return 0;
}
*/

void printArguments(char ** arr){
    int y = 0;
    for(y; y<=numberOfArguments;y++){



        printf("Ppinter;%s\n", arr[y]);

    }


}