class ValidBinarySearchTree {

    public boolean isValidBST(TreeNode root) {
        if(root == null) return true;

        return isValidBst(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
    }

    private boolean isValidBst(TreeNode root, int min, int max) {
        if(root == null) return true;

        if(root.val < min || root.val > max) return false;

        return isValidBst(root.left, min, root.val - 1) 
        && isValidBst(root.right, root.val + 1, max);
    }
    
}