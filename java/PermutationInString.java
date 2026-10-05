public class PermutationInString {

    public boolean checkInclusion(String s1, String s2) {
        if (s1.length() > s2.length()) return false;

        int[] s1Freq = new int[26];
        int[] window = new int[26];

        for (int i = 0; i < s1.length(); i++) {
            s1Freq[s1.charAt(i) - 'a']++;
            window[s2.charAt(i) - 'a']++;
        }

        for (int i = 0; i < s2.length() - s1.length(); i++) {
            if (checkIfSameCharFreq(s1Freq, window)) return true;
            window[s2.charAt(i) - 'a']--;
            window[s2.charAt(i + s1.length()) - 'a']++;
        }

        return checkIfSameCharFreq(s1Freq, window);
    }

    private boolean checkIfSameCharFreq(int[] freq1, int[] freq2) {
        for (int i = 0; i < 26; i++) {
            if (freq1[i] != freq2[i]) return false;
        }
        return true;
    }
}
