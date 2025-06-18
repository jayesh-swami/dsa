import java.util.*;

public class ParanthesesCheck {
    public boolean isValid(String s) {
        Map<Character, Character> closingBraceToOpeningMap = new HashMap<>();
        Set<Character> openingBraces = new HashSet<>();


        openingBraces.add('(');
        openingBraces.add('{');
        openingBraces.add('[');

        closingBraceToOpeningMap.put(')', '(');
        closingBraceToOpeningMap.put('}', '{');
        closingBraceToOpeningMap.put(']', '[');

        Stack<Character> paranthesesStack = new Stack<>();

        for (int i = 0; i < s.length(); i++) {
            Character c = s.charAt(i);

            if (openingBraces.contains(c)) paranthesesStack.push(c);

            if (closingBraceToOpeningMap.containsKey(c)) {
                if (!paranthesesStack.isEmpty() && paranthesesStack.peek() == closingBraceToOpeningMap.get(c)) {
                    paranthesesStack.pop();
                } else {
                    return false;
                }
            }
        }

        return paranthesesStack.isEmpty();
    }
}
