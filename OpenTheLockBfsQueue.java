import java.util.*;

public class OpenTheLockBfsQueue {
    static class CombinationStep {
        String combination;
        int steps;

        CombinationStep(String combination, int steps) {
            this.combination = combination;
            this.steps = steps;
        }
    }

    private Set<String> deadendCombinations;
    private Map<String, Integer> visited;

    public int openLock(String[] deadends, String target) {

        deadendCombinations = new HashSet<>();
        visited = new HashMap<>();

        for (String combination : deadends)
            deadendCombinations.add(combination);

        bfs("0000", target);

        return visited.containsKey(target) ? visited.get(target) : -1;
    }

    private void bfs(String start, String target) {

        Queue<CombinationStep> q = new LinkedList<>();

        q.add(new CombinationStep(start, 0));

        while (!q.isEmpty()) {
            CombinationStep currentCombinationStep = q.poll();

            String currentCombination = currentCombinationStep.combination;
            int currentSteps = currentCombinationStep.steps;

            if (deadendCombinations.contains(currentCombination) || visited.containsKey(currentCombination))
                continue;

            visited.put(currentCombination, currentSteps);

            if (currentCombination.equals(target)) break;

            List<String> nextCombinations = getNextPossibleCombinations(currentCombination);

            for (String nextComb : nextCombinations) q.add(new CombinationStep(nextComb, currentSteps + 1));
        }
    }

    private List<String> getNextPossibleCombinations(String combination) {
        char[] combArray = combination.toCharArray();

        List<String> result = new ArrayList<>();

        for (int i = 0; i < 4; i++) {
            combArray[i] = getNextChar(combArray[i]);
            result.add(String.valueOf(combArray));
            combArray[i] = getPrevChar(combArray[i]);

            combArray[i] = getPrevChar(combArray[i]);
            result.add(String.valueOf(combArray));
            combArray[i] = getNextChar(combArray[i]);
        }

        return result;
    }

    private char getNextChar(Character c) {
        if (c == '9') return '0';

        return (char) ((int) c + 1);
    }

    private char getPrevChar(Character c) {
        if (c == '0') return '9';

        return (char) ((int) c - 1);
    }
}
