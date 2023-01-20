#include <stdio.h>
#include <stdlib.h>

#define EXPR_LIMIT 256
#define SL_ADD '+'
#define SL_SUB '-'
#define SL_MUL '*'
#define SL_DIV '/'

char *simplestlisp_read();
int simplestlisp_eval(char *expr);
float simplestlisp_add(char *expr);
float simplestlisp_mult(char *expr);
float simplestlisp_div(char *expr);
float simplestlisp_sub(char *expr);

int main(int argc, char const **argv){
    (void) argc;
    (void) argv;
    while(1){
        fprintf(stdout, "REPL> ");
        fprintf(stdout, "%d\n", simplestlisp_eval(simplestlisp_read()));
    }
    return 0;
}

char *simplestlisp_read(){
    char *expr = malloc(EXPR_LIMIT);
    fgets(expr, EXPR_LIMIT, stdin);
    return expr;
}

float simplestlisp_add(char *expr){
    float sum = 0;

    while(*expr != ')'){
        if(*expr == ' '){
            expr++;
            continue;
        }

        float a = 0;
        sscanf(expr++, "%f", &a);
        sum += a;
    }

    return sum;
}

float simplestlisp_mult(char *expr){
    float product = 1;

    while(*expr != ')'){
        if(*expr == ' '){
            expr++;
            continue;
        }

        float a = 0;
        sscanf(expr++, "%f", &a);
        product *= a;
        
    }

    return product;
}

float simplestlisp_sub(char *expr){
    float a;
    float subtraction = 0;

    while(*expr != ')'){
        if(*expr == ' '){
            expr++;
            continue;
        }

        sscanf(expr++, "%f", &a);
        subtraction = a;
        break;
    }

    while(*expr != ')'){
        if(*expr == ' '){
            expr++;
            continue;
        }

        sscanf(expr++, "%f", &a);
        subtraction -= a;
    }

    return subtraction;
}

float simplestlisp_div(char *expr){
    float a;
    float division = 0;

    while(*expr != ')'){
        if(*expr == ' '){
            expr++;
            continue;
        }

        sscanf(expr++, "%f", &a);
        division = a;
        break;
    }

    while(*expr != ')'){
        if(*expr == 0){
            fprintf(stdout, "div by 0 :(\n");
            exit(0);
        }
        if(*expr == ' '){
            expr++;
            continue;
        }

        sscanf(expr++, "%f", &a);
        division /= a;
    }

    return division;
}

int simplestlisp_eval(char *expr){
    if(*(expr++) != '('){
        fprintf(stderr, "must begin with parentheses\n");
        return 1;
    }
    char *op = expr++;

    float result = 0;

    switch (*op){
    case SL_ADD:
        result = simplestlisp_add(expr);
        break;
    case SL_MUL:
        result = simplestlisp_mult(expr);
        break;
    case SL_DIV:
        result = simplestlisp_div(expr);
        break;
    case SL_SUB:
        result = simplestlisp_sub(expr);
        break;
    
    default:
        result = 0;
        break;
    }

    return result;
}
