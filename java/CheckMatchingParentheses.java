import java.util.Stack;

class CheckMatchingParentheses {

    public static void main(String[] args) {
        System.out.println(isValidParentheses(args[0]));
    }

    private static boolean isValidParentheses(String s) {
        Stack<Character> stack = new Stack<>();

        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (c == '(' || c == '{' || c == '[') {
                stack.push(c);
            } else {
                if (stack.empty()) return false;
                Character top = stack.peek();

                if (!areMatchingParentheses(top, c)) return false;

                stack.pop();
            }
        }
        return stack.empty();
    }

    private static boolean areMatchingParentheses(Character a, Character b) {
        return (a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']');
    }

}