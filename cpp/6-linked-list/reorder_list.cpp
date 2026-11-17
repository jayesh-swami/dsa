struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode *slowptr = head, *fastptr = head;

        while(fastptr && fastptr->next) {
            slowptr = slowptr->next;
            fastptr = fastptr->next->next;
        }

        ListNode *rev = reverseList(slowptr->next);
        slowptr->next = nullptr;

        zip(head, rev);
    }

    void zip(ListNode* l1, ListNode* l2) {
        ListNode dummy;
        ListNode *it = &dummy;
        int i = 0;

        while(l1 && l2) {
            if(i%2) {
                it->next = l2;
                l2 = l2->next;
            } else {
                it->next = l1;
                l1 = l1->next;
            }
            it = it->next;
            i++;
        }

        if(l1) it->next = l1;
        if(l2) it->next = l2;

        return;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr, *curr = head, *next = head;

        while(curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev;
    }
};
