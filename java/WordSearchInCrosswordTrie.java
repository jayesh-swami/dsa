import java.util.*;

public class WordSearchInCrosswordTrie {

    private TrieNode root = new TrieNode(null);
    private Set<List<Integer>> visited = new HashSet<>();

    public List<String> findWords(char[][] board, String[] words) {

        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[i].length; j++) {
                buildPrefixTree(board, i, j, "");
            }
        }

        List<String> result = new ArrayList<>();

        for (String word : words) {
            if (search(word)) result.add(word);
        }

        return result;
    }

    private void buildPrefixTree(char[][] board, int i, int j, String untilNow) {
        if (i < 0 || j < 0 || i >= board.length || j >= board[i].length) return;

        List<Integer> cell = new ArrayList<>();
        cell.add(i);
        cell.add(j);

        if (visited.contains(cell)) return;

        visited.add(cell);

        String newString = untilNow + board[i][j];
        insert(newString);

        buildPrefixTree(board, i + 1, j, newString);
        buildPrefixTree(board, i - 1, j, newString);
        buildPrefixTree(board, i, j + 1, newString);
        buildPrefixTree(board, i, j - 1, newString);

        visited.remove(cell);
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

        node.key = true;
    }

    private boolean search(String word) {
        TrieNode node = root;

        for (int i = 0; i < word.length(); i++) {
            Character c = word.charAt(i);

            if (node.children.containsKey(c)) {
                node = node.children.get(c);
            } else {
                return false;
            }
        }

        return node.key;
    }
}
