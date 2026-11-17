struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // One pass: fast starts n ahead of slow (slow on the dummy)
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(-1, head);
        ListNode *s = &dummy, *f = head;

        while(n) { f = f->next; n--;}

        while(f) {s = s->next; f = f->next; }

        ListNode *prev = s, *curr = s->next, *next = curr->next;

        prev->next = next;

        return dummy.next;
    }

    // Two passes: count the length, then walk len - n steps
    ListNode* removeNthFromEndTwoPass(ListNode* head, int n) {
        ListNode dummy(-1, head);
        int skips = listLen(head) - n;

        ListNode *prev = &dummy, *curr = head, *next = head->next;

        while(skips) {
            curr = curr->next;
            prev = prev->next;
            next = next->next;
            skips--;
        }

        prev->next = next;

        return dummy.next;
    }

    int listLen(ListNode* head){
        int n = 0;

        while(head) {
            n++;
            head = head->next;
        }

        return n;
    }
};
