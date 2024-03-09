/** 
 *  IZP PROJECT 1 - working with strings
 *  Author: David Bujzas, xbujzad00@stud.fit.vutbr.cz 
 *  Date: 15.10.2023 
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_STRING_LENGTH 100 // maximum characters allowed in a string

//function for converting strings to uppercase
void convertToUppercase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

//function which checks if there are any matching characters
int check(char *availableChars, char str){
    int stringLen = strlen(availableChars);
    int n = 0;
    int i = 0;
    while(i < stringLen){
        if(availableChars[i] == str){
            n++;
        }
        i++;
    }
    return n;
}

//function which sorts output into alphabetical order
void alphabeticalOrder(char* str) {
    int stringLen = strlen(str);

    for (int i = 0; i < stringLen; i++) {
        for (int j = i + 1; j < stringLen; j++) {
            if (str[i] > str[j]) {
                char temporary = str[i];
                str[i] = str[j];
                str[j] = temporary;
            }
        }
    }
}

int main(int argc, char* argv[]){

    char bufferStr[MAX_STRING_LENGTH + 2] = {0}; //array in which the strings from stdin are stored, it also adds two spaces for \n and '\0'
    char foundStr[MAX_STRING_LENGTH] = {0}; //array in which matching string is stored
    char availableChars[MAX_STRING_LENGTH] = {0}; //array in which the enabled characters are stored
    int matches = 0;
    int i;
    char* filter = ""; //variable which takes the form of an empty string or argv[1]

    //checking how many arguments were input and initializing filter to argv[1]
    if(argc == 2){
        filter = argv[1];
    }

    //checking if the input contains more than two arguments
    if(argc > 2){
        fprintf(stderr, "ERROR: Please provide one argument!\n");
        return 1;
    }

    convertToUppercase(filter);

    //main loop which filters stdin based on the argument
    while(fgets(bufferStr, sizeof(bufferStr), stdin) != NULL){
        int bufferLen = strlen(bufferStr) - 1; //-1 in order to remove the newline char
        int availableCharsLen = strlen(availableChars);
        int argLen = strlen(filter);
        convertToUppercase(bufferStr);
        bool flag = true;

        //loop which checks if the buffer string is equal to the argument
        for(i = 0; i < argLen; i++){
            if(bufferStr[i] == filter[i]){
                flag = true;
            }
            else{
                flag = false;
                break;
            }
        }

        //when the flag is true, use the check function
        if(flag){
            int n = check(availableChars, bufferStr[i]);
            //if the lengths dont match, check if the count is 0
            if(bufferLen != argLen){
                //when the count is 0, add the matching characters into the array for enabled characters
                if(n == 0){
                    availableChars[availableCharsLen] = bufferStr[i];
                }
            }
            //if there are no matches, copy the characters from the buffer into the array for found strings
            if(matches == 0){
                strcpy(foundStr, bufferStr);
            }

            matches++;
        }

    }
    //the function alphabetically sorts the enabled characters array
    alphabeticalOrder(availableChars);

    //if there is just a single match, the output is a matching string
    if (matches == 1)
    {
        printf("Found: %s", foundStr);
    }
    //if there is more than one match, the output is an array of enabled characters
    else if (matches > 1)
    {
        printf("Enable: %s\n", availableChars);
    }
    //if there are no matches, the argument we input is not found in stdin
    else
    {
        printf("Not found\n");
    }
    
    return 0;
}