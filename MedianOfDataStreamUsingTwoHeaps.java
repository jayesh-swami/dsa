import java.util.*;

public class MedianOfDataStreamUsingTwoHeaps {
    PriorityQueue<Integer> maxHeap;
    PriorityQueue<Integer> minHeap;

    public MedianOfDataStreamUsingTwoHeaps() {
        maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        minHeap = new PriorityQueue<>();
    }

    public void addNum(int num) {
        maxHeap.offer(num);

        if(!minHeap.isEmpty() && !maxHeap.isEmpty() && maxHeap.peek() > minHeap.peek()) {
            int temp = minHeap.poll();
            minHeap.offer(maxHeap.poll());
            maxHeap.offer(temp);
        }

        if(maxHeap.size() - minHeap.size() >= 2) {
            minHeap.offer(maxHeap.poll());
        }
    }

    public double findMedian() {
        if(minHeap.size() == maxHeap.size()) {
            return ((double) minHeap.peek() + (double) maxHeap.peek()) / (double) 2;
        }
        return maxHeap.peek();
    }
}
