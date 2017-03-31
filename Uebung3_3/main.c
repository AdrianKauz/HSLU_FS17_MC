/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 3.1
 * Reads every word from a simple txt-file and counts all the different words.
 * Bleh!
 * @author Adrian Kauz
 * @version 0.9
 * @date 2017.03.31
 * @return 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defines
#define MAXWORD 50
#define BUFSIZE 50


// Struct
struct tnode{
    char* word;
    int count;
    struct tnode* left;
    struct tnode* right;
};

// Globals
char buf[BUFSIZE];
int bufp = 0;


// Prototypes
int getch(void);
void ungetch(int c);
int getWord(char* pWord, int lim);
struct tnode* talloc();
struct tnode* addTree(struct tnode* pN, char* pW);
void treePrintInOrder(struct tnode* pN);
void treePrintPostOrder(struct tnode* pN);


/**
 * Convert user's input into a person-struct.
 * Part of code is from "Uebungen_3.pdf"
 * @author Adrian Kauz
 * @param argc      Argumentcounter
 * @param argv[]    Array of Arguments
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[]) {
    system("cls");

    if(argc != 2){
        if(argc == 1){
            printf("Filename is missing...\n");
        }
        else{
            printf("Too many arguments...\n");
        }
    }
    else{
        struct tnode* root = NULL;
        char word[MAXWORD];

        printf("\"%s\" reading file...\n", argv[1]);

        if(freopen(argv[1], "r", stdin) == NULL){
            printf("...couldn't open \"%s\"!", argv[1]);
        }
        else{
            while(getWord(word, MAXWORD) != EOF){
                if(isalpha((*word))){
                    root = addTree(root, word);
                }
            }
        }

        printf("\nInorder:\n--------\n");
        treePrintInOrder(root);

        printf("\nPostorder:\n----------\n");
        treePrintPostOrder(root);

        return(EXIT_SUCCESS);
    }

    return(EXIT_FAILURE);
}

/**
 * Get next char from "stdin"
 * Part of code is from "Uebungen_3.pdf"
 * @author Unknown
 * @return int      Charcode
 */
int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}


/**
 * Release char from "stdin"
 * Part of code is from "Uebungen_3.pdf"
 * @author Unknown
 */
void ungetch(int c){
    if(bufp >= BUFSIZE){
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}


/**
 * Get next word from "stdin"
 * Part of code is from "Uebungen_3.pdf"
 * @author Unknown
 * @param  lim      Limiter for wordsize
 * @param  word     Word-Pointer
 * @return int      First charcode from the word
 */
int getWord(char* pWord, int lim){
    int c;
    char* pW = pWord;

    // Ignore whitespace
    while(isspace(c = getch())){
    };

    if (c != EOF){
        *pW++ = c;
    }

    // End of word reached
    if (!isalpha(c)){
        *pW = '\0';
        return(c);
    }

    // Read word until character is not a number or alphanumeric
    for( ; --lim > 0 ; pW++){
        if(!isalnum(*pW = getch())){
            ungetch(*pW);
            break;
        }
    }

    *pW ='\0';

    return pWord[0];
}


/**
 * Allocate space for struct-type
 * Part of code is from "Uebungen_3.pdf"
 * @author Unknown
 * @return tnode*   Pointer
 */
struct tnode* talloc(){
    return malloc(sizeof(struct tnode));
}


/**
 * Adds a new tree-element to an existing tree
 * Part of code is from "Uebungen_3.pdf"
 * @author Unknown
 * @param  pN       tnode-Pointer
 * @param  pW       Word-Pointer
 * @return tnode*   Pointer of
 */
struct tnode* addTree(struct tnode* pN, char* pW){
    int cond;

    if(pN == NULL){
        pN = talloc();
        pN -> word = strdup(pW);
        pN -> count = 1;
        pN -> left = NULL;
        pN -> right = NULL;
    }
    else if ((cond = strcmp(pW, pN -> word)) == 0){
        pN -> count++;
    }
    else if (cond < 0){
        pN -> left = addTree(pN -> left, pW);
    }
    else{
        pN -> right = addTree(pN -> right, pW);
    }

    return pN;
}


/**
 * Prints out tree in "Inorder"
 * Part of code is from "Uebungen_3.pdf"
 * @author Unknown
 * @param  pN       tnode-Pointer
 */
void treePrintInOrder(struct tnode* pN){
    if (pN != NULL){
        treePrintInOrder(pN -> left);
        printf("%4d %s\n", pN -> count, pN -> word);
        treePrintInOrder(pN -> right);
    }
}


/**
 * Prints out tree in "Postorder"
 * Part of code is from "Uebungen_3.pdf"
 * @author Unknown
 * @param  pN       tnode-Pointer
 */
void treePrintPostOrder(struct tnode* pN){
    if (pN != NULL){
        treePrintPostOrder(pN -> right);
        printf("%4d %s\n", pN -> count, pN -> word);
        treePrintPostOrder(pN -> left);
    }
}