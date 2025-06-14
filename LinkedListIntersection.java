public class LinkedListIntersection {
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        int lenA = 0, lenB = 0;

        ListNode itA = headA, itB = headB;

        while (itA != null) {
            itA = itA.next;
            lenA++;
        }

        while (itB != null) {
            itB = itB.next;
            lenB++;
        }

        itA = headA;
        itB = headB;

        if (lenA < lenB) {
            while (lenA != lenB) {
                itB = itB.next;
                lenB--;
            }
        } else {
            while (lenA != lenB) {
                itA = itA.next;
                lenA--;
            }
        }

        while (itA != null && itB != null) {
            if (itA == itB) return itA;

            itA = itA.next;
            itB = itB.next;
        }

        return null;

    }
}
