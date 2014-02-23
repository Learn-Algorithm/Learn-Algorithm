// play.golang http://play.golang.org/p/t3XsHzgFAH

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

func min(root *Node) *Node {
	if root.Lchild == nil {
		return root
	}
	return min(root.Lchild)
}

func deleteMin(root *Node) *Node {
	if root.Lchild == nil {
		return root.Rchild
	}
	root.Lchild = deleteMin(root.Lchild)
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
			rchildMin := min(root.Rchild)
			root.Rchild = deleteMin(root.Rchild)
			root.Key = rchildMin.Key
			return
		}
	}
	return
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
	bst := create([]int{5, 4, 2, 1, 3, 6})
	fmt.Println("serarch:", serarch(3, bst).Key) // should equal 3
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

	//			7
	//		3		8
	//	2		5		9
	//1		4		6		10
	bst1 := create([]int{7, 3, 8, 2, 5, 9, 1, 4, 6, 10})
	delete(3, bst1)
	fmt.Println("bst1 inOrder:")
	inOrder(bst1, func(node *Node) {
		fmt.Println(node.Key)
	})
}

