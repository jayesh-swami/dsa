import java.util.Stack;


/**
 * Iterating from the right side and using a stack to store the index of next greater element to the right
 */
public class DailyTemperatures {

    public int[] dailyTemperatures(int[] temperatures) {
        int[] result = new int[temperatures.length];

        Stack<Integer> s = new Stack<>();

        for (int i = temperatures.length - 1; i >= 0; i--) {
            if (s.empty()) {
                s.push(i);
            } else {
                while (!s.empty() &&
                        temperatures[i] >= temperatures[s.peek()]) s.pop();

                if (!s.empty()) {
                    result[i] = s.peek() - i;
                }
                s.push(i);
            }
        }
        return result;
    }
}
