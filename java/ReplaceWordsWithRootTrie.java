import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ReplaceWordsWithRootTrie {

    class TrieNode {
        Character nodeIndex;
        Map<Character, TrieNode> children;
        String word;

        TrieNode(Character nodeIndex) {
            children = new HashMap<>();
            this.nodeIndex = nodeIndex;
        }
    }

    private TrieNode root = new TrieNode(null);

    public String replaceWords(List<String> dictionary, String sentence) {

        for (String word : dictionary) {
            insert(word);
        }

        String[] sentenceSeparated = sentence.split(" ");

        for (int i = 0; i < sentenceSeparated.length; i++) {

            String rootWord = getRootWord(sentenceSeparated[i]);

            if (rootWord != "") {
                sentenceSeparated[i] = rootWord;
            }
        }

        return String.join(" ", sentenceSeparated);
    }

    private void insert(String word) {
        TrieNode node = root;

        for (int i = 0; i < word.length(); i++) {
            Character c = word.charAt(i);

            if (node.children.containsKey(c)) {
                node = node.children.get(c);
            } else {
                TrieNode newNode = new TrieNode(c);
                node.children.put(c, newNode);
                node = newNode;
            }
        }

        node.word = word;
    }

    public String getRootWord(String word) {
        TrieNode node = root;

        for (int i = 0; i < word.length(); i++) {
            Character c = word.charAt(i);

            if (node.word != null) {
                return node.word;
            } else if (node.children.containsKey(c)) {
                node = node.children.get(c);
            } else {
                break;
            }
        }

        return "";
    }
}
