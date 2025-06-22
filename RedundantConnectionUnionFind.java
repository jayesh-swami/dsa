public class RedundantConnectionUnionFind {

    private int[] unionFindSet;

    public int[] findRedundantConnection(int[][] edges) {
        unionFindSet = new int[edges.length];

        for (int i = 0; i < edges.length; i++) unionFindSet[i] = i;

        for (int i = 0; i < edges.length; i++) {
            int node1 = edges[i][0] - 1;
            int node2 = edges[i][1] - 1;

            if (find(node1) == find(node2)) return edges[i];

            union(node1, node2);
        }

        return new int[]{};
    }

    private void union(int a, int b) {
        unionFindSet[find(b)] = find(a);
    }

    private int find(int n) {
        while (unionFindSet[n] != n) {
            unionFindSet[n] = unionFindSet[unionFindSet[n]];
            n = unionFindSet[n];
        }

        return n;
    }
}
