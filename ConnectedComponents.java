import java.util.*;

public class ConnectedComponents {

    private Set<Integer> visited = new HashSet<>();
    private Map<Integer, List<Integer>> adj = new HashMap<>();

    public int countComponents(int n, int[][] edges) {

        int result = 0;

        for (int i = 0; i < n; i++) {
            adj.put(i, new ArrayList<>());
        }

        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }

        for (int i = 0; i < n; i++) {
            if (!visited.contains(i)) {
                visitAllFromNode(i, -1);
                result++;
            }
        }

        return result;
    }

    private void visitAllFromNode(int node, int parent) {
        if (visited.contains(node)) return;

        visited.add(node);
        for (int adjNode : adj.get(node)) {
            if (adjNode == parent) continue;
            visitAllFromNode(adjNode, node);
        }
    }
}
