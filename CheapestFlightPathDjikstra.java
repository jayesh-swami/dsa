import java.util.*;

public class CheapestFlightPathDjikstra {

    class Flight {
        int dest;
        int price;

        Flight(int dest, int price) {
            this.dest = dest;
            this.price = price;
        }
    }

    int[] priceToDestination;
    Map<Integer, List<Flight>> flightMap = new HashMap<>();

    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {

        priceToDestination = new int[n];

        for(int i = 0 ; i < n ; i++) {
            priceToDestination[i] = Integer.MAX_VALUE;
            flightMap.put(i, new ArrayList<>());
        }

        for(int i = 0 ; i < flights.length ; i++)
            flightMap.get(flights[i][0]).add(new Flight(flights[i][1], flights[i][2]));


        djikstra(src, k, dst);

        return priceToDestination[dst] == Integer.MAX_VALUE ? -1 : priceToDestination[dst];
    }

    private void djikstra(int src, int maxStops, int dest) {
        priceToDestination[src] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>((f1, f2) -> Integer.compare(f1[1], f2[1]));
        Set<Integer> visited = new HashSet<>();

        pq.offer(new int[] {src, 0, -1});

        while(!pq.isEmpty()) {
            int[] currFlight = pq.poll();

            visited.add(currFlight[0]);

            if(currFlight[2] >= maxStops) continue;

            for(Flight flight: flightMap.get(currFlight[0])) {

                if(!visited.contains(flight.dest)) {

                    pq.offer(new int[] {
                            flight.dest,
                            currFlight[1] + flight.price,
                            currFlight[2] + 1});

                    priceToDestination[flight.dest] = Math.min(
                            priceToDestination[flight.dest],
                            currFlight[1] + flight.price);
                }
            }
        }
    }
}
