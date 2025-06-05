import java.util.*;

public class RemoveEdgeToMakeAcyclic {

    private Set<Integer> visited = new HashSet<>();
    private Map<Integer, List<Integer>> adj = new HashMap<>();
    private int cycleStart = -1;
    private Set<Integer> cyclicNodes = new HashSet<>();

    public int[] findRedundantConnection(int[][] edges) {

        int numberOfNodes = edges.length;

        for (int i = 1; i <= numberOfNodes; i++) {
            adj.put(i, new ArrayList<>());
        }

        for (int[] edge : edges) {
            adj.get(edge[0]).add(edge[1]);
            adj.get(edge[1]).add(edge[0]);
        }

        cycleDetect(1, -1);

        for (int i = edges.length - 1; i >= 0; i--) {
            int u = edges[i][0], v = edges[i][1];
            if (cyclicNodes.contains(u) && cyclicNodes.contains(v)) {
                return new int[]{u, v};
            }
        }
        return new int[0];

    }

    private boolean cycleDetect(int node, int parent) {
        if (visited.contains(node)) {
            cycleStart = node;
            return true;
        }

        visited.add(node);

        for (int adjNode : adj.get(node)) {
            if (adjNode == parent) continue;
            if (cycleDetect(adjNode, node)) {
                if (cycleStart != -1) cyclicNodes.add(node);
                if (node == cycleStart) {
                    cycleStart = -1;
                }
                return true;
            }
        }

        return false;
    }

}
