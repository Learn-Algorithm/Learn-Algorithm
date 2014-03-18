# Splay Tree

## How to use

### Compile & Run

```shell
make all
```

### Clean up

```shell
make clean
```

## 与AVL Tree 比较

### 优点

1. 大量查询时，总查询时间相对较少
2. 分割与合并操作快速
3. 内存效率更好，因为不用存储平衡度信息
4. 实现相对简单

### 缺点

1. 单次查询时间复杂度无法保证 O(log n)
2. 无法在多线程环境中使用
