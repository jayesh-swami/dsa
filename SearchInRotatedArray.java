public class SearchInRotatedArray {

    public int search(int[] nums, int target) {
        int low = 0, high = nums.length - 1;

        int minElementIndex = low;

        while (low < high) {
            int mid = (low + high) / 2;

            if (nums[low] < nums[high]) {
                minElementIndex = low;
                break;
            } else if (nums[mid] < nums[high]) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        minElementIndex = low;

        if (minElementIndex == 0) {
            return binarySearch(nums, target, 0, nums.length - 1);
        } else if (nums[0] > target) {
            return binarySearch(nums, target, minElementIndex, nums.length - 1);
        } else {
            return binarySearch(nums, target, 0, minElementIndex - 1);
        }
    }

    private int binarySearch(int[] nums, int target, int low, int high) {
        int l = low, h = high;

        while (l <= h) {
            int mid = (l + h) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                l = mid + 1;
            } else {
                h = mid - 1;
            }
        }

        return -1;
    }

}
