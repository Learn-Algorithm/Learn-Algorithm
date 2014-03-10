function Node(value){
    this.left = null;
    this.right = null;
    this.value = value;
}


Node.prototype = {
    "insert":function(value){
        if(value < this.value){
            if(this.left){
                this.left.insert(value);
            }else{
                this.left = new Node(value);
                this.left.parent = this;
            }
        }else if(value > this.value){
            if(this.right){
                this.right.insert(value);
            }else{
                this.right = new Node(value);
                this.right.parent = this;
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
        root.insert(value);
    });
    return root;
}