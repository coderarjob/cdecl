#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <acl_stack.h>

enum token_type {UNKNOWN, IDENTIFIER, QUALIFIER, TYPE, OPERATOR, SEPARATOR};
struct token
{
    enum token_type type;
    char string[100];
};


int gettoken(char **inp, struct token *t);
void prndesc(struct token *t);

int main(int argc, char *argv[])
{
    if (argc != 2) return 1;
    char *decl = argv[1];

    struct acl_stack *stack;
    stack = acl_create_stack(sizeof(struct token), 100);
 
    int state = 0;
    struct token t;
    while(state != 6 && state != 7) {
        switch(state) {
            case 0:
                if (!gettoken(&decl,&t)) state = 6; 
                if (t.type != IDENTIFIER) acl_stack_push(stack,&t);
                else { prndesc(&t); state = 1; }
                break;
            case 1:
                if      (!gettoken(&decl,&t)) state = 5; 
                else if (!strcmp(t.string,"(")) state = 2;
                else if (!strcmp(t.string,"[")) state = 3;
                else if (!strcmp(t.string,")")) state = 4;
                else    state = 6;

                if (state == 2 || state == 3) prndesc(&t);
                break;
            case 2:
                if (!gettoken(&decl,&t)) state = 6; 
                if (!strcmp(t.string,")")) state = 1;
                break;
            case 3:
                if      (!gettoken(&decl,&t)) state = 6; 
                else if (!strcmp(t.string,"]")) state = 1;
                //else if (!isdigit(t.string)) state = 6;
                break;
            case 4:
                if      (acl_stack_pop(stack,&t)) state = 6;
                else if (!strcmp(t.string,"(")) state = 1;
                else if (t.type != TYPE && 
                         t.type != QUALIFIER && 
                         strcmp(t.string,"*"))  state = 6;
                else prndesc(&t);
                break;
            case 5:
                if      (acl_stack_pop(stack,&t)) state = 7;
                else if (t.type != TYPE && 
                         t.type != QUALIFIER && 
                         strcmp(t.string,"*"))  state = 6;
                else prndesc(&t);
                break;
        }
    }

    if (state == 6) printf("\nSyntax error");
    printf("\n");
    return 0;
}

void prndesc(struct token *t)
{
    if      (!strcmp(t->string,"(")) printf(" a function returning");
    else if (!strcmp(t->string,"[")) printf(" an array of");
    else if (!strcmp(t->string,"*")) printf(" pointer to");
    else if (t->type == IDENTIFIER)  printf("%s is",t->string);
    else if (t->type == TYPE)        printf(" %s",t->string);
    else if (t->type == QUALIFIER)   printf(" %s",t->string);
    fflush(stdout);
}

int gettoken(char **inp, struct token *t)
{
    char *input = *inp;

    // Skip white spaces
    while(isspace(*input))
        input++;
   
    // Zero everything in 't'
    memset(t,0,sizeof(struct token));

    // Single character tokens
    char c;
    switch ((c = *input++)) {
        case '\0':
            return 0;
        case '*':
            t->type = OPERATOR;
            t->string[0] = c;
            goto found;
        case '(': case ')': case '[': case ']': case ';':
            t->type = SEPARATOR;
            t->string[0] = c;
            goto found;
        default:
            // Read too far.Not a single char token.Back once.
            input--;        
            break;
    };

    // May be identifier
    while (isalnum(*input)){
        strncat(t->string,input,1);
        input++;
    }

    if      (!strcmp(t->string,"int"))      t->type = TYPE;
    else if (!strcmp(t->string,"char"))     t->type = TYPE;
    else if (!strcmp(t->string,"short"))    t->type = TYPE;
    else if (!strcmp(t->string,"long"))     t->type = TYPE;
    else if (!strcmp(t->string,"void"))     t->type = TYPE;
    else if (!strcmp(t->string,"const"))    t->type = QUALIFIER;
    else if (!strcmp(t->string,"volatile")) t->type = QUALIFIER;
    else t->type = IDENTIFIER;

found:
    *inp = input;
    return 1;
}
