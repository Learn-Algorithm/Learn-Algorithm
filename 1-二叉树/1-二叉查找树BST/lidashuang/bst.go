package main

import (
	"fmt"
)

type Node struct {
	Key            int
	Lchild, Rchild *Node
}

func create(keys []int) *Node {
	var root *Node
	for _, v := range keys {
		root = insert(v, root)
	}
	return root
}

func insert(key int, root *Node) *Node {
	if root == nil {
		return &Node{key, nil, nil}
	}

	if key < root.Key {
		root.Lchild = insert(key, root.Lchild)
		return root
	} else {
		root.Rchild = insert(key, root.Rchild)
		return root
	}
}

func serarch(key int, root *Node) *Node {
	if root == nil {
		return nil
	}
	if key < root.Key {
		return serarch(key, root.Lchild)
	}
	if key > root.Key {
		return serarch(key, root.Rchild)
	}
	return root
}

func delete(key int, root *Node) {
	if root == nil {
		return
	}
	if key < root.Key {
		delete(key, root.Lchild)
		return
	}

	if key > root.Key {
		delete(key, root.Rchild)
		return
	}

	if key == root.Key {
		if root.Lchild == nil && root.Rchild == nil {
			root = nil
			return
		}
		if root.Lchild != nil && root.Rchild == nil {
			*root = *root.Lchild
			return
		}
		if root.Lchild == nil && root.Rchild != nil {
			*root = *root.Rchild
			return
		}

		if root.Lchild != nil && root.Rchild != nil {
			rchildMin := root.Rchild
			for rchildMin.Lchild != nil {
				rchildMin = rchildMin.Lchild
			}
			rchildMin.Lchild = root.Lchild
			*root = *rchildMin
			return
		}
	}
}

type action func(node *Node)

func inOrder(root *Node, action action) {
	if root == nil {
		return
	}
	inOrder(root.Lchild, action)
	action(root)
	inOrder(root.Rchild, action)
}

func main() {
	bst := create([]int{4, 2, 1, 3, 5, 6})
	fmt.Println("serarch:", serarch(3, bst).Key) // should equal 3
	fmt.Println("serarch:", serarch(4, bst).Key) // should equal 4
	fmt.Println("serarch:", serarch(6, bst).Key) // should equal 4

	// inOrder
	fmt.Println("Inorder:")
	inOrder(bst, func(node *Node) {
		fmt.Println(node.Key)
	}) // 123456

	delete(5, bst)

	fmt.Println("Inorder2: delete 5")
	inOrder(bst, func(node *Node) {
		fmt.Println(node.Key)
	}) //12346

	insert(5, bst)

	delete(6, bst)

	fmt.Println("Inorder3: delete 6")
	inOrder(bst, func(node *Node) {
		fmt.Println(node.Key)
	}) //12345

	insert(6, bst)

	delete(2, bst)
	fmt.Println("Inorder4: delete2")
	inOrder(bst, func(node *Node) {
		fmt.Println(node.Key)
	}) //13456
}
