#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;

void match(char *token) {
    int len = strlen(token);

    while(input[pos]==' ')
        pos++;

    if(strncmp(&input[pos], token, len)==0){
        printf("Matched %s\n", token);
        pos += len;
    }
    else{
        printf("\nString Rejected\n");
        exit(0);
    }
}

void E();
void E1();
void T();
void T1();
void F();

void E(){
    printf("E -> T E'\n");
    T();
    E1();
}

void E1(){
    while(input[pos]==' ')
        pos++;

    if(input[pos]=='+'){
        printf("E' -> + T E'\n");
        match("+");
        T();
        E1();
    }
    else{
        printf("E' -> ε\n");
    }
}

void T(){
    printf("T -> F T'\n");
    F();
    T1();
}

void T1(){
    while(input[pos]==' ')
        pos++;

    if(input[pos]=='*'){
        printf("T' -> * F T'\n");
        match("*");
        F();
        T1();
    }
    else{
        printf("T' -> ε\n");
    }
}

void F(){
    while(input[pos]==' ')
        pos++;

    if(strncmp(&input[pos],"id",2)==0){
        printf("F -> id\n");
        match("id");
    }
    else if(input[pos]=='('){
        printf("F -> (E)\n");
        match("(");
        E();
        match(")");
    }
    else{
        printf("\nString Rejected\n");
        exit(0);
    }
}

int main(){

    printf("Enter input: ");
    gets(input);

    E();

    while(input[pos]==' ')
        pos++;

    if(input[pos]=='\0')
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}