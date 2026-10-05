public class LinkedListPalindrome {
    public boolean isPalindrome(ListNode head) {
        int size = 0;

        ListNode it = head;

        while(it != null) {
            size++;
            it = it.next;
        }

        it = head;

        for(int i=0 ; i < size/2 ; i++) it = it.next;

        ListNode reverse = reverseList(it);

        it = head;

        while(it != null && reverse != null) {
            if(it.val != reverse.val) return false;
            it = it.next;
            reverse = reverse.next;
        }

        return true;

    }

    private ListNode reverseList(ListNode head) {
        if(head == null) return null;

        ListNode prev = null, next = head.next, curr = head;

        while(curr != null) {
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
}
