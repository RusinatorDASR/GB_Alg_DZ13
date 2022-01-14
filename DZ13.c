#include <stdio.h>
#include <stdlib.h>
#define T char
#define true 1 == 1
#define false 1 != 1
#define sn 6
typedef int boolean;

typedef struct Node {
    int dat;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} Stack;

void init(Stack* stack) {
    stack->head = NULL;
    stack->size = 0;
}

boolean push(Stack* stack, int value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("Stack overflow\n");
        return false;
    }
    tmp->dat = value;
    tmp->next = stack->head;

    stack->head = tmp;
    stack->size++;
    return true;
}

int pop(Stack* stack) {
    if(stack->size == 0) {
        printf("Stack is empty \n");
        return -1;
    }
    Node* tmp = stack->head;
    int data = stack->head->dat;
    stack->head = stack->head->next;
    free(tmp);
    stack->size--;
    return data;
}

void printOneLinkIntNode(Node *n) {
    if (n == NULL) {
        printf("[]");
        return;
    }
    printf("[%d]", n->dat);
}

void printOneLinkIntStack(Stack *stack) {
    Node *current = stack->head;
    if (current == NULL) {
        printOneLinkIntNode(current);
    } else {
        do {
            printOneLinkIntNode(current);
            current = current->next;
        } while (current != NULL);
    }
    printf(" Size: %d \n", stack->size);
}

int matrix[sn][sn] = {
    {0, 0, 0, 1, 1, 1},
    {0, 1, 1, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0},
};

boolean searchNumStack(Stack* stack, int num) {
    Node* node = stack->head;
    while (node != NULL) {
        if (node->dat == num) return true;
        node = node->next;
    }
    return false;
}

void depthTravers(int st, Stack* stack) {
    int r;
    printf("%d ", st);
    push(stack, st);
    for(r = 0; r < sn; ++r) {
        if(matrix[st][r] == 1 && !searchNumStack(stack, r)) {
            depthTravers(r, stack);
        }
    }
}

//===================== Задание 1 =======================//
boolean vArr[sn] = {0};

int getUnV(Stack* stack, int v) {
    for (int i = 0; i < sn; ++i) {
        if(matrix[v][i] == 1 && !vArr[i]) {
            return i;
        }
    }
    return -1;
}

void depthTravers2(int st, Stack* stack) {

    push(stack, st);
    printf("%d ", st);
    vArr[st] = true;
    while(stack->size) {
        int v = (getUnV(stack, stack->head->dat));
        if (v == -1) {
            pop(stack);
        } else {
            vArr[v] = true;
            printf("%d ", v);
            push(stack, v);
        }
    }
    for (int i = 0; i < sn; ++i) {
        vArr[i] = 0;
    }
}

int someArr[sn];
void resetArr() {
    for (int i = 0; i < sn; ++i) {
        someArr[i] = 0;
    }
}
void printIntArray(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d", array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");
}


//===================== Задание 2 =======================//

int matrixLinks[sn] = {0};
int traversLinks[sn] = {0};

void matrixCount() {
    for (int i = 0; i < sn; ++i) {
        for (int j = 0; j < sn; ++j) {
            if (matrix[j][i] == 1) {
                if (i != j) matrixLinks[i]++;
            }
        }
    }
}
void depthTraversCount(int st, Stack* stack) {
    int r;
    push(stack, st);
    for(r = 0; r < sn; ++r) {
        if(matrix[st][r] == 1) {
            if (st != r) traversLinks[r]++;
            if(!searchNumStack(stack, r)) {
                depthTraversCount(r, stack);
            }
        }
    }
}

int main()
{
    //=============== Задание 1 ============//
    Stack* st = (Stack*) malloc(sizeof(Stack));
    init(st);
    depthTravers2(0, st);
    printf("\n");
    //=============== Задание 2 ============//
    Stack* st2 = (Stack*) malloc(sizeof(Stack));
    init(st2);
    matrixCount();
    printIntArray(matrixLinks, sn);
    printf("\n");

    depthTraversCount(0, st2);
    printIntArray(traversLinks, sn);
    printf("\n");
    return 0;
}
