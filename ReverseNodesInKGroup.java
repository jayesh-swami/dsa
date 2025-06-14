public class ReverseNodesInKGroup {
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(0, head);
        ListNode prevGroupTail = dummy;

        while (true) {
            ListNode kth = getKth(prevGroupTail, k);

            if (kth == null) break;

            ListNode nextGroupHead = kth.next;

            ListNode prev = kth.next;
            ListNode curr = prevGroupTail.next;

            while (curr != nextGroupHead) {
                ListNode tmp = curr.next;
                curr.next = prev;
                prev = curr;
                curr = tmp;
            }

            ListNode tmp = prevGroupTail.next;
            prevGroupTail.next = kth;
            prevGroupTail = tmp;
        }

        return dummy.next;
    }


    private ListNode getKth(ListNode node, int k) {

        while(node != null && k > 0) {
            node = node.next;
            k--;
        }

        return node;
    }
}
