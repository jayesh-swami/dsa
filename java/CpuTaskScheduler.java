import java.util.*;

public class CpuTaskScheduler {
    public int leastInterval(char[] tasks, int n) {

        Queue<CpuTask> q = new LinkedList<>();

        PriorityQueue<Integer> pq = new PriorityQueue<>(Collections.reverseOrder());

        Map<Character, Integer> taskCount = new HashMap<>();

        for (char task : tasks)
            taskCount.put(task, taskCount.getOrDefault(task, 0) + 1);

        for (Integer count : taskCount.values())
            pq.offer(count);

        int currentCpuCycle = 0;

        while (!pq.isEmpty() || !q.isEmpty()) {
            currentCpuCycle++;

            if (!pq.isEmpty()) {
                int count = pq.poll() - 1;

                if (count >= 1) q.add(new CpuTask(count, currentCpuCycle + n));
            }

            if (!q.isEmpty() &&
                    q.peek().timeNextAvailable == currentCpuCycle) {
                pq.offer(q.poll().count);
            }
        }

        return currentCpuCycle;
    }

    class CpuTask {
        int count;
        int timeNextAvailable;

        CpuTask(int count, int timeNextAvailable) {
            this.count = count;
            this.timeNextAvailable = timeNextAvailable;
        }
    }
}
