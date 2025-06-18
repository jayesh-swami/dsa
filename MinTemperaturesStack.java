import java.util.Stack;

public class MinTemperaturesStack {
    public int[] dailyTemperatures(int[] temperatures) {

        int[] warmerTemperatures = new int[temperatures.length];

        Stack<Integer> futureTempIndexes = new Stack<>();

        for (int i = temperatures.length - 1; i >= 0; i--) {

            while (!futureTempIndexes.isEmpty() &&
                    temperatures[i] >= temperatures[futureTempIndexes.peek()]) futureTempIndexes.pop();

            if (!futureTempIndexes.isEmpty()) warmerTemperatures[i] = futureTempIndexes.peek() - i;

            futureTempIndexes.push(i);
        }

        return warmerTemperatures;
    }
}
