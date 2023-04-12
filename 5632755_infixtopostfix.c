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
        fprintf(stderr, "���� ���� ����\n");
        return;
    }
    else return s->data[(s->top)--];
}

element peek(StackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return s->data[s->top];
}

int prec(char op)//�������� �켱���� ��ȯ
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

    init_stack(&s); //�����ʱ�ȭ

    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        switch (ch)
        {
        case '+': case'-': case '*': case '/': //������
            while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
            {
                s_result[s_resultdx++] = peek(&s);
                pop(&s);
            }
            push(&s, ch);
            break;

        case '(': //���� ��ȣ
            push(&s, ch);
            break;

        case ')': //�����ʰ�ȣ

            top_op = pop(&s); //���� ��ȣ�� ���� �� ���� ���
            while (top_op != '(')
            {
                s_result[s_resultdx++] = top_op;
                top_op = pop(&s);
            }
            break;

        default: //�ǿ�����
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
    int op1, op2, i = 0; //�ǿ�����
    int len = strlen(exp); //���̺귯�� �Լ�, ��������
    char ch;
    StackType s; //����ü����
    init_stack(&s);
    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        if (((ch - 'A') >= 0) && ((ch - 'A') <= 57)) //�ƽ�Ű�ڵ尪 65~122�� ���ڰ� �ԷµǸ� invalid charater ���
        {
            printf("Invalid character");
            exit(1);
        }
        else if (ch != '+' && ch != '-' && ch != '*' && ch != '/')//�Է��� �ǿ����ڶ��
        {
            push(&s, ch - '0'); //���� �ٷ� ���������� (���߿� ���� ���ڷ� �ٲ㼭 ���)
        }


        //value = ch - '0' <-�߸��� (element�� char�� ����ֱ�� �ߴµ� int����
        else //�������ϰ��
        {
            if (is_empty(&s))
            {
                fprintf(stderr, "�ǿ����ڿ���");
            }
            //pop�ϱ� ���� ���� ����ִ��� Ȯ���ϴ� �Լ� �ʿ�
            else
            {
                op2 = pop(&s);
                op1 = pop(&s);

                switch (ch) {
                case '+': push(&s, op2 + op1); //pop�Ѱ� ���ؼ� ����ֱ�
                    break; //switch �����
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
