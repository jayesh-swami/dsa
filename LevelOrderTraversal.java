import java.util.*;

public class LevelOrderTraversal {
    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        levelOrderWithDepth(root, 0, result);
        return result;
    }

    private void levelOrderWithDepth(
            TreeNode root,
            int depth,
            List<List<Integer>> result) {
        if(root == null) return;

        if(result.size() <= depth) result.add(new ArrayList<>());

        result.get(depth).add(root.val);

        levelOrderWithDepth(root.left, depth + 1, result);
        levelOrderWithDepth(root.right, depth + 1, result);
    }
}
