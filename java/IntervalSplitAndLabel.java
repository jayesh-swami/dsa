import java.util.*;

public class IntervalSplitAndLabel {

    public List<List<String>> splitAndLabel(List<List<String>> in) {

        Set<Integer> events = new TreeSet<>();
        Map<Integer, List<String>> openEvents = new HashMap<>();
        Map<Integer, List<String>> closeEvents = new HashMap<>();

        for (List<String> event : in) {
            int open = Integer.parseInt(event.get(0));
            int close = Integer.parseInt(event.get(1));
            String label = event.get(2);

            events.add(open);
            events.add(close);

            openEvents.putIfAbsent(open, new ArrayList<>());
            closeEvents.putIfAbsent(close, new ArrayList<>());

            openEvents.get(open).add(label);
            closeEvents.get(close).add(label);
        }

        int start = -1;
        int end = 0;

        Set<String> intervalLabels =  new HashSet<>();
        List<List<String>> res = new ArrayList<>();

        for(Integer event: events) {
            if(start == -1) {
                start = event;
                intervalLabels.addAll(openEvents.get(event));
            } else {
                end = event;

                List<String> interval = new ArrayList<>();

                interval.add(String.valueOf(start));
                interval.add(String.valueOf(end));
                interval.add(String.join(",", new ArrayList<>(intervalLabels)));

                if(closeEvents.containsKey(event))
                    intervalLabels.removeAll(closeEvents.get(event));
                if(openEvents.containsKey(event))
                    intervalLabels.addAll(openEvents.get(event));
                start = event;

                res.add(interval);
            }
        }

        return res;
    }
}
