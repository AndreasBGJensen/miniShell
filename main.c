#include <stdio.h>
#include <string.h>
#include <dirent.h>


void welcome();
void getString();
void execute(char **arr);
void getDir();
int controller();
void crossRoad();
void changeDirectory();
void getDirectory();
char ** removeFirstElement(char **arr);
void makeDirectory(char **arr);

#define MAXARGUMENTS 10


char *(ptr1)[MAXARGUMENTS]; //This pointer array is used for holding the reference to the arguments.
int numberOfArguments;

int status;


int main() {
    welcome();
    while(1) {

        printf("\nWhat do you command\n");
        getString();
        fflush(stdin);
        crossRoad();

    }
    return 0;
}


/*
 * Prints instructione and an welcome message.
 */
void welcome()
    {
        printf("Wlcome to this miniShell\n");
        printf("These are the commands\n");
        printf("if you want to execute a file type EX: ./Hello\n Type [dir] if you will see whats in the directory(Put new line after 'dir'\n ");

    }

/*
 * Recives the inputstring and processes it so it can be used for arguments later on.
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
            str1[k][j] = '\0';// adds \0 at the end of the argument
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
    ptr1[numberOfArguments]=NULL; //For at argumenterne kan anvendes for funktionen execvp()

}



/*
 * The controller method desides what action that will be made. It compares the first input argument with
 * a predefined array: exe for executing the programme, cd for change derictory.
 * The controller coorporates with the function crossRoad().
 */
int controller(){

    char *indput[] = {"exe", "cd","dir", "mkdir"};

    for(int i = 0; i<4;i++){

        int res = strcmp(ptr1[0],indput[i]);

        if(res==0){

            return i;

        }
    }
    return -1;
}


/*
 * crossRoad function executes the desided action.
 * It gets the input from the controller method.
 */

void crossRoad(){

    switch(controller()){
        case 0:execute(ptr1);
            break;

        case 1: changeDirectory();
            break;

        case 2:getDir();
            break;

        case 3: makeDirectory(ptr1);
            break;

        default: printf("Unknown command\n");
    }
}


/*
 * If the request is to open af file a childprocess have to be made.
 * The execute method checks the command that have been typed, and disides if it will create a child process.
 */
void execute(char **arr) {

    arr = removeFirstElement(arr);

    int pid = fork();

    if (pid == 0) {   //The child process is running

        execvp(arr[0], arr);
        //execvp(argv[1], argv);

    } else if (pid < 0) { //If child process could not be created
        perror("Der er sket en fejl\n ");
    } else {
        waitpid(-1, &status, 0); //0 menas that it will wait for any child process to terminale}
    }
}


/*
 * Opens the current directory and prints all the files.
 * The code is originally from: https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister.html
 */
void getDir(){

    printf("The current directory is:"); getDirectory();

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


/*
 * Changes the directory and prints the directory
 */
void changeDirectory(){

    chdir(ptr1[1]);
    getDirectory();
}


/*
 * Prints the durrent directory out to the terminal
 *The method is inspired from: https://stackoverflow.com/questions/298510/how-to-get-the-current-directory-in-a-c-program
 */
void getDirectory(){

    char cwd[200];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");

    }
}

/*
 * Removes the first element of an array.
 */
char ** removeFirstElement(char **arr){

    for(int i=1;i<4;i++) {
        arr[i - 1] = arr[i];
    }
    return arr;
}

void makeDirectory(char **arr){
    arr = removeFirstElement(arr);

    if(mkdir(arr[0])==0){

        printf("The directory named: %s, has been created", arr[0]);
    }else{
        printf("Something went wrong");
    }


}