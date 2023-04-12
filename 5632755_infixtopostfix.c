#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct
{
    element data[MAX_STACK_SIZE];
    int top;
}StackType;

init_stack(StackType* s);
int is_empty(StackType* s);
void push(StackType* s, element item);
element pop(StackType* s);
element peek(StackType* s);

int prec(char op);
int eval(char exp[]);
char* infix_to_postfix(char exp[]);

int main()
{
    char* topostfix = "";
    int evalres;
    char* a = (char*)malloc(sizeof(char*));
    printf("Enter an infix expression : ");
    gets(a);
   topostfix = infix_to_postfix(a);
    printf("Postfix expression : %s\n", topostfix);
   evalres = eval(topostfix);
   printf("Result: %d\n", evalres);
   // system("pause");
    return 0;
}

init_stack(StackType* s)
{
    s->top = -1;
}
int is_empty(StackType* s)
{
    return (s->top == -1);
}

void push(StackType* s, element item)
{
    s->data[++(s->top)] = item;
}
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else return s->data[(s->top)--];
}

element peek(StackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else return s->data[s->top];
}

int prec(char op)//연산자의 우선순위 반환
{
    switch (op) {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

element* infix_to_postfix(char exp[])
{
    element* s_result = (element*)malloc(MAX_STACK_SIZE);
    int i, s_resultdx = 0;
    char ch, top_op;
    int len = strlen(exp);
    StackType s;

    init_stack(&s); //스택초기화

    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        switch (ch)
        {
        case '+': case'-': case '*': case '/': //연산자
            while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
            {
                s_result[s_resultdx++] = peek(&s);
                pop(&s);
            }
            push(&s, ch);
            break;

        case '(': //왼쪽 괄호
            push(&s, ch);
            break;

        case ')': //오른쪽괄호

            top_op = pop(&s); //왼쪽 괄호를 만날 때 까지 출력
            while (top_op != '(')
            {
                s_result[s_resultdx++] = top_op;
                top_op = pop(&s);
            }
            break;

        default: //피연산자
            /*if (ch != ('1' && '2' && '3' && '4' && '5' && '6' && '7' && '8' && '9' && '0'))
            {
                printf("Invalid character");
            }*/

            s_result[s_resultdx++] = ch;
            break;
        }
    }
    while (!is_empty(&s))
    {
        top_op = peek(&s);
        pop(&s);
        s_result[s_resultdx++] = top_op;
    }
    s_result[s_resultdx] = '\0';
    return s_result;
}

int eval(char exp[])
{
    int op1, op2, i = 0; //피연산자
    int len = strlen(exp); //라이브러리 함수, 길이측정
    char ch;
    StackType s; //구조체스택
    init_stack(&s);
    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        if (((ch - 'A') >= 0) && ((ch - 'A') <= 57)) //아스키코드값 65~122인 문자가 입력되면 invalid charater 출력
        {
            printf("Invalid character");
            exit(1);
        }
        else if (ch != '+' && ch != '-' && ch != '*' && ch != '/')//입력이 피연산자라면
        {
            push(&s, ch - '0'); //문자 바로 집어넣으면됨 (나중에 빼서 숫자로 바꿔서 계산)
        }


        //value = ch - '0' <-잘못됨 (element에 char값 집어넣기로 했는데 int값임
        else //연산자일경우
        {
            if (is_empty(&s))
            {
                fprintf(stderr, "피연산자오류");
            }
            //pop하기 전에 스택 비어있는지 확인하는 함수 필요
            else
            {
                op2 = pop(&s);
                op1 = pop(&s);

                switch (ch) {
                case '+': push(&s, op2 + op1); //pop한것 더해서 집어넣기
                    break; //switch 벗어나기
                case '-': push(&s, (op2 - op1));
                    break;
                case '*': push(&s, (op2 * op1));
                    break;
                case '/': push(&s, (op2 / op1));
                    break;

                }

            }
        }
    }
    return pop(&s);
}
