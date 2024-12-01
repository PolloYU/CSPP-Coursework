//C program code : 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// FILE * fptr; is a way to declare a file pointer
// fptr = fopen(name, ""); with this we are able to write in the file
// fclose(fptr); // closes the file

void createFile(){
    FILE *fptr;
    char name[1000];
    int lines;
    
    printf("Enter the file name(with file extension): ");
    scanf("%s", name);
    getchar();
    fptr = fopen(name, "w"); //checking if the file was opened 

    if(fptr == NULL){
        printf("Couldn't open the file\n");
    }else{
        printf("How many lines of content do you want to enter> ");
        scanf("%d", &lines);
        getchar(); //To take the \n

        char content[1000];
        for(int i = 0; i < lines; i++){
            printf("Enter the content for line %d ", i + 1);
            fgets(content, 1000, stdin); //like a getter to get the input line
            fputs(content, fptr); // writing the line into the file
        }
        printf("\nFile created\n");
        fclose(fptr);
    }
}

void showFile(){
    FILE *fptr;
    char name[1000];
    printf("Enter name of file to be displayed(With file extension): ");
    scanf("%s", name);
    getchar();
    fptr = fopen(name, "r");

    if(fptr == NULL){
        printf("Couldn't open the file\n");
    }else{
        char content[10000];
        printf("\nThe content of the file is as follows:\n");
        while(fgets(content, 10000, fptr)){  // reading each line
            printf("%s", content);
        }
        fclose(fptr);
    }   
}

void copyFile(){
    FILE *ogfptr; //original file  // The original file which content's we want to copy
    FILE *newfptr; //the new file  // the file in which we want to put the content

    char ogname[1000];
    char newname[1000];

    printf("Enter the name of the original file(with file extension): ");
    scanf("%s", ogname);
    getchar();
    printf("Enter the file to which you want to copy everything(with file extension): ");
    scanf("%s", newname);
    getchar();

    ogfptr = fopen(ogname, "r");
    newfptr = fopen(newname, "w");

    if(ogfptr == NULL || newfptr == NULL){
        printf("Couldn't open the file\n");
    }else{
        char lineContent[10000];
        while(fgets(lineContent, 10000, ogfptr)){
            fputs(lineContent, newfptr);
        }
        fclose(ogfptr);
        fclose(newfptr);
    }
}

void deleteFile(){
    char name[1000];
    printf("Enter the name of file to delete(with file extension): ");
    scanf("%s", name);
    getchar();

    if(remove(name) == 0){
        printf("Removed the file\n");
    }else{
        printf("Couldn't delete the file\n");
    }
}

/*  Extension of File Operations: Compare Files function.Idea is from question4 itself.        
    Our team did q4 separately so there is a need for code comparison to prevent errors in merging step.
    This function can be used for checking differences between text files or directly judge if two files are same. */
void compareFile(){
    FILE *fptr1;
    FILE *fptr2;

    char name1[1000];
    char name2[1000];

    printf("Enter the name of the first file(with file extension): ");
    scanf("%s", name1);
    getchar();
    printf("Enter the name of the second file(with file extension): ");
    scanf("%s", name2);
    getchar();

    fptr1 = fopen(name1, "r");
    fptr2 = fopen(name2, "r");

    if(fptr1 == NULL || fptr2 == NULL){
        printf("Couldn't open the file\n");
        return;
    }

    char content1[1000];
    char content2[1000];
    int line_count = 1; //count the number of lines so that we can know where the difference is
    int difference = 0; //to count the number of differences


    //while Loop and the strcmp function learned from Lab 3 can find, count differences and print them out until comparison is finished (one file is fully read).
    while(true){
        bool hascontent1 = fgets(content1, 1000, fptr1) != NULL;
        bool hascontent2 = fgets(content2, 1000, fptr2) != NULL;

        //ending the loop if both files are fully read
        if(!hascontent1 && !hascontent2){
            break;
        }

        //if one file is shorter
        if(!hascontent1){
            printf("File 1 is shorter. Comparing up to %d lines\n", line_count);
            difference ++;
            break;
        }

        if(!hascontent2){
            printf("File 2 is shorter. Comparing up to %d lines\n", line_count);
            difference ++;
            break;
        }

        //comparing the content of the two files
        if(strcmp(content1, content2) != 0){
            printf("Difference found at line %d\n", line_count);
            printf("File 1: %s", content1);
            printf("File 2: %s", content2);
            difference ++;
        }
        line_count ++;
    }

    if(difference == 0){
        printf("The files are identical\n");
    } else if(difference > 0){
        printf("Found %d differences\n", difference);
    }
    fclose(fptr1);
    fclose(fptr2);
}

