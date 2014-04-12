    package com.kiritor;  
      
    /**伸展树 
     * @author caven*/  
    public class SplayTree {  
      
        static class BinaryNode {  
            // Constructors  
            BinaryNode(Comparable theElement) {  
                this(theElement, null, null);  
            }  
      
            BinaryNode(Comparable theElement, BinaryNode lt, BinaryNode rt) {  
                element = theElement;  
                left = lt;  
                right = rt;  
            }  
            Comparable element;  
            BinaryNode left;   
            BinaryNode right;  
        }  
      
        private BinaryNode root;  
        private static BinaryNode nullNode;  
        static   
        {  
            nullNode = new BinaryNode(null);  
            nullNode.left = nullNode.right = nullNode;  
        }  
      
        private static BinaryNode newNode = null; //用于插入的操作  
        private static BinaryNode header = new BinaryNode(null);//用于调整操作   
          
        public SplayTree() {  
            root = nullNode;  
        }  
        public void insert(Comparable x) {  
            if (newNode == null)  
                newNode = new BinaryNode(x);//新建一个结点  
            //根结点为空则新建的结点作为根结点  
            if (root == nullNode) {  
                newNode.left = newNode.right = nullNode;  
                root = newNode;  
            } else {  
                root = splay(x, root);//调整  
                if (x.compareTo(root.element) < 0) {  
                    newNode.left = root.left;  
                    newNode.right = root;  
                    root.left = nullNode;  
                    root = newNode;  
                } else if (x.compareTo(root.element) > 0) {  
                    newNode.right = root.right;  
                    newNode.left = root;  
                    root.right = nullNode;  
                    root = newNode;  
                } else  
                    return;  
            }  
            newNode = null;   
        }  
      
        public void remove(Comparable x) {  
            BinaryNode newTree;  
            root = splay(x, root);  
            if (root.element.compareTo(x) != 0)  
                return; // Item not found; do nothing  
            if (root.left == nullNode)  
                newTree = root.right;  
            else {  
                newTree = root.left;  
                newTree = splay(x, newTree);  
                newTree.right = root.right;  
            }  
            root = newTree;  
        }  
        public Comparable findMin() {  
            if (isEmpty())  
                return null;  
            BinaryNode ptr = root;  
            while (ptr.left != nullNode)  
                ptr = ptr.left;  
            root = splay(ptr.element, root);  
            return ptr.element;  
        }  
      
        public Comparable findMax() {  
            if (isEmpty())  
                return null;  
            BinaryNode ptr = root;  
            while (ptr.right != nullNode)  
                ptr = ptr.right;  
            root = splay(ptr.element, root);  
            return ptr.element;  
        }  
        public Comparable find(Comparable x) {  
            root = splay(x, root);  
            if (root.element.compareTo(x) != 0)  
                return null;  
            return root.element;  
        }  
        public void makeEmpty() {  
            root = nullNode;  
        }  
      
        public boolean isEmpty() {  
            return root == nullNode;  
        }  
        public void printTree() {  
            if (isEmpty())  
                System.out.print("Empty tree  ");  
            else  
                printTree(root);  
        }  
      
        private BinaryNode splay(Comparable x, BinaryNode t) {  
            BinaryNode leftTreeMax, rightTreeMin;  
            header.left = header.right = nullNode;  
            leftTreeMax = rightTreeMin = header;  
            nullNode.element = x;   
            for (;;)  
                if (x.compareTo(t.element) < 0) {  
                    if (x.compareTo(t.left.element) < 0)  
                        t = rotateWithLeftChild(t);  
                    if (t.left == nullNode)  
                        break;  
                    rightTreeMin.left = t;  
                    rightTreeMin = t;  
                    t = t.left;  
                } else if (x.compareTo(t.element) > 0) {  
                    if (x.compareTo(t.right.element) > 0)  
                        t = rotateWithRightChild(t);  
                    if (t.right == nullNode)  
                        break;  
                    // Link Left  
                    leftTreeMax.right = t;  
                    leftTreeMax = t;  
                    t = t.right;  
                } else  
                    break;  
      
            leftTreeMax.right = t.left;  
            rightTreeMin.left = t.right;  
            t.left = header.right;  
            t.right = header.left;  
            return t;  
        }  
      
          
        static BinaryNode rotateWithLeftChild(BinaryNode k2) {  
            BinaryNode k1 = k2.left;  
            k2.left = k1.right;  
            k1.right = k2;  
            return k1;  
        }  
      
          
        static BinaryNode rotateWithRightChild(BinaryNode k1) {  
            BinaryNode k2 = k1.right;  
            k1.right = k2.left;  
            k2.left = k1;  
            return k2;  
        }  
      
        private void printTree(BinaryNode t) {  
            if (t != t.left) {  
                printTree(t.left);  
                System.out.print(t.element.toString()+"  ");  
                printTree(t.right);  
            }  
        }  
      
        public static void main(String[] args) {  
            SplayTree tree = new SplayTree();  
            tree.insert(12);  
            tree.insert(8);  
            tree.insert(2);  
            tree.insert(4);  
            tree.insert(14);  
            tree.insert(16);  
            tree.insert(6);  
            tree.insert(1);  
            tree.insert(11);  
            tree.remove(8);   
            System.out.println("被查找的节点:" + tree.find(11));  
            System.out.println("此时的根:" + tree.root.element);  
            System.out.println("被查找的节点:" + tree.find(12));  
            System.out.println("此时的根:" + tree.root.element);  
            System.out.println("被查找的节点:" + tree.find(11));  
            System.out.println("此时的根:" + tree.root.element);  
            System.out.println("伸展树值情况:");  
            tree.printTree();   
      
        }  
    }  