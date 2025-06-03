public class DiameterOfTree {
    private int diameter = 0;

    public int diameterOfBinaryTree(InvertBinaryTree.TreeNode root) {
        treeHeightAndDiameterUpdate(root);

        return this.diameter;
    }

    private int treeHeightAndDiameterUpdate(InvertBinaryTree.TreeNode root) {
        if(root == null) return 0;

        int leftHeight = treeHeightAndDiameterUpdate(root.left);
        int rightHeight = treeHeightAndDiameterUpdate(root.right);

        this.diameter = Math.max(diameter, leftHeight + rightHeight);

        return 1 + Math.max(leftHeight, rightHeight);
    }
}
