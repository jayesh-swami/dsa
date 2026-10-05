import java.util.PriorityQueue;

class KthLargest {

    private final PriorityQueue<Integer> priorityQueue;
    private final Integer size;

    public KthLargest(int k, int[] nums) {
        size = k;
        priorityQueue = new PriorityQueue<>(k);
        for(int n: nums) {
            add(n);
        }
    }

    public int add(int val) {
        if(priorityQueue.size() < size) {
            priorityQueue.add(val);
        } else if (!priorityQueue.isEmpty() && priorityQueue.peek() < val) {
            priorityQueue.poll();
            priorityQueue.add(val);
        }

        return priorityQueue.peek();
    }
}


/**
 * Implementation with my custom min heap
 */
//class KthLargest {
//
//    private final MinHeap minHeap;
//
//    public KthLargest(int k, int[] nums) {
//        this.minHeap = new MinHeap(k);
//
//        for (int num : nums) {
//            if(!minHeap.isFull()) {
//                minHeap.add(num);
//            } else if (minHeap.top() < num) {
//                minHeap.removeTop();
//                minHeap.add(num);
//            }
//        }
//    }
//
//    public int add(int val) {
//        if(!minHeap.isFull()) {
//            minHeap.add(val);
//        } else if (minHeap.top() < val) {
//            minHeap.removeTop();
//            minHeap.add(val);
//        }
//
//        return minHeap.top();
//    }
//}