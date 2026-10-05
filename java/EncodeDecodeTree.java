import java.util.*;

public class EncodeDecodeTree {
    private int deserializeIndex;

    // Encodes a tree to a single string.
    public String serialize(TreeNode root) {
        List<String> encodedStrings = new ArrayList<>();

        serializeTreeUtil(root, encodedStrings);

        return String.join("#", encodedStrings);
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(String data) {
        String[] treeEncoded = data.split("#");

        deserializeIndex = -1;

        return deserializeTreeUtil(treeEncoded);
    }

    private TreeNode deserializeTreeUtil(String[] treeEncoded) {
        deserializeIndex++;
        String valueAtIndex = treeEncoded[deserializeIndex];

        if(valueAtIndex.equals("N")) return null;

        TreeNode node = new TreeNode(Integer.valueOf(valueAtIndex));

        node.left = deserializeTreeUtil(treeEncoded);
        node.right = deserializeTreeUtil(treeEncoded);

        return node;
    }

    private void serializeTreeUtil(TreeNode node, List<String> encodedStrings) {

        if(node == null) {
            encodedStrings.add("N");
            return;
        }

        encodedStrings.add(String.valueOf(node.val));
        serializeTreeUtil(node.left, encodedStrings);
        serializeTreeUtil(node.right, encodedStrings);
    }
}
