import java.util.HashMap;
import java.util.Map;

class TrieNode {
    Character nodeIndex;
    Map<Character, TrieNode> children;
    boolean key;

    TrieNode(Character nodeIndex) {
        children = new HashMap<>();
        key = false;
        this.nodeIndex = nodeIndex;
    }
}