public class ValidPalindrome {

    public boolean isPalindrome(String s) {
        String ss = s.toLowerCase();

        ss = ss.replaceAll("[^a-z0-9]", "");

        for(int i=0, j = s.length()-1 ; i <= j ; i++,j--) {
            if(ss.charAt(i) != ss.charAt(j)) return false;
        }
        return true;
    }

}
