import java.util.ArrayList;
import java.util.List;

public class BinaryTreeRightSideView {
    public List<Integer> rightSideView(TreeNode root) {
        List<Integer> result = new ArrayList<>();
        fillRightSide(root, 0, result);
        return result;
    }

    void fillRightSide(TreeNode root, int depth, List<Integer> result) {
        if(root == null) return;

        if(result.size() <= depth) result.add(root.val);

        fillRightSide(root.right, depth + 1, result);
        fillRightSide(root.left, depth + 1, result);
    }
}
