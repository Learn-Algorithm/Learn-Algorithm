function Node(value){
    this.left = null;
    this.right = null;
    this.value = value;
    this.parent = null;
    this.height = 0;
}


// 1(0)
// =>
//   1(1)
//     8(0)
// =>
//
//   1
//     8
//   6
//
// => RL
//    6
// 1     8


function toList(tree){
    var list = [];
    tree.inOrder(function(node){
        list.push(node.value);
    });
    var result = list.join(",");
    return result;
}

function noLeaf(node){
    return node === null || node.left === null && node.right === null;
}

function height(node){
    return node ? node.height : -1;
}

function calHeight(node){
    return Math.max(height(node.left),height(node.right)) + 1;
}


function balenceFact(node){
    return height(node.left) - height(node.right);
}

function adjust(value, node){
    var bf;
    console.log("inserting %s",value);
    while(node){
        if(!node.parent){
            break;y
        }else{
            node = node.parent;
        }
        node.height = calHeight(node);
        bf = balenceFact(node);
        if(Math.abs(bf) > 1){
            // right of right sub tree, do RR
            if(value > node.value && value > node.right.value){
                console.log("ll");
                node = leftRotate(node);
            // left of right sub tree, do RL
            }else if(value > node.value && value < node.right.value){
                console.log("rl");
                node = rightLeftRotate(node);
            // right of left sub tree, do LR
            }else if(value < node.value && value > node.left.value){
                console.log("lr");
                node = leftRightRotate(node);
            // left of left sub tree, do LL
            }else if(value < node.value && node < node.left.value){
                console.log("rr");
                node = rightRotate(node);
            }
        }
    }
    return node;
}

function connectParent(node,pivot){
    if(node.parent.right == node){
        node.parent.right = pivot;
    }else{
        node.parent.left = pivot;
    }
}

//  1
//    6
//      8
//
// => RL
//    6
// 1     8


function leftRotate(node){
    var pivot = node.right;
    if(node.parent){
        connectParent(node,pivot);
    }
    pivot.parent = node.parent;

    // 特殊情况
    if(pivot.left){
        node.right = pivot.left;
        pivot.left.parent = node;
    }else{
        node.right = null;
    }

    node.parent = pivot;
    pivot.left = node;

    node.height = calHeight(node);
    pivot.height = calHeight(pivot);
    return pivot;
}

//     8           6
//   6      =>  1     8
// 1
//          AND
//   1             1
//     8    =>       6
//   6                 8
function rightRotate(node){
    var pivot = node.left;
    if(node.parent){
        connectParent(node,pivot);
    }
    pivot.parent = node.parent;

    // 特殊情况
    if(pivot.right){
        node.left = pivot.right;
        pivot.right.parent = node;
    }else{
        node.left = null;
    }

    node.parent = pivot;
    pivot.right = node;


    node.height = calHeight(node);
    pivot.height = calHeight(pivot);
    return pivot;
}

function rightLeftRotate(node){
    node.right = rightRotate(node.right);
    var n = leftRotate(node);
    return n;
}

function leftRightRotate(node){
    node.left = leftRotate(node.left);
    return rightRotate(node);
}

function getRoot(node){
    while(node){
        if(!node.parent){
            break;
        }
        node = node.parent;
    }
    return node;
}


Node.prototype = {
    "insert":function(value){
        if(value < this.value){
            if(this.left){
                return this.left.insert(value);
            }else{
                this.left = new Node(value);
                this.left.parent = this;
                return adjust(value,this.left);
            }
        }else if(value > this.value){
            if(this.right){
                return this.right.insert(value);
            }else{
                this.right = new Node(value);
                this.right.parent = this;
                return adjust(value,this.right);
            }
        }
    },
    "search":function(value){
        if(value === this.value){
            return true;
        }else if(value < this.value){
            return this.left ? this.left.search(value) : false;
        }else{
            return this.right ? this.right.search(value) : false;
        }
    },
    "delete":function(value){
        if(value === this.value){
            this.remove();
        }else if(this.left === null && this.right === null){
            return false;
        }else if(value < this.value){
            this.left && this.left.delete(value);
        }else{
            this.right && this.right.delete(value);
        }
    },
    "inOrder":function(cb){
        this.left && this.left.inOrder(cb);
        cb && cb(this);
        this.right && this.right.inOrder(cb);
    },
    "remove":function(){
        if(this.left === null && this.right === null){
            if(this.parent.left == this){
                this.parent.left = null;
            }else{
                this.parent.right = null;
            }
        }else if(this.left === null && this.right){
            this.replace(this.right);
        }else if(this.right === null && this.left){
            this.replace(this.left);
        }else{
            var current = this.right;
            while(current.left){
                current = current.left;
                if(current.left === null){
                    break;
                }
            }

            this.value = current.value;
            current.remove();
        }
    },
    "replace":function(node){
        if(this.parent.right == this){
            this.parent.right = node;
            node.parent = this.parent;
        }else if(this.parent.left == this){
            this.parent.left = node;
            node.parent = this.parent;
        }
    }
}
exports.create = function (values) {
    var root = new Node(values[0]);
    values.slice(1).forEach(function(value,i){
        root = root.insert(value);
    });
    return root;
}



// var tree = create([1,8,6,2,3,5,7,9]);
// console.log(tree);


// function toList(tree){
//     var list = [];
//     tree.inOrder(function(node){
//         list.push(node.value);
//     });
//     var result = list.join(",");
//     console.log(result);
//     return result;
// }

// toList(tree);