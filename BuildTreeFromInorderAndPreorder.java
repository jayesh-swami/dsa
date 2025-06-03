import java.util.HashMap;
import java.util.Map;

public class BuildTreeFromInorderAndPreorder {

    private int preIndex = 0;

    public TreeNode buildTree(int[] preorder, int[] inorder) {
        Map<Integer, Integer> inorderMap = new HashMap<>();

        for(int i=0 ; i < inorder.length ; i++) inorderMap.put(inorder[i], i);

        return buildTree(preorder, inorder, 0, inorder.length - 1, inorderMap);
    }

    private TreeNode buildTree(
            int[] preorder,
            int[] inorder,
            int left,
            int right,
            Map<Integer, Integer> inorderMap) {
        if(left > right || left < 0 || right >= inorder.length) return null;

        TreeNode node = new TreeNode(preorder[preIndex]);

        int inorderIndex = inorderMap.get(preorder[preIndex]);

        preIndex = preIndex + 1;

        node.left = buildTree(
                preorder,
                inorder,
                left,
                inorderIndex - 1,
                inorderMap);

        node.right = buildTree(
                preorder,
                inorder,
                inorderIndex + 1,
                right,
                inorderMap);

        return node;
    }
}
