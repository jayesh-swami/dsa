public class InvertBinaryTree {

    public TreeNode invertTree(TreeNode root) {
        if (root == null) return root;

        TreeNode temp = invertTree(root.left);

        root.left = invertTree(root.right);
        root.right = temp;

        return root;
    }
}
