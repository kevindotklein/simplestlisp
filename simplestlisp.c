#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define EXPR_LIMIT 4096
#define SL_ADD '+'
#define SL_SUB '-'
#define SL_MUL '*'
#define SL_DIV '/'
#define SL_QUIT 'q'
#define SL_HELP 'h'

char *simplestlisp_read();
int simplestlisp_eval(char *expr);
float simplestlisp_add(char *expr);
float simplestlisp_mult(char *expr);
float simplestlisp_div(char *expr);
float simplestlisp_sub(char *expr);
void simplestlisp_print_help();

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

        while(*expr != ' '){
            if(*expr == ')') break;
            expr++;
            continue;
        }
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
        
        while(*expr != ' '){
            if(*expr == ')') break;
            expr++;
            continue;
        }
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

        while(*expr != ' '){
            if(*expr == ')'){
                return subtraction;
            }
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
        if(*expr == ' '){
            expr++;
            continue;
        }

        while(*expr != ' '){
            if(*expr == ')'){
                return division;
            }
            expr++;
            continue;
        }

        sscanf(expr++, "%f", &a);
        division /= a;

    }

    return division;
}

void simplestlisp_print_help(){
    fprintf(stdout, "the simplestlisp is a simple interpreter\n");
    fprintf(stdout, "type `:q` to quit\n");
    fprintf(stdout, "u can evaluate few math expressions, such as + - * /\n");
    fprintf(stdout, "try to follow this template for the operations above `(<operand> <number_1> <number_2> <number_n>)`\n");
}

int simplestlisp_eval(char *expr){

    float result = 0;

    if(*expr == ':'){
        expr++;
        char *op = expr++;

        switch (*op)
        {
        case SL_QUIT:
            exit(0);
            break;
        case SL_HELP:
            simplestlisp_print_help();
            return 0;
            break;

        default:
            break;
        }
    }else{
        if(*(expr++) != '('){
            fprintf(stderr, "try `:h` for help\n");
            return 0;
        }

        char *op = expr++;


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
    }
    return result;
}
