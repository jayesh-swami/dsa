import java.util.*;

public class GroupAnagrams {
    public List<List<String>> groupAnagrams(String[] strs) {
        HashMap<List<Integer>, List<String>> map = new HashMap<>();

        for(String s: strs) {
            List<Integer> l = new ArrayList<>(Collections. nCopies(26, 0));

            for(int i=0; i < s.length(); i++) {
                int index = s.charAt(i) - 'a';
                l.set(index , l.get(index) + 1);
            }

            if(map.containsKey(l)) {
                map.get(l).add(s);
            } else {
                map.put(l, new ArrayList<>(List.of(s)));
            }
        }

        List<List<String>> result = new ArrayList<>();

        for(List<Integer> it: map.keySet()) {
            result.add(map.get(it));
        }

        return result;
    }
}
