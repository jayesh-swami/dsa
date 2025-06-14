public class FlattenDoublyLinkedList {
    static class Node {
        int val;
        Node next;
        Node prev;
        Node child;
    }

    public Node flatten(Node head) {
        Node it = head;

        while (it != null) {

            if (it.child != null) {

                Node childStart = flatten(it.child);

                Node itChild = childStart;

                while (itChild.next != null) itChild = itChild.next;

                Node itNext = it.next;

                it.next = childStart;
                childStart.prev = it;

                itChild.next = itNext;
                if (itNext != null) itNext.prev = itChild;

                it.child = null;

                it = itChild;
            }

            it = it.next;
        }

        return head;
    }
}
