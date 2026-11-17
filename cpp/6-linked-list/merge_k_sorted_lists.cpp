#include <queue>
#include <utility>
#include <vector>

using std::greater;
using std::pair;
using std::priority_queue;
using std::vector;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    // Min-heap of the current heads: O(N log k) time, O(k) space
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<>> pq;

        for(ListNode* it: lists) if(it) pq.push({it->val, it});

        ListNode dummy;
        ListNode *it = &dummy;

        while(!pq.empty()) {
            pair<int, ListNode*> p = pq.top();
            pq.pop();
            if(p.second) {
                it->next = p.second;
                it = it->next;

                if(p.second->next) pq.push({p.second->next->val, p.second->next});
            }
        }

        return dummy.next;
    }
};
