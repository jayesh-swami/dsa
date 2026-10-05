class MergeLinkedListsImportant {
    /**
     * Think of it as a lagging pointer that stitches the linked list together as we move forward
     * <p>
     * The lesser value is assigned to the lagging pointer's next
     * The lesser node is incremented
     * The lagging pointer is incremented to it's next (lesser value)
     * <p>
     * At the end we merge the remaining items in the list
     *
     * @param list1
     * @param list2
     * @return
     */
    public ListNode mergeTwoLists(ListNode list1, ListNode list2) {

        if (list1 == null && list2 == null) return null;
        if (list1 == null) return list2;
        if (list2 == null) return list1;

        ListNode temp;
        ListNode head;

        if (list1.val < list2.val) {
            head = list1;
            temp = list1;
            list1 = list1.next;
        } else {
            head = list2;
            temp = list2;
            list2 = list2.next;
        }


        while (list1 != null && list2 != null) {
            if (list1.val < list2.val) {
                temp.next = list1;
                list1 = list1.next;
            } else {
                temp.next = list2;
                list2 = list2.next;
            }
            temp = temp.next;
        }

        if (list1 == null) temp.next = list2;
        if (list2 == null) temp.next = list1;

        return head;
    }

}