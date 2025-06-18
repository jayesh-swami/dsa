import java.util.*;

public class InorderTraversalUsingStack {
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> res = new ArrayList<>();

        Stack<TreeNode> s = new Stack<>();

        TreeNode it = root;

        while (!s.isEmpty() || it != null) {

            while (it != null) {

                s.push(it);

                it = it.left;
            }

            it = s.pop();
            res.add(it.val);

            it = it.right;
        }

        return res;
    }
}
