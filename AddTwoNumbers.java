public class AddTwoNumbers {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {

        ListNode head = new ListNode(0);
        ListNode it = head;

        int carry = 0;

        int t = l1.val + l2.val + carry;
        it.val = t % 10;
        carry = t / 10;

        l1 = l1.next;
        l2 = l2.next;

        while (l1 != null || l2 != null) {
            ListNode temp = new ListNode(0);

            int l1Val = l1 == null ? 0 : l1.val;
            int l2Val = l2 == null ? 0 : l2.val;

            int total = l1Val + l2Val + carry;
            temp.val = total % 10;
            carry = total / 10;

            it.next = temp;
            l1 = l1 == null ? l1 : l1.next;
            l2 = l2 == null ? l2 : l2.next;
            it = it.next;
        }

        if (carry != 0) {
            ListNode temp = new ListNode(carry);
            it.next = temp;
        }

        return head;
    }
}
