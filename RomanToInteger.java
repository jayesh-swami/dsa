class RomanToInteger {

    public static void main(String[] args) {
        System.out.println(args[0]);
        System.out.println(romanToInt(args[0]));
    }

    private static int romanToInt(String romanNumeral) {
        int result = 0;
        int i = romanNumeral.length() - 1;

        for(; i >= 0; i--) {
            char c = romanNumeral.charAt(i);

            result += romanCharToInt(c);

            if(i != 0) {
                int reduceAmount = reduceAmountBy(c, romanNumeral.charAt(i-1));
                result -= reduceAmount;
                if(reduceAmount != 0) i--;
            }
        }
        return result;
    }

    private static int reduceAmountBy(char currentChar, char leftChar) {
        return switch (currentChar) {
            case 'V', 'X' -> leftChar == 'I' ? 1 : 0;
            case 'L', 'C' -> leftChar == 'X' ? 10 : 0;
            case 'M', 'D' -> leftChar == 'C' ? 100 : 0;
            default -> 0;
        };
    }

    private static int romanCharToInt(char romanCharacter) {
        return switch (romanCharacter) {
            case 'M' -> 1000;
            case 'D' -> 500;
            case 'C' -> 100;
            case 'L' -> 50;
            case 'X' -> 10;
            case 'V' -> 5;
            case 'I' -> 1;
            default -> 0;
        };
    }

    // Another solution I found on leetcode that uses a very neat trick to check
    // if 4 * current < answer then we subtract the current value from it.
    // This trick will get rid of switch case statement in reduceAmountBy function.
    public int romanToInteger(String s) {
        int ans = 0, num = 0;
        for (int i = s.length()-1; i >= 0; i--) {
            num = switch (s.charAt(i)) {
                case 'I' -> 1;
                case 'V' -> 5;
                case 'X' -> 10;
                case 'L' -> 50;
                case 'C' -> 100;
                case 'D' -> 500;
                case 'M' -> 1000;
                default -> num;
            };
            if (4 * num < ans) ans -= num;
            else ans += num;
        }
        return ans;
    }
}