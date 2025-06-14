public class OddEvenLinkedList {
    public ListNode oddEvenList(ListNode head) {
        if (head == null) return head;

        int size = 1;

        ListNode tail = head;

        while (tail.next != null) {
            tail = tail.next;
            size++;
        }

        size = size / 2;

        int n = 0;

        ListNode prev = head, it = head.next;

        while (size != 0) {
            if (it == tail) break;

            tail.next = it;
            prev.next = it.next;
            it.next = null;

            tail = tail.next;
            prev = prev.next;
            it = prev.next;

            size--;
        }

        return head;
    }
}
