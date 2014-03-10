package algorithm;

public class AVLTree {
    private static class Node {
        Node left;
        Node right;
        int height;
        int data;
    }

    private int heigth(Node t) {
        if(t == null){
            return 0;
        }
        return t.height;
    }

    private Node rightRotate(Node a) {
        Node b = a.left;
        a.left = b.right;
        b.right = a;
        a.height = max(heigth(a.left), heigth(a.right));
        b.height = max(heigth(b.left), heigth(b.right));
        return b;
    }

    // RR
    private Node leftRotate(Node a) {
        Node b = a.right;
        a.right = b.left;
        b.left = a;
        a.height = max(heigth(a.left), heigth(a.right));
        b.height = max(heigth(b.left), heigth(b.right));
        return b;
    }

    //LR
   private  Node leftRightRotate(Node a){
        a.left = leftRotate(a.left);
        return rightRotate(a);
    }

    //RL
   private Node rightLeftRotate(Node a){
        a.right = rightRotate(a.right);
        return leftRotate(a);
    }

    //insert
   public Node insert(int data, Node t){
        if(t == null){
            t = newNode(data);
        }else if(data < t.data){
            t.left = insert(data, t.left);
            if(heigth(t.left) - heigth(t.right) == 2){
                if(data < t.left.data){
                    t = rightRotate(t);
                }else{
                    t = leftRightRotate(t);
                }
            }
        }else{
            t.right = insert(data, t.right);
            if(heigth(t.right) - heigth(t.left) == 2){
                if(data > t.right.data){
                    t = leftRotate(t);
                }else{
                    t = rightLeftRotate(t);
                }
            }
        }
        t.height = max(heigth(t.left), heigth(t.right));
        return t;
    }

    private Node newNode(int data){
        Node a = new Node();
        a.left = a.right = null;
        a.height = 0;
        a.data = data;
        return a;
    }
    private int max(int heigth, int heigth2) {

        return heigth > heigth2 ? heigth : heigth2;
    }

    public void travel(Node root) {
        Node node = root;
        if (node == null) {
            return;
        }
        travel(node.left);
        System.out.print(node.data + " ");
        travel(node.right);
    }

    public static void main(String[] args) {
        int[] a = {0, 1, 5, 3, 8, 9, 2,  7, 6, };
        Node root = null;
        AVLTree avl = new AVLTree();
        for(int b : a){
            root = avl.insert(b, root);
        }
        System.out.println(root);
        avl.travel(root);
    }
}