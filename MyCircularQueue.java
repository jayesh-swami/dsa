class MyCircularQueue {

    private int[] queue;
    private int front;
    private int rear;
    private int size;
    private int capacity;

    public MyCircularQueue(int k) {
        queue = new int[k];
        front = 0;
        rear = 0;
        size = 0;
        capacity = k;
    }

    public boolean enQueue(int value) {
        if(isFull()) return false;

        size++;
        queue[rear] = value;

        if(rear == capacity - 1) {
            rear = 0;
        } else {
            rear++;
        }

        return true;
    }

    public boolean deQueue() {
        if(isEmpty()) return false;

        size--;

        if(front == capacity - 1) {
            front = 0;
        } else {
            front++;
        }

        return true;
    }

    public int Front() {
        return isEmpty() ? -1 : queue[front];
    }

    public int Rear() {
        if(isEmpty()) return -1;

        if(rear == 0) return queue[capacity - 1];

        return queue[rear - 1];
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean isFull() {
        return size == capacity;
    }
}