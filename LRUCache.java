import java.util.*;

class LRUCache {

    static class Node {
        Node prev;
        Node next;
        int key;
        int val;

        Node(int key, int val) {
            this.key = key;
            this.val = val;
        }
    }

    Node head;
    Node tail;
    Map<Integer, Node> nodeMap;
    int capacity;

    public LRUCache(int capacity) {
        this.capacity = capacity;
        nodeMap = new HashMap<>();
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head.prev = tail;
        tail.next = head;
    }

    public int get(int key) {
        if (!nodeMap.containsKey(key)) return -1;

        Node node = nodeMap.get(key);

        // remove the node
        node.prev.next = node.next;
        node.next.prev = node.prev;

        // add the node to front
        node.next = head;
        node.prev = head.prev;
        head.prev.next = node;
        head.prev = node;

        return node.val;
    }

    public void put(int key, int value) {
        if (nodeMap.containsKey(key)) {
            Node node = nodeMap.get(key);

            // remove the node
            node.prev.next = node.next;
            node.next.prev = node.prev;
            node.next = null;
            node.prev = null;

            nodeMap.remove(key);
        }

        Node newNode = new Node(key, value);

        nodeMap.put(key, newNode);

        newNode.next = head;
        newNode.prev = head.prev;
        head.prev.next = newNode;
        head.prev = newNode;

        if (nodeMap.size() > capacity) {
            // remove node from tail
            Node end = tail.next;
            tail.next = tail.next.next;
            end.next.prev = tail;
            end.next = null;
            end.prev = null;

            nodeMap.remove(end.key);
        }
    }
}
