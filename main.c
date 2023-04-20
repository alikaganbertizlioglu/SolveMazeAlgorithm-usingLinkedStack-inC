#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LINKED_STACK_NODE_s *LINKED_STACK_NODE;
typedef struct LINKED_STACK_NODE_s {
    LINKED_STACK_NODE next;
    void *data;
} LINKED_STACK_NODE_t[1];


typedef struct LINKED_STACK_s {
    LINKED_STACK_NODE head;
} LINKED_STACK_t[1], *LINKED_STACK;


LINKED_STACK linked_stack_init() {
    LINKED_STACK stack = NULL;
    stack = (LINKED_STACK) malloc(sizeof(LINKED_STACK_t));
    if (stack != NULL) {
        stack->head = NULL;
    }
    return stack;
}


void linked_stack_free(LINKED_STACK stack) {
    free(stack);
}


int linked_stack_push(LINKED_STACK stack, void *data) {
    LINKED_STACK_NODE node = (LINKED_STACK_NODE) malloc(sizeof(LINKED_STACK_NODE_t));
    if (node != NULL) {
        node->data = data;
        node->next = stack->head;
        stack->head = node;
        return 1;
    } else {
        return 0;
    }
}


void *linked_stack_pop(LINKED_STACK stack) {
    LINKED_STACK_NODE node;
    void *res = NULL;

    if (stack->head != NULL) {
        node = stack->head;
        res = node->data;
        stack->head = node->next;
        free(node);
    }

    return res;
}


void *linked_stack_top(LINKED_STACK stack) {
    void *res = NULL;

    if (stack->head != NULL) {
        res = stack->head->data;
    }

    return res;
}


int linked_stack_is_empty(LINKED_STACK stack) {
    return (stack->head == NULL);
}

typedef struct {
    int R;
    int C;
} POS_t[1], *POS;


void solve_maze() {

    int M[8][8] = {
            /* R\C   0  1  2  3  4  5  6  7 */
            /* 0 */ {0, 0, 0, 1, 0, 0, 0, 0},
            /* 1 */
                    {0, 1, 1, 1, 0, 0, 1, 0},
            /* 2 */
                    {0, 1, 0, 1, 0, 0, 1, 0},
            /* 3 */
                    {0, 1, 0, 1, 1, 1, 1, 0},
            /* 4 */
                    {0, 1, 0, 0, 0, 0, 1, 1},
            /* 5 */
                    {0, 1, 1, 0, 1, 1, 1, 0},
            /* 6 */
                    {0, 0, 0, 0, 1, 0, 0, 0},
            /* 7 */
                    {0, 0, 0, 0, 1, 0, 0, 0},
    };

    int I, J, R = 0, C = 3;
    LINKED_STACK stack;
    POS pos = (POS) malloc(sizeof(POS));
    stack = linked_stack_init();
    pos->R=0;
    pos->C=3;
    do {
        M[R][C] = 2;
        linked_stack_push(stack, pos);
        for (C = 0; C < 7; ++C) {
            for (R = 0; R < 7; ++R) {
                if (M[R - 1][C] == 1) {//NORTH
                    printf("North\n");
                    printf("%d %d\n",pos->R,pos->C);
                    linked_stack_push(stack, pos);
                    M[R - 1][C] = M[R][C] = 2;
                    pos->R--;
                } else if (M[R][C + 1] == 1) {//EAST
                    printf("East\n");
                    printf("%d %d\n",pos->R,pos->C);

                    linked_stack_push(stack, pos);
                    M[R][C + 1] = M[R][C] = 2;
                    pos->C++;
                } else if (M[R][C - 1] == 1) {//SOUTH
                    printf("South\n");
                    printf("%d %d\n",pos->R,pos->C);

                    linked_stack_push(stack, pos);
                    M[R][C - 1] = M[R][C] = 2;
                    pos->C--;
                } else if (M[R + 1][C] == 1) {//WEST
                    printf("West\n");
                    printf("%d %d\n",pos->R,pos->C);

                    linked_stack_push(stack, pos);
                    M[R + 1][C] = M[R][C] = 2;
                    pos->R++;
                } else if (M[R][C] == 0) {
                    printf("Obstackle !\n");
                    printf("%d %d\n",pos->R,pos->C);
                    linked_stack_pop(stack);
                    M[R][C] = -1;
                    linked_stack_top(stack);
                }
            }
        }
    } while (R != 7 && C != 7 && R != 0 && C != 0);
    linked_stack_free(stack);
}

int main() {
    solve_maze();
    return 0;
}
