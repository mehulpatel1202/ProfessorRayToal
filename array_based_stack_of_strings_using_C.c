#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 10

typedef struct {
    char** stack;
    int top;
    int capacity;
} Stack;

typedef enum {
    STACK_OK,
    STACK_FULL,
    STACK_EMPTY,
    STACK_ERROR
} StackError;

typedef struct {
    StackError error;
    char* message;
} StackResponse;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        perror("Error: Failed to allocate memory for stack");
        exit(EXIT_FAILURE);
    }

    stack->stack = (char**)malloc(STACK_SIZE * sizeof(char*));
    if (stack->stack == NULL) {
        perror("Error: Failed to allocate memory for stack data");
        free(stack);
        exit(EXIT_FAILURE);
    }

    stack->top = -1;
    stack->capacity = STACK_SIZE;
    return stack;
}

void destroyStack(Stack* stack) {
    if (stack != NULL) {
        if (stack->stack != NULL) {
            for (int i = 0; i <= stack->top; i++) {
                free(stack->stack[i]);
            }
            free(stack->stack);
        }
        free(stack);
    }
}

bool isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isStackFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

StackResponse* push(Stack* stack, const char* item) {
    StackResponse* response = (StackResponse*)malloc(sizeof(StackResponse));
    if (response == NULL) {
        perror("Error: Failed to allocate memory for response object");
        exit(EXIT_FAILURE);
    }

    if (isStackFull(stack)) {
        response->error = STACK_FULL;
        response->message = "Error: Stack is full, cannot push item";
        return response;
    }

    char* newItem = strdup(item);
    if (newItem == NULL) {
        response->error = STACK_ERROR;
        response->message = "Error: Failed to allocate memory for new item";
        free(response);
        exit(EXIT_FAILURE);
    }

    stack->top++;
    stack->stack[stack->top] = newItem;
    response->error = STACK_OK;
    response->message = "Success: Item pushed to stack";
    return response;
}

StackResponse* pop(Stack* stack) {
    StackResponse* response = (StackResponse*)malloc(sizeof(StackResponse));
    if (response == NULL) {
        perror("Error: Failed to allocate memory for response object");
        exit(EXIT_FAILURE);
    }

    if (isStackEmpty(stack)) {
        response->error = STACK_EMPTY;
        response->message = "Error: Stack is empty, cannot pop item";
        return response;
    }

    char* poppedItem = stack->stack[stack->top];
    stack->top--;
    response->error = STACK_OK;
    response->message = poppedItem;
    return response;
}

int main() {
    Stack* stack = createStack();

    // Pushing items
    StackResponse* response = push(stack, "First item");
    if (response->error != STACK_OK) {
        printf("%s\n", response->message);
    } else {
        printf("%s\n", response->message);
    }
    free(response);

    response = push(stack, "Second item");
    if (response->error != STACK_OK) {
        printf("%s