void appendLine(){
    FILE *fptr;
    char name[1000];
    printf("Enter file name(with the file extension): ");
    scanf("%s", name);
    getchar();

    fptr = fopen(name, "a");

    if(fptr == NULL){
        printf("Couldn't open the file\n");
    }else{
        char content[10000];
        printf("Enter line: ");
        fgets(content, 10000, stdin);   // reading the input line
        fputs(content, fptr);           // appending the new line to the file
        fclose(fptr);
    }
}

void deleteLine(){
    FILE *fptr;
    FILE *ftemp;
    char name[1000];
    printf("Enter the file name: ");
    scanf("%s", name);
    getchar();

    fptr = fopen(name, "r");
    ftemp = fopen("temp.txt", "w"); //opening a temporary file in writing mode

    if(fptr == NULL || ftemp == NULL){
        printf("Couldn't open the file\n");
    }else{
        char lineNumChar;
        printf("Enter line number> ");
        scanf("%c", &lineNumChar);
        getchar();

        int lineNum = lineNumChar - '0'; //preventing error from ocuring if user enters a letter instead of int
        
        int line = 1;
        char content[10000];
        bool deleted = false;
        while(fgets(content, 10000, fptr)){
            if(line != lineNum){
                fputs(content, ftemp); // copying the lines except the one we deleted
            }else{
                deleted = true;
            }
            line++;
        }
        if(deleted){
            printf("Deleted successfully\n");
        }else{
            printf("Line is out of range\n");
        }
    }
    fclose(fptr);
    fclose(ftemp);
    remove(name);
    rename("temp.txt", name);
}

void insertLine(){
    FILE *fptr;
    FILE *ftemp;
    char name[1000];
    printf("Enter the file name: ");
    scanf("%s", name);
    getchar();

    fptr = fopen(name, "r");
    ftemp = fopen("temp.txt", "w");

    if(fptr == NULL || ftemp == NULL){
        printf("Couldn't open the file\n");
    }else{
        char lineNumChar;
        printf("Enter line number> ");
        scanf("%c", &lineNumChar);
        getchar();

        int lineNum = lineNumChar - '0'; //preventing error from ocuring if user enters a letter instead of int
        
        int line = 1;
        char content[10000];
        bool inserted = false;
        while(fgets(content, 10000, fptr)){
            if(line != lineNum){
                fputs(content, ftemp);
            }else{
                char insertContent[10000];
                printf("Enter the line to be inserted: ");
                fgets(insertContent, 10000, stdin);
                fputs(insertContent, ftemp);
                fputs(content, ftemp);
                inserted = true;
            }
            line++;
        }
        if(inserted){
            printf("Inserted successfully\n");
        }else{
            printf("Line is out of range\n");
        }
    }
    fclose(fptr);
    fclose(ftemp);
    remove(name);   // Deleting the original file
    rename("temp.txt", name);   //Renaming the temporary file
}

void showLine(){
    FILE *fptr;
    char name[1000];

    printf("Enter the file name: ");
    scanf("%s", name);
    getchar();

    fptr = fopen(name, "r");

    int line = 1;
    bool showed = false;
    char lineNumChar;
    printf("Enter the line number: ");
    scanf("%c", &lineNumChar);
    getchar();

    int lineNum = lineNumChar - '0';  //preventing error from ocuring if user enters a letter instead of int

    char content[10000];
    while(fgets(content, 10000, fptr)){
        if(line == lineNum){
            printf("%s", content);
            showed = true;
        }
        line++;
    }
    if(!showed){
        printf("Out of range\n");
    }
    fclose(fptr);
}

