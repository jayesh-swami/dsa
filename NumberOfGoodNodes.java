public class NumberOfGoodNodes {

    private int numberOfGoodNodes = 0;

    public int goodNodes(TreeNode root) {
        if (root == null) return 0;

        goodNodesCount(root, root.val);

        return this.numberOfGoodNodes;
    }

    private void goodNodesCount(TreeNode root, int maxInPath) {
        if (root == null) return;

        if (root.val >= maxInPath) this.numberOfGoodNodes++;

        goodNodesCount(root.left, Math.max(root.val, maxInPath));
        goodNodesCount(root.right, Math.max(root.val, maxInPath));
    }
}
