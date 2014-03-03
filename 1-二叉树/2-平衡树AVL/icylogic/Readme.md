## AVL树的使用情景

AVL 树插入效率并不高, 因此实际使用中更多见 RB 树. 我找到 AVL 的实际应用有两例, 都是应用于 Windows 的

### Windows 虚拟内存管理

>In order to conserve memory and enhance performance, Windows uses a lazy evaluation algorithm in which a PTE is not actually created until the reserved or committed memory is First accessed. This method significantly improves per-formance for processes that allocate large amounts of memory which may only be scarcely accessed. In order to support the lazy evaluation algorithm, Windows needs to keep track of the memory that has not yet been accessed (and for which PTEs have not yet been created). As such, each process maintains a set of data structures known as virtual address descriptors (VADs). VADs are structured in self-balancing AVL trees and hold all the information on the memory ranges allocated in a process, necessary to set up PTEs correctly. This includes information such as the page protection, whether memory has been committed, pointers to associated File objects in memory mapped Files, and so on. 

![AVL for VAD][AVL for VAD]

### 存储文件系统相关信息
[RTL_AVL_TABLE structure][RTL_AVL_TABLE structure]
[RtlInitializeGenericTableAvl routine][RtlInitializeGenericTableAvl routine]

## 算法问题

暂无

[AVL for VAD]: http://icylogic.qiniudn.com/image/Learn-Algorithm/AVL%20for%20VAD.png
[RTL_AVL_TABLE structure]: http://msdn.microsoft.com/en-us/library/windows/hardware/ff553327(v=vs.85).aspx
[RtlInitializeGenericTableAvl routine]: http://msdn.microsoft.com/en-us/library/windows/hardware/hh406465(v=vs.85).aspx
