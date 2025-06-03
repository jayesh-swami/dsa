public class BalancedTreeCheck {

    private boolean isBalanced = true;

    public boolean isBalanced(TreeNode root) {
        height(root);

        return this.isBalanced;
    }

    private int height(TreeNode root) {
        if (root == null) return 0;

        int leftHeight = height(root.left);
        int rightHeight = height(root.right);

        if (Math.abs(leftHeight - rightHeight) > 1) this.isBalanced = false;

        return 1 + Math.max(leftHeight, rightHeight);
    }
}
