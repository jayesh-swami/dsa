public class TwoSumSortedArray {
    public int[] twoSum(int[] numbers, int target) {
        int i = 0, j = numbers.length-1;

        while(numbers[i] + numbers[j] != target) {
            int sum = numbers[i] + numbers[j];
            if(sum < target) i++;
            if(sum > target) j--;
        }
        return new int[]{ i+1, j+1 };
    }
}