/*  Extra Operations1: Security Operations
    Idea of this part is the need for users to protect their personal information saved in text files.
    One solution is to make information unrecognizable. The Lab 1 exercise 1.3 inspired me to modify the text by adding an integer to a char.
    Users can type a key and easily change the content of text file. */

void encryptFile(){
    FILE *fptr1;
    FILE *fptr2;

    char name1[1000];
    char name2[1000];
    int key;

    printf("Enter the file name(with file extension): ");
    scanf("%s", name1);
    getchar();
    printf("Enter the new encrypted file name(with file extension): ");
    scanf("%s", name2);
    getchar();
    printf("Enter the key(integer): ");
    scanf("%d", &key);
    getchar();

    fptr1 = fopen(name1, "r");
    fptr2 = fopen(name2, "w");

    if(fptr1 == NULL || fptr2 == NULL){
        printf("Couldn't open the file\n");
    }else{
        char char1;
        while((char1 = fgetc(fptr1)) != EOF){ //loop until the end of the file
            char char2 = char1 + key; //use addition for encryption
            fputc(char2, fptr2); //writing the encrypted content to the new file
        }
        printf("Encryption is done.Please remember your key is %d\n", key);
    }
    fclose(fptr1);
    fclose(fptr2);
}

void decryptFile(){
    FILE *fptr1;
    FILE *fptr2;

    char name1[1000];
    char name2[1000];
    int key;

    printf("Enter the file name(with file extension): ");
    scanf("%s", name1);
    getchar();
    printf("Enter the new decrypted file name(with file extension): ");
    scanf("%s", name2);
    getchar();
    printf("Enter the key(integer): ");
    scanf("%d", &key);
    getchar();

    fptr1 = fopen(name1, "r");
    fptr2 = fopen(name2, "w");

    if(fptr1 == NULL || fptr2 == NULL){
        printf("Couldn't open the file\n");
    }else{
        char char1;
        //the fgetc function is learned from Lab 4
        //when noticing the fgets fputs pair, I searched fputc and found it.
        while((char1 = fgetc(fptr1)) != EOF){
            char char2 = char1 - key; //use subtraction for decryption
            fputc(char2, fptr2);
        }
        printf("Decrypted file is now created\n");
    }
    fclose(fptr1);
    fclose(fptr2);
}

/*  Extra Operation2: Text Structure Operation
    It is time-consuming to handle those spaces and additional lines in text file using multiple line operations.
    And it is easy to get error again when correcting text manually.
    The removeTextSpaces() and removeExtraRows() functions can help users to make the format of text file standard.  */

void removeTextSpaces(){
    FILE *fptr1;
    FILE *fptr2;

    char name1[1000];
    char name2[1000];

    printf("Enter the file name(with file extension): ");
    scanf("%s", name1);
    getchar();
    printf("Enter the new file name(with file extension): ");
    scanf("%s", name2);
    getchar();


    fptr1 = fopen(name1, "r");
    fptr2 = fopen(name2, "w");

    if(fptr1 == NULL || fptr2 == NULL){
        printf("Couldn't open the file\n");
    }else{
        char content[1000];
        while(fgets(content, 1000, fptr1)){
            char row[1000];
            int i =0;
            int n = 0;
            bool lastChar = false; //check if the last character is a space

            while(content[i] == ' '){
                i++;
            }

            while(content[i] != '\0'){
                if(content[i] != ' '){
                    //if the character is not a space, just copy
                    row[n] = content[i];
                    n++;
                    lastChar = false;
                }else if(!lastChar && content[i+1] != '\0' && content[i+1] != '\n'){
                    //if there are spaces together, copy only one space
                    row[n] = ' ';
                    n++;
                    lastChar = true;
                }
                i++;
            }


            if(n > 0 && row[n-1] != '\n'){
                row[n] = '\n';
                n++;
            }

            //end the string
            row[n] = '\0';
            fputs(row, fptr2);
        }
        printf("Spaces removed\n");
    }
    fclose(fptr1);
    fclose(fptr2);
}

