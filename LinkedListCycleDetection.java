import java.util.HashSet;
import java.util.Set;

class LinkedListCycleDetection {

    static class ListNode {
        int val;
        ListNode next;

        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public static void main(String[] args) {
        ListNode node1 = new ListNode(1);
        ListNode node2 = new ListNode(2);
        ListNode node3 = new ListNode(3);
        ListNode node4 = new ListNode(4);
        ListNode node5 = new ListNode(5);

        node1.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node5;
        node5.next = node2;

        System.out.println(hasCycle(node1));
    }

    /**
     * Simple solution that keeps track of the value and if there is a repetition there is a cycle
     * @param head
     * @return
     */
    private static boolean hasCycle(ListNode head) {
        Set<ListNode> map = new HashSet<>();

        if(head == null) return false;

        while(head.next != null) {
            if(map.contains(head)) {
                return true;
            }
            map.add(head);
            head = head.next;
        }
        return false;
    }

    /**
     * Am improved solution that uses the two pointer method. Basically has 2 pointers
     * moving at 1 and 2 speed. If they land on the same node, there is a cycle
     * @param head
     * @return
     */
    private static boolean hasCycleImproved(ListNode head) {
        ListNode slowPointer = head;
        ListNode fastPointer = head;

        if(fastPointer == null) return false;

        while(fastPointer.next != null && fastPointer.next.next != null) {
            slowPointer = slowPointer.next;
            fastPointer = fastPointer.next.next;

            if(slowPointer == fastPointer) return true;
        }
        return false;
    }
}