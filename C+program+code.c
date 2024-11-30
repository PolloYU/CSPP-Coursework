//C program code : 

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void createFile(){
    FILE *fptr;
    char name[1000];
    int lines;
    
    printf("Enter the file name(with file extension): ");
    scanf("%s", name);
    getchar();
    fptr = fopen(name, "w");

    if(fptr == NULL){
        printf("Couldn't open the file\n");
    }else{
        printf("How many lines of content do you want to enter> ");
        scanf("%d", &lines);
        getchar(); //To take the \n

        char content[1000];
        for(int i = 0; i < lines; i++){
            printf("Enter the content for line %d ", i + 1);
            fgets(content, 1000, stdin);
            fputs(content, fptr);
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
        while(fgets(content, 10000, fptr)){
            printf("%s", content);
        }
        fclose(fptr);
    }   
}

void copyFile(){
    FILE *ogfptr; //original file
    FILE *newfptr; //the new file

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
    }

    char content1[1000];
    char content2[1000];
    int line_count = 1;
    int difference = 0;

    while(true){
        bool hascontent1 = fgets(content1, 1000, fptr1) != NULL;
        bool hascontent2 = fgets(content2, 1000, fptr2) != NULL;

        if(!hascontent1 && !hascontent2){
            break;
        }

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
        fgets(content, 10000, stdin);
        fputs(content, fptr);
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
        bool deleted = false;
        while(fgets(content, 10000, fptr)){
            if(line != lineNum){
                fputs(content, ftemp);
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
    remove(name);
    rename("temp.txt", name);
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

int main(){
    char choice;
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
        printf("Compare file -- 9\n");
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
                compareFile();
                break;
            default:
                return 0;
        }
    }
    return 0;
}