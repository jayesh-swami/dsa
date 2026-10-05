class WordDictionary {
    private TrieNode root;


    public WordDictionary() {
        root = new TrieNode(null);
    }

    public void addWord(String word) {
        TrieNode node = root;

        for (int i = 0; i < word.length(); i++) {
            char c = word.charAt(i);

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

    public boolean search(String word) {
        return searchUtil(root, word, 0);
    }

    private boolean searchUtil(
            TrieNode startNode,
            String word,
            int startIndex) {

        TrieNode node = startNode;

        for (int i = startIndex; i < word.length(); i++) {
            Character c = word.charAt(i);

            if (c == '.') {
                for(TrieNode child : node.children.values()) {
                    if(searchUtil(child, word, i + 1)) return true;
                }
                return false;
            } else {
                if(!node.children.containsKey(c)) return false;
                node = node.children.get(c);
            }
        }

        return node.key;
    }
}
