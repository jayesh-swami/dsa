struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // Iterative: O(n) time, O(1) space
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

    // Recursive: O(n) time, O(n) stack space
    ListNode* reverseListRecursive(ListNode* head) {
        if(!head) return head;
        if(!head->next) return head;

        ListNode* rev = reverseListRecursive(head->next);
        head->next->next = head;
        head->next = nullptr;

        return rev;
    }
};
