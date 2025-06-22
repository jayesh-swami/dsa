import java.util.*;

public class ConnectedComponentsBfs {
    Set<Integer> visited = new HashSet<>();
    Map<Integer, List<Integer>> adjList = new HashMap<>();

    public int countComponents(int n, int[][] edges) {
        for (int i = 0; i < n; i++) adjList.put(i, new ArrayList<>());

        for (int i = 0; i < edges.length; i++) {
            adjList.get(edges[i][0]).add(edges[i][1]);
            adjList.get(edges[i][1]).add(edges[i][0]);
        }

        int connectedComponents = 0;

        for (int i = 0; i < n; i++) {
            if (!visited.contains(i)) {
                connectedComponents++;
                bfsVisit(i);
            }
        }

        return connectedComponents;
    }

    private void bfsVisit(int n) {
        Queue<Integer> q = new LinkedList<>();
        Set<Integer> visiting = new HashSet<>();
        q.add(n);

        while (!q.isEmpty()) {
            int node = q.poll();

            visiting.add(node);

            for (Integer neighbour : adjList.get(node)) {
                if (!visiting.contains(neighbour)) q.add(neighbour);
            }
            visited.add(node);
        }
    }
}
