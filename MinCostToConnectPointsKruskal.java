import java.util.*;

public class MinCostToConnectPointsKruskal {
    private int[] uf;

    public int minCostConnectPoints(int[][] points) {
        uf = new int[points.length];

        for (int i = 0; i < uf.length; i++) uf[i] = i;

        Map<Integer, List<int[]>> edges = new TreeMap<>();

        for (int i = 0; i < points.length; i++) {
            for (int j = i + 1; j < points.length; j++) {
                int manhattanDistance =
                        Math.abs(points[i][0] - points[j][0]) +
                                Math.abs(points[i][1] - points[j][1]);

                if (!edges.containsKey(manhattanDistance)) edges.put(manhattanDistance, new ArrayList<>());

                edges.get(manhattanDistance).add(new int[]{i, j});
            }
        }

        int cost = 0;

        for (Map.Entry<Integer, List<int[]>> entry : edges.entrySet()) {

            for (int[] pointsIdx : entry.getValue()) {
                int idx1 = pointsIdx[0];
                int idx2 = pointsIdx[1];

                if (union(idx1, idx2))
                    cost += entry.getKey();
            }

        }

        return cost;
    }

    private boolean union(int n1, int n2) {
        if (find(n1) == find(n2)) return false;

        uf[find(n2)] = find(n1);

        return true;
    }

    private int find(int n) {
        while (uf[n] != n) {
            uf[n] = uf[uf[n]];
            n = uf[n];
        }

        return n;
    }
}
