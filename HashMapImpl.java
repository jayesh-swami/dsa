public class HashMapImpl {

    private final int MAX_HASH_SIZE = 1000;
    private final Node[] hashMap;

    static class Node {
        int key;
        int val;
        Node next;

        Node() {
        }
    }

    public HashMapImpl() {
        this.hashMap = new Node[MAX_HASH_SIZE];
    }

    public void put(int key, int value) {
        if (get(key) != -1) remove(key);

        int hashValue = hash(key);

        Node temp = new Node();
        temp.key = key;
        temp.val = value;

        if (hashMap[hashValue] != null) temp.next = hashMap[hashValue];

        hashMap[hashValue] = temp;
    }

    public int get(int key) {
        Node temp = hashMap[hash(key)];

        while (temp != null) {
            if (temp.key == key) return temp.val;
            temp = temp.next;
        }

        return -1;
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

    private int hash(int key) {
        return key % MAX_HASH_SIZE;
    }
}
