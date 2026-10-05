import java.util.Objects;
import java.util.Stack;


/**
 * Just take care of division v1/v2 or v2/v1
 */
public class ReversePolishNotation {

    public int evalRPN(String[] tokens) {
        Stack<Integer> stack = new Stack<>();

        for(String token: tokens) {
            if(!isOperation(token)) {
                stack.push(Integer.parseInt(token));
            } else {
                Integer v1 = stack.pop();
                Integer v2 = stack.pop();
                stack.push(evaluateExpression(v2, v1, token));
            }
        }
        return stack.peek();
    }

    private static int evaluateExpression(
            Integer val1,
            Integer val2,
            String operation) {
        switch(operation) {
            case "+": return val1 + val2;
            case "-": return val1 - val2;
            case "/": return val1 / val2;
            case "*": return val1 * val2;
        }
        return -1;
    }

    private static boolean isOperation(String s) {
        return Objects.equals(s, "+") || Objects.equals(s, "-") || Objects.equals(s, "*") || Objects.equals(s, "/");
    }

}