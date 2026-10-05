import java.util.*;

public class ConstructFlightPath {
    Map<String, PriorityQueue<String>> flightMap = new HashMap<>();
    List<String> res = new ArrayList<>();

    public List<String> findItinerary(List<List<String>> tickets) {
        for (int i = 0; i < tickets.size(); i++) {
            String src = tickets.get(i).get(0);
            String dst = tickets.get(i).get(1);

            flightMap.putIfAbsent(src, new PriorityQueue<>());

            flightMap.get(src).offer(dst);
        }

        constructFlightPath("JFK");

        Collections.reverse(res);

        return res;
    }

    private void constructFlightPath(String src) {

        PriorityQueue<String> q = flightMap.get(src);

        while (q != null && !q.isEmpty()) {
            String nextStop = q.poll();
            constructFlightPath(nextStop);
        }

        res.add(src);
    }
}
