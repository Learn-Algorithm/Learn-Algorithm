package main

import (
  "fmt"
)

type TrieTreeNode struct {
  IsEnd bool
  Count int
  Key   rune

  Next, Children *TrieTreeNode
}

type TrieTree struct {
  Root *TrieTreeNode
}

func NewTrieTreeNode(key rune) *TrieTreeNode {
  node := &TrieTreeNode{
    IsEnd:    false,
    Count:    0,
    Key:      key,
    Next:     nil,
    Children: nil,
  }
  return node
}

func NewTrieTree() *TrieTree {
  return &TrieTree{
    Root: NewTrieTreeNode('z'),
  }
}

/*
              .
      /       |      \
     a        e       r
   /   \      |       |
  m     n     m       o
  |     |     |     /   \
  y     n     m    b     g
  |     |     |    |     |
\0 56 \0 15   a  \0 27   e
              |          |
            \0 30        r
                         |
                       \0 52


  |
  a --------- e ----- r
  |           |       |
  m --- n     m       o
  |     |     |       |
  y     n     m       b ----- g
  |     |     |       |       |
\0 56 \0 15   a     \0 27     e
              |               |
            \0 30             r
                              |
                            \0 52
*/

func (tree *TrieTree) Insert(str string) {
  ptr := tree.Root

  for _, ch := range str {
    if ptr.Children == nil {
      ptr.Children = NewTrieTreeNode(ch)
      ptr = ptr.Children
    } else {
      if ptr.Children.Key != ch {
        // 有兄弟结点并且相等
        if ptr.Children.Next != nil && ptr.Children.Next.Key == ch {
          ptr = ptr.Children.Next
        } else {
          // 创建兄弟节点
          ptr.Children.Next = NewTrieTreeNode(ch)
          ptr = ptr.Children.Next
        }
      } else {
        // 相等
        ptr = ptr.Children
      }
    }
  }

  ptr.IsEnd = true
  ptr.Count++
}

// 查询一个单词，返回单词个数
func (tree *TrieTree) SearchWord(str string) int {
  ptr := tree.Root
  var noWord = 0

  for _, ch := range str {
    if ptr.Children == nil {
      return noWord
    }

    if ptr.Children.Key == ch {
      ptr = ptr.Children
      continue
    }

    // 判断next
    if ptr.Children.Next != nil && ptr.Children.Next.Key == ch {
      ptr = ptr.Children.Next
      continue
    }
    return noWord
  }
  return ptr.Count
}

// todo
func (tree *TrieTree) RemoveWord(str string) {
}

func main() {
  tree := NewTrieTree()

  var strs = []string{"amy", "ann", "ann", "baa", "baa"}
  for _, str := range strs {
    tree.Insert(str)
  }

  ptr := tree.Root

  fmt.Printf("%c\n", ptr.Children.Children.Next.Children.Key)   // should n
  fmt.Printf("%c\n", ptr.Children.Next.Key)                     // should b
  fmt.Printf("%c\n", ptr.Children.Next.Children.Key)            // should a
  fmt.Printf("%c\n", ptr.Children.Next.Children.Children.Key)   // should a
  fmt.Printf("%d\n", ptr.Children.Next.Children.Children.Count) // should 2
  fmt.Printf("%d\n", ptr.Children.Children.Next.Children.Count) // should 2

  tree.Insert("ann")

  // test search
  fmt.Println("====test search=====")
  fmt.Printf("%d\n", tree.SearchWord("ann")) // should 3
  fmt.Printf("%d\n", tree.SearchWord("baa")) // should 2
  fmt.Printf("%d\n", tree.SearchWord("amy")) // should 1

  // other test
  /*
  	var strs = []string{"amy", "amy", "amy", "ama"}
  	for _, str := range strs {
  		tree.Insert(str)
  	}
  	ptr := tree.Root
  	fmt.Printf("%d\n", ptr.Children.Children.Children.Count)      // should 3
  	fmt.Printf("%d\n", ptr.Children.Children.Children.Next.Count) // should 3
  */
}
