public class LargestPathSum {

    int maxSum = Integer.MIN_VALUE;

    public int maxPathSum(TreeNode root) {
        maxPathSumUtil(root);

        return maxSum;
    }

    private int maxPathSumUtil(TreeNode node) {
        if (node == null) return 0;

        int maxSumOfSubtreeLeft = maxPathSumUtil(node.left);
        int maxSumOfSubtreeRight = maxPathSumUtil(node.right);

        maxSum = Math.max(
                maxSum,
                Math.max(
                        Math.max(
                                maxSumOfSubtreeLeft + node.val,
                                maxSumOfSubtreeRight + node.val),
                        Math.max(
                                node.val,
                                maxSumOfSubtreeLeft + maxSumOfSubtreeRight + node.val)
                )
        );

        return Math.max(
                Math.max(
                        maxSumOfSubtreeLeft + node.val,
                        maxSumOfSubtreeRight + node.val),
                node.val
        );
    }
}
