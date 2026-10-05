public class MaxHeap {

    private int[] heap;
    private int size;

    MaxHeap(int size) {
        heap = new int[size];
        for(int i = 0; i < size; i ++) heap[i] = Integer.MIN_VALUE;
        this.size = 0;
    }

    public boolean add(int val) {
        if(size == heap.length) return false;

        heap[size] = val;

        int idx = size;

        size++;

        while(heap[getParentIndex(idx)] < heap[idx]) {
            swapPlaces(idx, getParentIndex(idx));
            idx = getParentIndex(idx);
        }

        return true;
    }

    public int poll() {
        int top = heap[0];
        heap[0] = Integer.MIN_VALUE;
        int idx = 0;

        size--;

        while(getLeftChildIndex(idx) < heap.length && getRightChildIndex(idx) < heap.length &&
                (heap[getLeftChildIndex(idx)] > heap[idx] ||
                heap[getRightChildIndex(idx)] > heap[idx])) {

            if(heap[getLeftChildIndex(idx)] < heap[getRightChildIndex(idx)]) {
                swapPlaces(idx, getRightChildIndex(idx));
                idx = getRightChildIndex(idx);
            } else {
                swapPlaces(idx, getLeftChildIndex(idx));
                idx = getLeftChildIndex(idx);
            }
        }

        return top;
    }

    private int getParentIndex(int index) {
        return (index - 1) / 2;
    }

    private int getLeftChildIndex(int index) {
        return 2 * index + 1;
    }

    private int getRightChildIndex(int index) {
        return 2 * index + 2;
    }

    private void swapPlaces(int index1, int index2) {
        int temp = heap[index1];

        heap[index1] = heap[index2];
        heap[index2] = temp;
    }

}
