# Windows运用AVL树对地址空间的管理

-----
32位的Windows系统中，进程在用户态可用的地址空间是低2G。随着进程不断的申请和释放内存，这个2G的地址空间，有的地址范围是保留状态，有的地址范围是提交状态（映射到了物理内存），有的地址范围是空闲的。Windows采用平衡二叉书把这些离散的地址范围管理起来。

见的平衡二叉树有红黑树和AVL树两种，其中红黑树应用更广，C#/Java/C++STL等若干数据结构内部都是用红黑树实现的，然而Windows这次选择了AVL树。根据维基百科，AVL树的最大高度是1.44 * log(N+2) - 0.33，红黑树的最大高度是2.00* log(N+1)。与红黑树相比，AVL树的插入删除操作更慢一些，但是查询操作更快。想必对进程地址空间的查询操作更频繁一些，所以AVL得以入选。

AVL树的节点结构是
```c
typedef struct _MMADDRESS_NODE { 
  ULONG_PTR StartingVpn; // 起始虚拟地址
  ULONG_PTR EndingVpn; // 终止虚拟地址
  struct _MMADDRESS_NODE *Parent; 
  struct _MMADDRESS_NODE *LeftChild; 
  struct _MMADDRESS_NODE *RightChild; 
} MMADDRESS_NODE, *PMMADDRESS_NODE; 
```
AVL树的根节点保存在进程内核对象_EProcess中。_EProcess的结构没有出现在文档中，但是我们可以通过windbg获取。在Windows 2003中，用windbg获取如下输出：

```shell
kd> dt _EProcess 
nt!_EPROCESS 
+0x000 Pcb : _KPROCESS 
+0x078 ProcessLock : _EX_PUSH_LOCK 
+0x080 CreateTime : _LARGE_INTEGER 
+0x088 ExitTime : _LARGE_INTEGER
 …… 
+0x24c PriorityClass : UChar 
+0x250 VadRoot : _MM_AVL_TABLE 
+0x270 Cookie : Uint4B 
```

上图中偏移量为0x250处的VadRoot字段保存了AVL输根节点所在的地址。因此，在驱动程序中，通过以下代码可以获取当前进程的AVL树的根节点地址。

```c
PMMADDRESS_NODE ZsaGetVmRoot(){
  char * pEProcess = (char*)PsGetCurrentProcess(); 
  char * avlRoot = pEProcess + 0x250; 
  char * p_MM_AVL_TABLE = avlRoot; 
  return (PMMADDRESS_NODE) p_MM_AVL_TABLE;
 } 
```

既然获得了根地址，则可以对二叉树进行遍历，打印出整个数据结构。以下是某个测试进程在进行了1024*1024次new分配后，AVL树的内容。可以看到，树基本是平衡的。

 
0,0

├─────N

└─────280,2b3

            ├─────150,24f

            │          ├─────130,134

            │          │          ├─────20,20

            │          │          │          ├─────10,10

            │          │          │          └─────30,12f

            │          │          └─────140,140

            │          └─────260,275

            │                      ├─────250,25f

            │                      └─────N

            └─────10200,10372

                        ├─────400,502

                        │          ├─────310,315

                        │          │          ├─────2c0,300

                        │          │          └─────370,37f

                        │          │                      ├─────320,360

                        │          │                      └─────380,382

                        │          └─────c10,140f

                        │                      ├─────610,80f

                        │                      │          ├─────510,60f

                        │                      │          └─────810,c0f

                        │                      └─────2410,440f

                        │                                  ├─────1410,240f

                        │                                  └─────4410,840f

                        └─────7c930,7c9ff

                                   ├─────10540,1853f

                                   │          ├─────10480,10536

                                   │          └─────7c800,7c92a

                                   │                      ├─────18540,2853f

                                   │                      └─────N

                                   └─────7ffdd,7ffdd

                                               ├─────7ffa0,7ffd2

                                               │          ├─────7f6f0,7f7ef

                                               │          └─────N

                                                └─────7ffde,7ffde


