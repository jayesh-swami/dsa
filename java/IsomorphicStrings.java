import java.util.*;

public class IsomorphicStrings {

    public boolean isIsomorphic(String s, String t) {
        if (s.length() != t.length()) return false;

        int n = s.length();

        Map<Character, Integer> sFirstIndexesMap = new HashMap<>();
        Map<Character, Integer> tFirstIndexesMap = new HashMap<>();

        for (int i = 0; i < n; i++) {

            char c1 = s.charAt(i);
            char c2 = t.charAt(i);

            if (!sFirstIndexesMap.containsKey(c1)) sFirstIndexesMap.put(c1, i);

            if (!tFirstIndexesMap.containsKey(c2)) tFirstIndexesMap.put(c2, i);

            if (sFirstIndexesMap.get(c1) != tFirstIndexesMap.get(c2)) return false;
        }

        return true;
    }
}
