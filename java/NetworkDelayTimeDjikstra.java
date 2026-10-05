import java.util.*;

public class NetworkDelayTimeDjikstra {
    class GraphEdge {
        int end;
        int weight;

        GraphEdge(int end, int weight) {
            this.end = end;
            this.weight = weight;
        }
    }

    Map<Integer, List<GraphEdge>> adjList;
    Set<Integer> visited = new HashSet<>();
    int[] distance;

    public int networkDelayTime(int[][] times, int n, int k) {
        adjList = new HashMap<>();
        distance = new int[n];

        for (int i = 0; i < n; i++) {
            adjList.put(i, new ArrayList<>());
            distance[i] = Integer.MAX_VALUE;
        }

        for (int i = 0; i < times.length; i++) {
            adjList.get(times[i][0] - 1).add(
                    new GraphEdge(times[i][1] - 1, times[i][2]));
        }

        return djikstra(k - 1);
    }

    private int djikstra(int source) {
        distance[source] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>((p1, p2) -> Integer.compare(p1[1], p2[1]));

        pq.offer(new int[]{source, 0});

        while (!pq.isEmpty()) {
            int[] node = pq.poll();

            visited.add(node[0]);

            for (GraphEdge edge : adjList.get(node[0])) {
                if (!visited.contains(edge.end)) {
                    pq.offer(new int[]{edge.end, edge.weight + node[1]});
                    distance[edge.end] = Math.min(distance[edge.end], edge.weight + node[1]);
                }
            }
        }

        int maxTime = Integer.MIN_VALUE;

        for (int i = 0; i < distance.length; i++) {
            if (distance[i] == Integer.MAX_VALUE) return -1;
            maxTime = Math.max(maxTime, distance[i]);
        }

        return maxTime;
    }
}
