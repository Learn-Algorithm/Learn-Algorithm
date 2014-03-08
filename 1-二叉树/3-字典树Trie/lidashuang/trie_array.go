package main

import (
  "fmt"
)

const (
  MaxNum = 26 // a-z count
  Aval   = 97 // a ansi value
)

type TrieTreeNode struct {
  IsEnd bool
  Count int
  Key   rune
  Child [MaxNum]*TrieTreeNode
}

type TrieTree struct {
  Root *TrieTreeNode
}

func NewTrieTreeNode(key rune) *TrieTreeNode {
  return &TrieTreeNode{
    IsEnd: false,
    Count: 0,
    Key:   key,
  }
}

func NewTrieTree() *TrieTree {
  return &TrieTree{
    Root: NewTrieTreeNode(' '),
  }
}

func (tree *TrieTree) Insert(str string) {
  ptr := tree.Root
  for _, ch := range str {
    idx := int(ch) - Aval
    if ptr.Child[idx] == nil {
      ptr.Child[idx] = NewTrieTreeNode(ch)
    }
    ptr = ptr.Child[idx]
  }
  ptr.IsEnd = true
  ptr.Count++
}

func (tree *TrieTree) Search(str string) int {
  ptr := tree.Root
  for _, ch := range str {
    idx := int(ch) - Aval
    if ptr.Child[idx] == nil {
      return 0
    }
    ptr = ptr.Child[idx]
  }
  return ptr.Count
}

// todo
func (tree *TrieTree) Remove(str string) {
}

func main() {
  tree := NewTrieTree()
  var strs = []string{"amy", "ann", "ann", "baa", "baa"}
  for _, str := range strs {
    tree.Insert(str)
  }

  fmt.Printf("%d\n", tree.Search("ann")) // should 2
}
