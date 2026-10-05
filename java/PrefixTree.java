class PrefixTree {

    private TrieNode root;

    public PrefixTree() {
        root = new TrieNode(null);
    }

    public void insert(String word) {
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

    public boolean search(String word) {
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

    public boolean startsWith(String prefix) {
        TrieNode node = root;

        for (int i = 0; i < prefix.length(); i++) {
            Character c = prefix.charAt(i);

            if (node.children.containsKey(c)) {
                node = node.children.get(c);
            } else {
                return false;
            }
        }

        return true;
    }
}
