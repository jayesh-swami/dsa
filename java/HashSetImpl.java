public class HashSetImpl {

    private final int MAX_HASH_SIZE = 1000;
    private final Node[] hashMap;

    static class Node {
        int key;
        Node next;

        Node() {
        }
    }

    public HashSetImpl() {
        this.hashMap = new Node[MAX_HASH_SIZE];
    }

    public void add(int key) {
        if (contains(key)) return;

        Node temp = new Node();
        temp.key = key;

        if (hashMap[hash(key)] != null) temp.next = hashMap[hash(key)];

        hashMap[hash(key)] = temp;
    }

    public void remove(int key) {
        Node temp = hashMap[hash(key)];
        Node prev = null;

        while (temp != null) {
            if (temp.key == key) {
                if (prev == null) {
                    hashMap[hash(key)] = temp.next;
                } else {
                    prev.next = temp.next;
                    temp.next = null;
                }
            }
            prev = temp;
            temp = temp.next;
        }
    }

    public boolean contains(int key) {
        Node temp = hashMap[hash(key)];

        while (temp != null) {
            if (temp.key == key) return true;
            temp = temp.next;
        }

        return false;
    }

    private int hash(int key) {
        return key % MAX_HASH_SIZE;
    }
}
