// run online: http://play.golang.org/p/an7CpQZ9nZ

package main

import (
	"fmt"
)

type avlNode struct {
	Key            int
	Height         int
	Lchild, Rchild *avlNode
}

func leftRotate(root *avlNode) *avlNode {
	node := root.Rchild
	// fmt.Println(node.Key)
	root.Rchild = node.Lchild
	node.Lchild = root

	root.Height = max(height(root.Lchild), height(root.Rchild)) + 1
	node.Height = max(height(node.Rchild), height(node.Lchild)) + 1
	return node
}

func leftRigthRotate(root *avlNode) *avlNode {
	root.Lchild = leftRotate(root.Lchild)
	root = rightRotate(root)
	return  root
}

func rightRotate(root *avlNode) *avlNode {
	node := root.Lchild
	root.Lchild = node.Rchild
	node.Rchild = root
	root.Height = max(height(root.Lchild), height(root.Rchild)) + 1
	node.Height = max(height(node.Lchild), height(node.Rchild)) + 1
	return node
}

func rightLeftRotate(root *avlNode) *avlNode {
	root.Rchild = rightRotate(root.Rchild)
	root = leftRotate(root)
	return  root
}

func height(root *avlNode) int {
	if root != nil {
		return root.Height
	}
	return -1
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func insert(root *avlNode, key int) *avlNode {
	if root == nil {
		root = &avlNode{key, 0, nil, nil}
		root.Height = max(height(root.Lchild), height(root.Rchild)) + 1
		return root
	} 

	if key < root.Key {
		root.Lchild = insert(root.Lchild, key)
		if height(root.Lchild)-height(root.Rchild) == 2 {
			if key < root.Lchild.Key {
				root = rightRotate(root) // 左左
			} else {
				root = leftRigthRotate(root) // 左右
			}
		}
	} 

	if key > root.Key {
		root.Rchild = insert(root.Rchild, key)
		if height(root.Rchild)-height(root.Lchild) == 2 {
			if key > root.Rchild.Key {
				root = leftRotate(root) // 右右
			} else {
				root = rightLeftRotate(root) // 右左
			}
		}
	}

	root.Height = max(height(root.Lchild), height(root.Rchild)) + 1
	return root
}


type action func(node *avlNode)

func inOrder(root *avlNode, action action) {
	if root == nil {
		return
	}

	inOrder(root.Lchild, action)
	action(root)
	inOrder(root.Rchild, action)
}

func main() {
	var root *avlNode
	keys := []int{2, 6, 1, 3, 5, 7, 16, 15, 14, 13, 12, 11, 8, 9, 10}
	for _, key := range keys {
		root = insert(root, key)
	}

	inOrder(root, func(node *avlNode) {
		fmt.Println(node.Key, node.Height)
	})
}
