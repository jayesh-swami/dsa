import java.util.*;

public class CloneGraphDfs {
    Set<Node> nodes;
    Map<Node, List<Node>> adjList;

    public Node cloneGraph(Node node) {
        nodes = new HashSet<>();
        adjList = new HashMap<>();

        Map<Node, Node> oldToNewMap = new HashMap<>();

        dfs(node);

        for (Node oldNode : nodes) {
            oldToNewMap.put(oldNode, new Node(oldNode.val));
        }

        for (Map.Entry<Node, List<Node>> entry : adjList.entrySet()) {

            for (Node child : entry.getValue())
                oldToNewMap.get(entry.getKey()).neighbors.add(oldToNewMap.get(child));
        }

        return oldToNewMap.get(node);
    }

    private void dfs(Node node) {
        if (nodes.contains(node) || node == null) return;

        nodes.add(node);

        adjList.put(node, new ArrayList<>());

        for (Node neighbor : node.neighbors) adjList.get(node).add(neighbor);

        for (Node neighbor : node.neighbors) dfs(neighbor);
    }
}
