import java.util.*;

public class MinHeap {

    private final Integer size;
    private Integer currentSize;
    private final List<Integer> heap;

    public MinHeap(Integer size) {
        this.size = size;
        this.currentSize = 0;
        this.heap = new ArrayList<>(Collections.nCopies(size, Integer.MAX_VALUE));
    }

    public void add(Integer n) {
        if (Objects.equals(currentSize, size)) {
            return;
        }
        heap.set(currentSize, n);

        int it = currentSize;

        while(it > 0 && heap.get(getParentIndex(it)) > heap.get(it)) {
            int parent = getParentIndex(it);
            swapValuesAtIndex(parent, it);
            it = parent;
        }

        currentSize++;

        heap.getFirst();
    }

    public Integer top() {
        return heap.getFirst();
    }

    public void removeTop() {
        heap.set(0, heap.get(currentSize - 1));
        heap.set(currentSize - 1, Integer.MAX_VALUE);

        currentSize--;

        minHeapify(0);
    }

    public boolean isFull() {
        return Objects.equals(size, currentSize);
    }

    private void minHeapify(Integer index) {
        if(!isLeaf(index)) {
            int leftIndex = getLeftChildIndex(index);
            int rightIndex = getRightChildIndex(index);
            if(heap.get(index) > heap.get(leftIndex) || heap.get(index) > heap.get(rightIndex)) {
                if(heap.get(leftIndex) < heap.get(rightIndex)) {
                    swapValuesAtIndex(index, leftIndex);
                    minHeapify(leftIndex);
                } else {
                    swapValuesAtIndex(index, rightIndex);
                    minHeapify(rightIndex);
                }
            }
        }
    }

    private void swapValuesAtIndex(int index1, int index2) {
        int temp = heap.get(index1);
        heap.set(index1, heap.get(index2));
        heap.set(index2, temp);
    }

    private boolean isLeaf(Integer index) {
        return getLeftChildIndex(index) >= size || getRightChildIndex(index) >= size;
    }

    private static Integer getParentIndex(Integer i) {
        return (i - 1) / 2;
    }

    private static Integer getLeftChildIndex(Integer parentIndex) {
        return 2 * parentIndex + 1;
    }

    private static Integer getRightChildIndex(Integer parentIndex) {
        return 2 * parentIndex + 2;
    }
}