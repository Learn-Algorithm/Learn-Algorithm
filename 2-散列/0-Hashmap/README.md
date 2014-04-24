#Hashmap

-----------------------------

Hashmap是一种高效的数据存储结构。它结合了链表和数组各自的优点，既可以快速查找，又便于插入和删除操作。


## 任务：

实现一个Hashmap类，为便于测评，我们将key的类型固定为string， value的类型固定为int

用户可以使用的操作：

```cpp
1. void insert (string key， int value)  // 插入一个key-value对，如果key已经存在，则插入无效
2. int find (string key)                 // 通过key查找value， 如果key不存在，返回0
3. print(Hashmap map)                    // 打印整个map，每一行为一个key value（用空格隔开）
```

## 测评：

通过已经给出的createFile.cpp文件，会生成一个2GB大小的文件（inputfile.txt），该文件每一行是一个单词（实际是随机生成的一个字符串，单词会重复出现）
生成的过程时间比较长，需要耐心等待。（可以自己修改MAX的大小进行小规模测试）

通过自己写的Hashmap进行单词统计，即每一个单词出现的次数，然后打印最终结果和所用时间。
看看谁的算法能最快完成2GB文件的单词统计任务！

用Java的Hashmap和C++11的unordermap在我的laptop上的测试结果分别是

Java：105s
C++：83s






