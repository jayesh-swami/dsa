import java.util.*;

public class ValidTreeUndirectedGraphCycleDetection {
    private final Map<Integer, List<Integer>> dep = new HashMap<>();
    private final Set<Integer> visited = new HashSet<>();

    public boolean validTree(int n, int[][] edges) {

        for (int i = 0; i < n; i++) {
            dep.put(i, new ArrayList<>());
        }

        for (int[] edge : edges) {
            dep.get(edge[0]).add(edge[1]);
            dep.get(edge[1]).add(edge[0]);
        }

        if (cycleExists(0, Integer.MIN_VALUE)) return false;


        return visited.size() == n;
    }

    private boolean cycleExists(
            int courseNum,
            int prevNode) {

        if (visited.contains(courseNum)) return true;

        visited.add(courseNum);

        for (int i = 0; i < dep.get(courseNum).size(); i++) {
            if (dep.get(courseNum).get(i) == prevNode) continue;
            if (cycleExists(dep.get(courseNum).get(i), courseNum)) return true;
        }

        return false;
    }
}
