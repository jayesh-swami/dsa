import java.util.LinkedList;
import java.util.Queue;

public class BSTImpl {

    static class BSTNode {
        BSTNode left;
        BSTNode right;
        int data;

        BSTNode(int data) {
            this.data = data;
        }
    }

    private BSTNode root;

    BSTImpl() {
        this.root = null;
    }

    public void insert(int data) {
        if(root == null) {
            root = new BSTNode(data);
            return;
        }

        insertUtil(data, root);
    }

    public boolean contains(int data) {
        return containsUtil(data, this.root);
    }

    public void printInorder() {
        printInorderUtil(root);
    }

    public void printLevelOrder() {
        Queue<BSTNode> bstNodeQueue = new LinkedList<>();

        bstNodeQueue.add(root);

        while(!bstNodeQueue.isEmpty()) {
            BSTNode node = bstNodeQueue.poll();

            if(node.left != null) bstNodeQueue.add(node.left);
            if(node.right != null) bstNodeQueue.add(node.right);

            System.out.println(node.data);
        }
    }

    public void delete(int data) {
        if(!contains(data)) return;

        root = deleteUtil(data, root);
    }

    private BSTNode deleteUtil(int data, BSTNode node) {
        if(node == null) return null;

        if(node.data > data) {
            node.left = deleteUtil(data, node.left);
        } else if(node.data < data) {
            node.right = deleteUtil(data, node.right);
        } else {
            if(node.left == null) return node.right;
            if(node.right == null) return node.left;

            BSTNode nextInorder = findNextInorder(node);

            int dataTemp = node.data;
            node.data = nextInorder.data;
            nextInorder.data = dataTemp;

            root.right = deleteUtil(dataTemp, node.right);
        }

        return node;
    }

    private BSTNode findNextInorder(BSTNode node) {
        BSTNode curr = node.right;

        while(curr.left != null) curr = curr.left;
        return curr;
    }

    private void printInorderUtil(BSTNode node) {
        if(node == null) return;

        printInorderUtil(node.left);
        System.out.println(node.data);
        printInorderUtil(node.right);
    }

    private void insertUtil(int data, BSTNode node) {
        if(node.data <= data) {
            if(node.right == null) {
                node.right = new BSTNode(data);
                return;
            }
            insertUtil(data, node.right);
        } else {
            if(node.left == null) {
                node.left = new BSTNode(data);
                return;
            }
            insertUtil(data, node.left);
        }
    }

    private boolean containsUtil(int data, BSTNode node) {
        if(node == null) return false;
        if(node.data == data) return true;

        if(node.data > data) return containsUtil(data, node.left);

        return containsUtil(data, node.right);
    }

    public static void main(String[] args) {
        BSTImpl bst = new BSTImpl();

        bst.insert(5);
        bst.insert(4);
        bst.insert(6);
        bst.insert(1);
        bst.delete(1);

        bst.printInorder();
    }
}
