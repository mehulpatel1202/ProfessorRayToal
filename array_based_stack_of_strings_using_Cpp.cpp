#include <iostream>
#include <memory>

constexpr int STACK_SIZE = 10;

class StackException : public std::exception {
private:
    std::string errorMessage;

public:
    StackException(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

class Stack {
private:
    std::unique_ptr<std::string[]> stack;
    int top;
    int capacity;

public:
    Stack() : stack(std::make_unique<std::string[]>(STACK_SIZE)), top(-1), capacity(STACK_SIZE) {}

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == capacity - 1;
    }

    void push(const std::string& item) {
        if (isFull()) {
            throw StackException("Error: Stack is full, cannot push item");
        }

        top++;
        stack[top] = item;
    }

    std::string pop() {
        if (isEmpty()) {
            throw StackException("Error: Stack is empty, cannot pop item");
        }

        std::string poppedItem = stack[top];
        top--;
        return poppedItem;
    }
};

int main() {
    Stack stack;

    try {
        stack.push("First item");
        stack.push("Second item");

        std::cout << "Popped item: " << stack.pop() << std::endl;
        std::cout << "Popped item: " << stack.pop() << std::endl;
        std::cout << "Popped item: " << stack.pop() << std::endl;  // This will throw an exception
    } catch (const StackException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
