import java.util.Comparator;
import java.util.PriorityQueue;

public class KthClosestPoints {
    public int[][] kClosest(int[][] points, int k) {

        PriorityQueue<int[]> pq = new PriorityQueue(k, new PointsComparator());

        for (int i = 0; i < points.length; i++) {
            if (pq.size() < k) {
                pq.offer(points[i]);
            } else {
                if (getDistanceSquared(pq.peek()) > getDistanceSquared(points[i])) {
                    pq.poll();
                    pq.offer(points[i]);
                }
            }
        }
        int[][] result = new int[k][2];
        int i = 0;
        for (int[] point : pq) {
            result[i] = point;
            i++;
        }

        return result;
    }

    private long getDistanceSquared(int[] point) {
        return point[0] * point[0] + point[1] * point[1];
    }

    class PointsComparator implements Comparator<int[]> {

        @Override
        public int compare(int[] pointA, int[] pointB) {
            long sqrA = getDistanceSquared(pointA);
            long sqrB = getDistanceSquared(pointB);

            return Long.compare(sqrB, sqrA);
        }
    }
}
