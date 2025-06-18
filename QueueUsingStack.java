import java.util.Stack;

public class QueueUsingStack {
    private Stack<Integer> q;

    public QueueUsingStack() {
        q = new Stack<>();
    }

    public void push(int x) {
        Stack<Integer> tempStack = new Stack<>();

        while (!q.isEmpty()) tempStack.push(q.pop());

        q.push(x);

        while (!tempStack.isEmpty()) q.push(tempStack.pop());
    }

    public int pop() {
        return q.pop();
    }

    public int peek() {
        return q.peek();
    }

    public boolean empty() {
        return q.isEmpty();
    }
}
