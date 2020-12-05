//
// Created by tangz on 2020/9/5.
//

#ifndef PACKAG_STACKOFINT_H
#define PACKAG_STACKOFINT_H

#include <stdio.h>
#include <stdlib.h>

//深搜使用的栈

typedef struct Node {
    int x;//横坐标
    int y;//纵坐标
    char *direction;//下一步的方向
} Node;//输出的三元组

typedef struct Stack {
    Node *data;
    struct Stack *nextNode;
} Stack;//栈本体

//初始化栈
Stack *init(Stack *stack, Node *data) {
    stack = (Stack *) malloc(sizeof(Stack));
    stack->data = data;
    stack->nextNode = NULL;
    return stack;
}

//栈是否为空
int isEmpty(Stack *stack) {
    return (stack == NULL) ? 0 : 1;
}

//压入栈顶
Stack *push(Stack *head, Node *data, Stack **top) {

    if (!isEmpty(head)) {//如果栈中head为空
        head = init(head, data);
        *top = head;
        return head;
    }
    Stack *loop = head;
    Stack *push = (Stack *) malloc(sizeof(Stack));
    push->nextNode = NULL;
    while (loop->nextNode != NULL) {
        loop = loop->nextNode;
    }
    push->data = data;
    loop->nextNode = push;
    *top = push;
    return head;
}

//弹出栈顶
Stack *pop(Stack *head, Stack **top) {
    if (!isEmpty(head)) {
        return head;
    }
    if (head == *top) {
        head = NULL;
        *top = NULL;
        return head;
    }
    Stack *loop = head;
    Stack *p = NULL;
    while (loop->nextNode != NULL) {
        p = loop;
        loop = loop->nextNode;
    }
    *top = p;
    free(loop);
    p->nextNode = NULL;
    return head;
}

#endif //PACKAG_STACKOFINT_H
