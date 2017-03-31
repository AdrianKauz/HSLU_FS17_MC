/**
 * HSLU FS2017 - Mikrocontroller - TA.MC
 * Exercise 3.1
 * Get name and forename via console from the user and save the values
 * as a simple list.
 * Still full with bugs! Bleh!
 * @author Adrian Kauz
 * @version 0.5
 * @date 2017.03.28
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

char buf[BUFSIZE];
int bufp = 0;

// Prototypes
int getch(void);
void ungetch(int c);
int getWord(char *word, int lim);
struct tnode* talloc();
struct tnode* addTree(struct tnode* p, char* w);
void treePrintInOrder(struct tnode* p);
void treePrintPostOrder(struct tnode* p);


int main(int argc, char *argv[]) {
    system("cls");

    if(argc != 2){
        if(argc == 1){
            printf("Dateiname fehlt...\n");
        }
        else{
            printf("Zu viele Argumente...\n");
        }
    }
    else{
        struct tnode* root = NULL;
        char word[MAXWORD];

        printf("\"%s\" wird eingelesen...\n", argv[1]);

        if(freopen(argv[1], "r", stdin) == NULL){
            printf("...konnte \"%s\" nicht öffnen!", argv[1]);
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


int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c){
    if(bufp >= BUFSIZE){
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}


int getWord(char *word, int lim){
    int c;
    char *w = word;

    while(isspace(c = getch())){

    };

    if (c != EOF){
        *w++ = c;
    }

    if (!isalpha(c)){
        *w = '\0';
        return(c);
    }

    for( ; --lim > 0; w++){
        if(!isalnum(*w = getch())){
            ungetch(*w);
            break;
        }
    }

    *w ='\0';

    return word[0];
}


struct tnode* talloc(){
    return malloc(sizeof(struct tnode));
}


struct tnode* addTree(struct tnode* p, char* w){
    int cond;

    if(p == NULL){
        p = talloc();
        p -> word = strdup(w);
        p -> count = 1;
        p -> left = NULL;
        p -> right = NULL;
    }
    else if ((cond = strcmp(w, p -> word)) == 0){
        p -> count++;
    }
    else if (cond < 0){
        p -> left = addTree(p -> left, w);
    }
    else{
        p -> right = addTree(p -> right, w);
    }

    return p;
}


void treePrintInOrder(struct tnode* p){
    if (p != NULL){
        treePrintInOrder(p -> left);
        printf("%4d %s\n", p -> count, p -> word);
        treePrintInOrder(p -> right);
    }
}


void treePrintPostOrder(struct tnode* p){
    if (p != NULL){
        treePrintPostOrder(p -> right);
        printf("%4d %s\n", p -> count, p -> word);
        treePrintPostOrder(p -> left);
    }
}
