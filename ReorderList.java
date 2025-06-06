public class ReorderList {
    public void reorderList(ListNode head) {
        int n = 0;
        ListNode it = head;
        while (it != null) {
            n++;
            it = it.next;
        }

        it = head;
        for (int i = 0; i < n / 2; i++) it = it.next;

        ListNode reversedSecondHalf = reverseList(it);
        it.next = null;

        mergeList(head, reversedSecondHalf);
    }

    private ListNode reverseList(ListNode node) {
        ListNode temp = null;
        ListNode next = null;

        while (node != null) {
            next = node.next;
            node.next = temp;
            temp = node;
            node = next;
        }

        return temp;
    }

    private void mergeList(ListNode node1, ListNode node2) {
        int counter = 0;

        ListNode temp = node1;
        node1 = node1.next;

        while (node1 != null && node2 != null) {
            if (counter % 2 == 0) {
                temp.next = node2;
                node2 = node2.next;
            } else {
                temp.next = node1;
                node1 = node1.next;
            }
            counter++;
            temp = temp.next;
        }
    }
}
