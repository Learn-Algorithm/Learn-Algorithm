
# AVL Tree

## How to use

#### Compile & Run

```shell
make && ./avl
```

#### Clean up

```shell
make clean
```

## 遇到的坑

在删除操作中，对满足条件的子树，只需要重新计算高度，不需要做任何操作。另外，在代码实现时，需要保持思路清晰，不然容易乱。好在操作是完全对称的，只要搞定了一种情况，另外一种只需要完全反向即可。

## 实际应用

AVL Tree 和 BST
的使用方法完全相同，只不过对于search的性能好很多，因此实用很多。找到一篇[论文][1]是将其应用于替换STM
(software transactional memory) 中的 concurrent skip lists, 很有意思。

[1]: http://ppl.stanford.edu/papers/ppopp207-bronson.pdf "A Practical Concurrent Binary Search Tree"
