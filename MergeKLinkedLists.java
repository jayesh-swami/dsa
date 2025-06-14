public class MergeKLinkedLists {
    public ListNode mergeKLists(ListNode[] lists) {
        if (lists.length == 0) return null;

        ListNode head = lists[0];

        for (int i = 1; i < lists.length; i++)
            head = mergeTwoLists(head, lists[i]);

        return head;
    }

    private ListNode mergeTwoLists(ListNode l1, ListNode l2) {
        if (l1 == null) return l2;
        if (l2 == null) return l1;

        ListNode head = l1;
        ListNode it = l1;

        if (l2.val < l1.val) {
            it = l2;
            l2 = l2.next;
        } else {
            l1 = l1.next;
        }

        head = it;

        while (l1 != null && l2 != null) {

            if (l1.val < l2.val) {
                it.next = l1;
                l1 = l1.next;
            } else {
                it.next = l2;
                l2 = l2.next;
            }

            it = it.next;
        }

        if (l1 != null) it.next = l1;
        if (l2 != null) it.next = l2;

        return head;
    }
}
