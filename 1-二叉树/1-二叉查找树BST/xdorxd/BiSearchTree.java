/**
 * Created with IntelliJ IDEA.
 * User: xdorxd
 * Date: 14-2-23
 * Time: 下午3:10
 */

public class BiSearchTree {
    private Node root;
    private int size = 0;

    public BiSearchTree() {

    }

    public BiSearchTree(int value) {
        this.root = new Node(value);
        this.size = 1;
    }

    public Node getRoot() {
        return root;
    }

    //构建
    public void create(int[] data) {
        if (data != null) {
            for (int i : data) {
                insert(i);
            }
        }
    }

    //插入
    public void insert(int data) {
        if (root == null) {
            root = new Node(data);
        } else {
            Node curNode = root;
            Node parentNode;
            while (true) {
                parentNode = curNode;
                if (data < curNode.data) {
                    curNode = curNode.left;
                    if (curNode == null) {
                        parentNode.left = new Node(data);
                        parentNode.left.leftOrRight = -1;
                        break;
                    }
                } else {
                    curNode = curNode.right;
                    if (curNode == null) {
                        parentNode.right = new Node(data);
                        parentNode.right.leftOrRight = 1;
                        break;
                    }
                }
            }
        }
        ++size;
    }

    public Node search(int value) {
        Node node = root;
        while (node.data != value) {
            if (value < node.data) {
                node = node.left;
            } else {
                node = node.right;
            }
            if (node == null) {
                node = null;
            }
        }
        return node;
    }


    public boolean delete(int value) {
        boolean flag = false;
        Node node = search(value);
        Node parent = parent(value);
        if (node != null) {
            if (node.equals(root)) {
                root = null;
            }
            if (node.left == null && node.right == null) {
                if (node.leftOrRight == 1) {
                    node = null;
                    parent.right = null;
                }
                if (node.leftOrRight == -1) {
                    node = null;
                    parent.left = null;
                }
            } else if (node.left != null
                    && node.right != null) {
                Node successor = successor(node);
                if (node.leftOrRight == -1) {
                    parent.left = successor;
                    parent.left.leftOrRight = -1;
                }
                if (node.leftOrRight == 1) {
                    parent.right = successor;
                    parent.right.leftOrRight = 1;
                }
                successor.left = node.left;
            } else {
                if (node.left != null) {
                    if (node.leftOrRight == 1) {
                        parent.right = node.left;
                    }
                    if (node.leftOrRight == -1) {
                        parent.left = node.left;
                    }
                }
                if (node.right != null) {
                    if (node.leftOrRight == 1) {
                        parent.right = node.right;
                    }
                    if (node.leftOrRight == -1) {
                        parent.left = node.right;
                    }
                }
                node = null;
            }
            flag = true;
            --size;
        }
        return flag;
    }
    public void inOrder() {
        inOrder(this.root);
    }

    private void inOrder(Node node) {
        if (node != null) {
            inOrder(node.left);
            System.out.print(node.data + " ");
            inOrder(node.right);
        }
    }

    private Node parent(int data) {
        Node parent = null;
        Node node = root;
        while (node.data != data) {
            parent = node;
            if (data < node.data) {
                node = node.left;
            } else {
                node = node.right;
            }
            if (node == null) {
                node = null;
                parent = null;
            }
        }
        return parent;
    }

    private Node successor(Node delNode) {
        Node parent = delNode;
        Node successor = delNode;
        Node curNode = delNode.right;

        while (curNode != null) {
            parent = successor;
            successor = curNode;
            curNode = curNode.left;
        }
        if (!successor.equals(delNode.right)) {
            parent.left = successor.right;
            successor.right = delNode.right;
        }
        return successor;
    }

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public class Node {
        int leftOrRight = 0;
        int data;
        Node left;
        Node right;

        public Node(int data) {
            this.data = data;
        }

    }

    public static void main(String[] args) {
        int[] A = {3,7,13,14,17,32};

        System.out.println("打印出数组A中的元素");
        for(int i=0;i<A.length;i++){
            System.out.print(A[i]+",");
        }
        System.out.println();

        BiSearchTree bst = new BiSearchTree();
        System.out.println("用数组A构建二叉树:");
        bst.create(A);

        System.out.println("中序遍历二叉树:");
        bst.inOrder();
        System.out.println();

        System.out.println("插入新值8:");
        bst.insert(8);

        System.out.println("中序遍历二叉树:");
        bst.inOrder();
        System.out.println();

        System.out.println("搜索二叉树14:");
		try{
			Node searchNode = bst.search(15);
			System.out.println("查找成功");
		}catch(Exception e){
			System.out.println("查找失败，不包含此值");
		}

        System.out.println("删除值13:");
        bst.delete(13);

        System.out.println("中序遍历二叉树:");
        bst.inOrder();
    }

}