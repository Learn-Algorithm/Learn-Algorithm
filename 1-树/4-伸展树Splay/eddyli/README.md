## 伸展树 ##
参考了[这里](http://zh.wikipedia.org/wiki/%E4%BC%B8%E5%B1%95%E6%A0%91 "这里")的实现


其中最关键的操作就是splay函数

这个函数接受一个节点，并且把这个节点通过一系列的旋转转到根部
,在insert和find后调用splay，将对应的节点调整至根部即可


在splay函数中有一个关于双旋转的片段需要仔细考虑：

    else if( x->parent->left == x && x->parent->parent->left == x->parent ) {
		//这里首先要对x->parent->parent旋转
    	zig( x->parent->parent );
    	zig( x->parent );
    } else if( x->parent->right == x && x->parent->parent->right == x->parent ) {
    	zag( x->parent->parent );
    	zag( x->parent );
    } else if( x->parent->left == x && x->parent->parent->right == x->parent ) {
		//这里则首先要对x->parent旋转
    	zig( x->parent );
    	zag( x->parent );
    } else {
    	zag( x->parent );
    	zig( x->parent );
    }