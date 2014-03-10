function TreeNode(value){
    this.value = value;
    return this;
}

TreeNode.prototype = {
    preOrder : function(cb){
        // abcdefg
        cb(this);
        this.left && this.left.preOrder(cb);
        this.right && this.right.preOrder(cb);
    },
    inOrder: function(cb){
        // cbdafeg
        this.left && this.left.inOrder(cb);
        cb(this);
        this.right && this.right.inOrder(cb);
    },
    postOrder: function(cb){
        this.left && this.left.postOrder(cb);
        this.right && this.right.postOrder(cb);
        cb(this);
    },
    levelOrder: function(cb){
        var tree = this;
        var current = null;
        var list = [tree];
        while(list.length){
            var len = list.length;
            current = list[0];
            current.left && list.push(current.left);
            current.right && list.push(current.right);
            cb(list.shift());
        }
    }
}


function handler(tree){
    process.stdout.write(tree.value);
}


var tree = new TreeNode("a");
tree.left = new TreeNode("b");
tree.left.left = new TreeNode("c");
tree.left.right = new TreeNode("d");
tree.right = new TreeNode("e");
tree.right.left = new TreeNode("f");
tree.right.right = new TreeNode("g");


tree.preOrder(handler);
console.log();
tree.inOrder(handler);
console.log();
tree.postOrder(handler);
console.log();
tree.levelOrder(handler);