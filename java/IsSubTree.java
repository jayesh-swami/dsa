public class IsSubTree {

    public boolean isSubtree(TreeNode root, TreeNode subRoot) {
        if(root == subRoot) return true;

        if(root == null || subRoot == null) return false;

        if(root.val == subRoot.val) return isSameTree(root, subRoot) || (isSubtree(root.left, subRoot) || isSubtree(root.right, subRoot));

        return isSubtree(root.left, subRoot) || isSubtree(root.right, subRoot);
    }

    private boolean isSameTree(TreeNode p, TreeNode q) {
        if(p == q) return true;

        if(p == null || q == null) return false;

        return p.val == q.val && isSameTree(p.left, q.left) && isSameTree(p.right, q.right);
    }
}
