import java.util.Stack;

public class MinStack {

    Stack<Integer> stack;
    Stack<Integer> minStack;

    public MinStack() {
        stack = new Stack<>();
        minStack = new Stack<>();
    }

    public void push(int val) {
        if(stack.empty()){
            minStack.push(val);
        } else {
            if(minStack.peek() >= val) {
                minStack.push(val);
            } else {
                minStack.push(minStack.peek());
            }
        }
        stack.push(val);
    }

    public void pop() {
        stack.pop();
        minStack.pop();
    }

    public int top() {
        return stack.peek();
    }

    public int getMin() {
        return minStack.peek();
    }
}