public class LongestRepeatingCharacterWithReplacement {
    private int[] freq = new int[26];

    public int characterReplacement(String s, int k) {
        int l = 0, r = 0;
        int res = 0;

        while (r < s.length()) {
            if (checkIfPossible(k)) {
                res = Math.max(res, r - l);
                freq[s.charAt(r) - 'A']++;
                r++;
            } else {
                freq[s.charAt(l) - 'A']--;
                l++;
            }
        }
        if (checkIfPossible(k)) res = Math.max(res, r - l);
        return res;
    }

    private boolean checkIfPossible(int k) {
        int maxFreqIndex = -1;

        for (int i = 0; i < 26; i++) {
            if (maxFreqIndex == -1 || freq[i] >= freq[maxFreqIndex]) {
                maxFreqIndex = i;
            }
        }

        int restCount = 0;

        for (int i = 0; i < 26; i++) {
            if (i != maxFreqIndex) {
                restCount += freq[i];
            }
        }

        return restCount <= k;
    }
}
