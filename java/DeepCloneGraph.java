import java.util.*;

public class DeepCloneGraph {
    Map<Node, Node> nodeMap = new HashMap<>();
    Set<Node> visited = new HashSet<>();

    public Node cloneGraph(Node node) {
        if (node == null) return null;

        addNodeMap(node);
        addEdges(node);
        return nodeMap.get(node);
    }

    private void addNodeMap(Node node) {
        if (nodeMap.containsKey(node)) return;

        nodeMap.put(node, new Node(node.val));

        for (Node adjacentNode : node.neighbors) {
            addNodeMap(adjacentNode);
        }
    }

    private void addEdges(Node node) {
        if (visited.contains(node)) return;

        List<Node> adjacentNodes = new ArrayList<>();

        for (Node adjacentNode : node.neighbors) {
            adjacentNodes.add(nodeMap.get(adjacentNode));
        }

        visited.add(node);
        nodeMap.get(node).neighbors = adjacentNodes;

        for (Node adjacentNode : node.neighbors) {
            addEdges(adjacentNode);
        }
    }
}
