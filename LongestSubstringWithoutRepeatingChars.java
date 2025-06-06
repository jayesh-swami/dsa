import java.util.*;

public class LongestSubstringWithoutRepeatingChars {

    private Map<Character, Integer> count = new HashMap<>();

    public int lengthOfLongestSubstring(String s) {

        if (s.length() == 0) return 0;

        for (int i = 0; i < s.length(); i++) {
            if (!count.containsKey(s.charAt(i)))
                count.put(s.charAt(i), 0);
        }

        int result = 1;

        int left = 0, right = 0;

        while (right < s.length()) {
            while (count.get(s.charAt(right)) >= 1) {
                count.replace(
                        s.charAt(left),
                        count.get(s.charAt(left)) - 1);
                left++;
            }
            result = Math.max(result, right - left + 1);
            count.replace(
                    s.charAt(right),
                    count.get(s.charAt(right)) + 1);
            right++;

        }

        return result;

    }
}
