public class ReverseLinkedList {

    public ListNode reverseList(ListNode head) {
        ListNode temp = null;
        ListNode next = null;

        while (head != null) {
            next = head.next;
            head.next = temp;
            temp = head;
            head = next;
        }

        return temp;

    }
}
