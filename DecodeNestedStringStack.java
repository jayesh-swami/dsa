import java.util.Stack;

public class DecodeNestedStringStack {
    public String decodeString(String s) {

        Stack<String> characterStack = new Stack<>();
        Stack<Integer> countStack = new Stack<>();

        int i = 0;

        while (i < s.length()) {

            if (Character.isDigit(s.charAt(i))) {

                int count = 0;

                while (Character.isDigit(s.charAt(i))) {
                    count = 10 * count + (s.charAt(i) - '0');
                    i++;
                }
                countStack.push(count);

            } else if (s.charAt(i) != ']') {

                characterStack.push(s.substring(i, i + 1));
                i++;

            } else {

                StringBuilder tempString = new StringBuilder();

                StringBuilder newString = new StringBuilder();

                while (!characterStack.peek().equals("["))
                    tempString.append(characterStack.pop());

                characterStack.pop();

                for (int j = 0; j < countStack.peek(); j++) newString.append(tempString);

                countStack.pop();

                characterStack.push(newString.toString());

                i++;
            }
        }
        StringBuilder res = new StringBuilder();

        while (!characterStack.isEmpty()) res.append(characterStack.pop());

        return res.reverse().toString();
    }
}
