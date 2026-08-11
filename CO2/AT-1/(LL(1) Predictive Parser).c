#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char input[100];
int pos = 0;

void S();
void SP();
void T();
void TP();
void F();

void skipSpace()
{
    while(input[pos]==' ')
        pos++;
}

void match(char *token)
{
    skipSpace();

    if(strncmp(&input[pos], token, strlen(token))==0)
    {
        printf("%-20s %-20s Match %s\n"," ",&input[pos],token);
        pos += strlen(token);
    }
    else
    {
        printf("\nString Rejected\n");
        exit(0);
    }
}

void S()
{
    printf("%-20s %-20s S -> T S'\n","S",&input[pos]);
    T();
    SP();
}

void SP()
{
    skipSpace();

    if(input[pos]=='+')
    {
        printf("%-20s %-20s S' -> + T S'\n","S'",&input[pos]);

        match("+");

        T();

        SP();
    }
    else
    {
        printf("%-20s %-20s S' -> ε\n","S'",&input[pos]);
    }
}

void T()
{
    printf("%-20s %-20s T -> F T'\n","T",&input[pos]);

    F();

    TP();
}

void TP()
{
    skipSpace();

    if(input[pos]=='*')
    {
        printf("%-20s %-20s T' -> * F T'\n","T'",&input[pos]);

        match("*");

        F();

        TP();
    }
    else
    {
        printf("%-20s %-20s T' -> ε\n","T'",&input[pos]);
    }
}

void F()
{
    skipSpace();

    if(strncmp(&input[pos],"id",2)==0)
    {
        printf("%-20s %-20s F -> id\n","F",&input[pos]);

        match("id");
    }

    else if(input[pos]=='(')
    {
        printf("%-20s %-20s F -> (S)\n","F",&input[pos]);

        match("(");

        S();

        match(")");
    }

    else
    {
        printf("\nString Rejected\n");
        exit(0);
    }
}

int main()
{
    printf("LL(1) Predictive Parser\n");
    printf("------------------------------\n");

    printf("Enter Input : ");

    gets(input);

    printf("\nStack(Symbol)        Remaining Input      Action\n");
    printf("----------------------------------------------------------\n");

    S();

    skipSpace();

    if(input[pos]=='\0')
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}