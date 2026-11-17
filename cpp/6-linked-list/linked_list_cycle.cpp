struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode *slowptr = head, *fastptr = head;

        while(slowptr && fastptr) {
            if(!fastptr->next || !fastptr->next->next) break;

            slowptr = slowptr->next;
            fastptr = fastptr->next->next;

            if(slowptr == fastptr) return true;
        }
        return false;
    }
};
