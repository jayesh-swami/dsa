import java.util.*;

public class MinIndexSumOfTwoLists {

    public String[] findRestaurant(String[] list1, String[] list2) {

        Map<String, Integer> list1Map = new HashMap<>();
        Map<String, Integer> list2Map = new HashMap<>();

        for (int i = 0; i < list1.length; i++) list1Map.put(list1[i], i);
        for (int i = 0; i < list2.length; i++) list2Map.put(list2[i], i);

        List<String> res = new ArrayList<>();
        int indexSum = Integer.MAX_VALUE;

        for (Map.Entry<String, Integer> entry : list1Map.entrySet()) {
            if (list2Map.containsKey(entry.getKey())) {
                if (entry.getValue() + list2Map.get(entry.getKey()) < indexSum) {
                    indexSum = entry.getValue() + list2Map.get(entry.getKey());
                }
            }
        }

        for (Map.Entry<String, Integer> entry : list1Map.entrySet()) {
            if (list2Map.containsKey(entry.getKey())) {
                if (entry.getValue() + list2Map.get(entry.getKey()) == indexSum) {
                    res.add(entry.getKey());
                }
            }
        }

        return res.toArray(new String[res.size()]);
    }
}
