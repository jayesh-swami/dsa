import java.util.*;

public class DuplicateSubtrees {
    Map<String, Integer> hashMap = new HashMap<>();
    Map<String, Integer> strSerial = new HashMap<>();

    List<TreeNode> result = new ArrayList<>();
    int stringId = 0;

    public List<TreeNode> findDuplicateSubtrees(TreeNode root) {
        hashTree(root);

        return result;
    }

    private int hashTree(TreeNode node) {
        if (node == null) return 0;

        int left = hashTree(node.left);
        int right = hashTree(node.right);
        int curr = node.val;

        String serializedTree = "#" + String.valueOf(curr) + "," + String.valueOf(left) + "," + String.valueOf(right) + "#";

        hashMap.put(serializedTree, hashMap.getOrDefault(serializedTree, 0) + 1);

        if (!strSerial.containsKey(serializedTree)) {
            stringId++;
            strSerial.put(serializedTree, stringId);
        }

        if (hashMap.get(serializedTree) == 2) {
            result.add(node);
        }

        return strSerial.get(serializedTree);
    }
}
