import java.util.*;

public class KeysAndRooms {
    public boolean canVisitAllRooms(List<List<Integer>> rooms) {
        Set<Integer> visited = new HashSet<>();

        Queue<Integer> q = new LinkedList<>();

        q.offer(0);

        while(!q.isEmpty()) {
            int room = q.poll();

            visited.add(room);

            for(Integer roomToBeUnlocked: rooms.get(room)) {
                if(!visited.contains(roomToBeUnlocked)) q.offer(roomToBeUnlocked);
            }
        }

        return visited.size() == rooms.size();
    }
}
