public class RemoveElementsFromLinkedList {
    public ListNode removeElements(ListNode head, int val) {

        while(head != null && head.val == val) head = head.next;

        if(head == null) return null;

        ListNode prev = head, it = head.next;

        while(it != null) {

            if(it.val == val) {
                while(it != null && it.val == val) it = it.next;

                prev.next = it;
            } else {
                prev = it;
                it = it.next;
            }
        }

        return head;
    }
}
