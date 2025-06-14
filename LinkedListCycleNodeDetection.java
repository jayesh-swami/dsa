public class LinkedListCycleNodeDetection {
    public ListNode detectCycle(ListNode head) {

        ListNode slowP = head;
        ListNode fastP = head;

        while (slowP != null && fastP != null && fastP.next != null) {
            slowP = slowP.next;
            fastP = fastP.next.next;

            if (slowP == fastP) {
                ListNode temp = head;

                while (temp != slowP) {
                    temp = temp.next;
                    slowP = slowP.next;
                }

                return slowP;
            }
        }

        return null;
    }
}
