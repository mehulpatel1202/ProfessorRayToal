public class StackException extends RuntimeException {
    public StackException(String message) {
        super(message);
    }
}

public class Stack {
    private String[] stack;
    private int top;
    private int capacity;

    public Stack() {
        stack = new String[10];
        top = -1;
        capacity = 10;
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public boolean isFull() {
        return top == capacity - 1;
    }

    public void push(String item) {
        if (isFull()) {
            throw new StackException("Error: Stack is full, cannot push item");
        }

        top++;
        stack[top] = item;
    }

    public String pop() {
        if (isEmpty()) {
            throw new StackException("Error: Stack is empty, cannot pop item");
        }

        String poppedItem = stack[top];
        top--;
        return poppedItem;
    }

    public static void main(String[] args) {
        Stack stack = new Stack();

        try {
            stack.push("First item");
            stack.push("Second item");

            System.out.println("Popped item: " + stack.pop());
            System.out.println("Popped item: " + stack.pop());
            System.out.println("Popped item: " + stack.pop());  // This will throw an exception
        } catch (StackException e) {
            System.err.println(e.getMessage());
        }
    }
}
