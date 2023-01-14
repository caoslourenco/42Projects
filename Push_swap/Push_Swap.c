#include <stdio.h>
#include <stdlib.h>

#define BASE 10
#define MAX_DIGITS 10

// Estrutura para representar um nó na pilha
struct Node {
    int value;
    struct Node *next;
};

// Estrutura para representar a pilha
struct Stack {
    struct Node *top;
};

// Inicializa uma nova pilha
void init(struct Stack *stack) {
    stack->top = NULL;
}

// Empilha um valor na pilha
void push(struct Stack *stack, int value) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
}

// Desempilha o valor do topo da pilha
int pop(struct Stack *stack) {
    if (stack->top == NULL) {
        printf("Error: stack underflow\n");
        exit(1);
    }
    int value = stack->top->value;
    struct Node *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

// Verifica se a pilha está vazia
int is_empty(struct Stack *stack) {
    return (stack->top == NULL);
}

// Ordena a pilha usando o algoritmo de ordenação radix
void radix_sort(struct Stack *stack) {
    struct Stack buckets[BASE];
    int i, digit, divisor = 1;
    for (i = 0; i < BASE; i++) {
        init(&buckets[i]);
    }
    for (i = 0; i < MAX_DIGITS; i++) {
        while (!is_empty(stack)) {
            digit = (pop(stack) / divisor) % BASE;
            push(&buckets[digit], digit);
        }
        divisor *= BASE;
        for (digit = 0; digit < BASE; digit++) {
            while (!is_empty(&buckets[digit])) {
                push(stack, pop(&buckets[digit]));
            }
        }
    }
}

// Exemplo de uso
int main() {
    struct Stack stack;
    init(&stack);
    push(&stack, 1234);
    push(&stack, 5678);
    push(&stack, 9876);
    push(&stack, 5432);
    push(&stack, 7654);
    printf("Pilha original: ");
    while (!is_empty(&stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
    init(&stack);
    push(&stack, 1234);
    push(&stack, 5678);
    push(&stack, 9876);
    push(&stack, 5432);
    push(&stack, 7654);
    radix_sort(&stack);
    printf("Pilha ordenada: ");
    while (!is_empty(&stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");
    return 0;
}

Este código cria uma pilha e empilha alguns valores, em seguida, chama a função radix_sort 
para ordenar a pilha e imprime o resultado ordenado. Este exemplo usa base 10 e assume que 
todos os valores na pilha têm no máximo MAX_DIGITS dígitos.

Aqui, você pode ver que a função radix_sort utiliza um array de pilhas para armazenar as filas
 de trabalho, uma para cada dígito. O algoritmo então classifica cada elemento na pilha de entrada
  baseado no dígito do número na posição específica (por exemplo, o dígito das unidades para base 10) 
  e concatena as filas de trabalho de volta na pilha de entrada, começando com a fila de trabalho
   correspondente ao dígito menos significativo. O processo é repetido, classificando cada elemento 
   na pilha de entrada baseado no próximo dígito mais significativo (por exemplo, o dígito das dezenas
    para base 10) até que todos os dígitos tenham sido considerados.