void removeExtraRows(){
    FILE *fptr1;
    FILE *fptr2;

    char name1[1000];
    char name2[1000];

    printf("Enter the file name(with file extension): ");
    scanf("%s", name1);
    getchar();
    printf("Enter the new file name(with file extension): ");
    scanf("%s", name2);
    getchar();

    fptr1 = fopen(name1, "r");
    fptr2 = fopen(name2, "w");

    if(fptr1 == NULL || fptr2 == NULL){
        printf("Couldn't open the file\n");
    }else{
        char content[1000];
        bool lastRow = false; //similarly, check if the last row is empty

        while(fgets(content, 1000, fptr1)){
            bool thisRow = (content[0] == '\n'); //check if the row is empty
            if(!thisRow || !lastRow){
                fputs(content, fptr2); //copy text and skip extra empty rows
            }
            lastRow = thisRow; //update last row
        }
        printf("Extra rows removed\n");
    }
    fclose(fptr1);
    fclose(fptr2);
}

int main(){
    char choice;
    char choice2;
    char choice3;
    while(true){
        printf("\nThese are the following commands possible. Use the number to get started with the particular operation\n");
        printf("Create file -- 1\n");
        printf("Copy file -- 2\n");
        printf("Delete file -- 3\n");
        printf("Show file -- 4\n");
        printf("Append Line -- 5\n");
        printf("Delete Line -- 6\n");
        printf("Insert Line -- 7\n");
        printf("Show Line -- 8\n");
        printf("More options -- 9\n"); //4b part
        printf("Any other key for exit\n");
        printf("> ");
        scanf("%c", &choice);
        getchar(); //capturing the enter

        switch(choice){
            case '1':
                createFile();
                break;
            case '2':
                copyFile();
                break;
            case '3':
                deleteFile();
                break;
            case '4':
                showFile();
                break;
            case '5':
                appendLine();
                break;
            case '6':
                deleteLine();
                break;
            case '7':
                insertLine();
                break;
            case '8':
                showLine();
                break;
            case '9':
                printf("Compare file -- 1\n");
                printf("Encrypt file -- 2\n");
                printf("Decrypt file -- 3\n");
                printf("Remove text spaces -- 4\n");
                printf("Remove extra rows -- 5\n");
                printf("> ");
                scanf("%c", &choice2);
                getchar();
                switch(choice2){
                    case '1':
                        compareFile();
                        break;
                    case '2':
                        encryptFile();
                        printf("Please remember your key\n");
                        printf("Would you like to remove the original file?\n(make sure you have a backup) (type y for yes): ");
                        scanf("%c", &choice3);
                        getchar();
                        if(choice3 == 'y'){
                            deleteFile();
                        }
                        break;
                    case '3':
                        decryptFile();
                        printf("Would you like to remove the encrypted file? (type y for yes): ");
                        scanf("%c", &choice3);
                        getchar();
                        if(choice3 == 'y'){
                            deleteFile();
                        }
                        break;
                    case '4':
                        removeTextSpaces();
                        printf("Would you like to remove the original file? (type y for yes): ");
                        scanf("%c", &choice3);
                        getchar();
                        if(choice3 == 'y'){
                            deleteFile();
                        }
                        break;
                    case '5':
                        removeExtraRows();
                        printf("Would you like to remove the original file? (type y for yes): ");
                        scanf("%c", &choice3);
                        getchar();
                        if(choice3 == 'y'){
                            deleteFile();
                        }
                        break;
                    default:
                        printf("Invalid option\n");
                        break;
                }
                break;
            default:
                return 0;
        }
    }
    return 0;
}