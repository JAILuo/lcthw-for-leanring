#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top;
    int *data;
    int maxSize;
} Stack;

// 初始化栈
void initStack(Stack *stack, int maxSize)
{
    stack->top = -1;
    stack->maxSize = maxSize;
    stack->data = (int *)malloc(maxSize * sizeof(int));
    if (stack->data == NULL) {
        printf("Failed to initialize stack: out of memory\n");
        exit(1);
    }
}

// 判断栈是否为空
int isEmpty(Stack *stack) 
{
    return stack->top == -1;
}

// 判断栈是否已满
int isFull(Stack *stack)
{
    return stack->top == stack->maxSize - 1;
}

// 压入元素
void push(Stack *stack, int value)
{
    if (isFull(stack))
    {
        printf("Stack overflow\n");
        return;
    }
    stack->data[++stack->top] = value;
}

// 弹出元素
int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->data[stack->top--];
}

// 销毁栈
void destroyStack(Stack *stack)
{
    free(stack->data);
    stack->data = NULL;
    stack->maxSize = 0;
    stack->top = -1;
    stack = NULL;
}

int main() {
    Stack stack;
    initStack(&stack, 100);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Popped %d from stack\n", pop(&stack));
    printf("Popped %d from stack\n", pop(&stack));
    printf("Popped %d from stack\n", pop(&stack));
    printf("Popped %d from stack\n", pop(&stack));

    destroyStack(&stack);

    return 0;
}
