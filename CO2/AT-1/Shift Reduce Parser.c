#include <stdio.h>
#include <string.h>

char stack[100];
int top=-1;

void push(char c){
    stack[++top]=c;
    stack[top+1]='\0';
}

void reduce(){

    int len=strlen(stack);

    // id -> E
    if(len>=2 &&
       stack[len-2]=='i' &&
       stack[len-1]=='d'){
        top-=1;
        stack[top]='E';
        stack[top+1]='\0';
        printf("Reduce: id -> E\n");
        return;
    }

    // E*E -> E
    len=strlen(stack);
    if(len>=3 &&
       stack[len-3]=='E' &&
       stack[len-2]=='*' &&
       stack[len-1]=='E'){
        top-=2;
        stack[top]='E';
        stack[top+1]='\0';
        printf("Reduce: E*E -> E\n");
        return;
    }

    // E+E -> E
    len=strlen(stack);
    if(len>=3 &&
       stack[len-3]=='E' &&
       stack[len-2]=='+' &&
       stack[len-1]=='E'){
        top-=2;
        stack[top]='E';
        stack[top+1]='\0';
        printf("Reduce: E+E -> E\n");
        return;
    }
}

int main(){

    char input[]="id+id*id$";

    int i=0;

    printf("Stack\tInput\tAction\n");

    while(input[i]!='$'){

        if(input[i]=='i'){
            push('i');
            push('d');
            i+=2;
            printf("%s\t%s\tShift id\n",stack,&input[i]);
            reduce();
        }

        else{
            push(input[i]);
            printf("%s\t%s\tShift %c\n",stack,&input[i+1],input[i]);
            i++;
        }

        reduce();

        // precedence: reduce multiplication before addition
        while(strstr(stack,"E*E"))
            reduce();

        while(strstr(stack,"E+E") && !strstr(stack,"E*E"))
            reduce();
    }

    if(strcmp(stack,"E")==0)
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}