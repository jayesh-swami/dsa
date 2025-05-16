class MergeLinkedListsImportant {

    public static class ListNode {

        int val;
        ListNode next;

        ListNode(int val) {
            this.val = val;
        }
    }

    public static void printList(ListNode node) {
        while(node != null) {
            System.out.print(node.val + " -> ");
            node = node.next;
        }
        System.out.println("null");
    }

    public static void main(String[] args) {
        ListNode n1 = new ListNode(1);
        ListNode n2 = new ListNode(2);
        ListNode n3 = new ListNode(4);

        ListNode r1 = new ListNode(1);
        ListNode r2 = new ListNode(3);
        ListNode r3 = new ListNode(4);

        n1.next = n2;
        n2.next = n3;

        r1.next = r2;
        r2.next = r3;

        printList(mergedList(n1, r1));

    }

    /**
     * Think of it as a lagging pointer that stitches the linked list together as we move forward
     *
     * The lesser value is assigned to the lagging pointer's next
     * The lesser node is incremented
     * The lagging pointer is incremented to it's next (lesser value)
     *
     * At the end we merge the remaining items in the list
     *
     * @param list1
     * @param list2
     * @return
     */
    public static ListNode mergedList(ListNode list1, ListNode list2) {
        ListNode temp = new ListNode(-1);
        ListNode it = temp;

        while(list1 != null && list2 != null) {
            if(list1.val <= list2.val) {
                it.next = list1;
                list1 = list1.next;
            } else {
                it.next = list2;
                list2 = list2.next;
            }
            it = it.next;
        }

        it.next = list1 == null ? list2 : list1;
        return temp.next;
    }

}