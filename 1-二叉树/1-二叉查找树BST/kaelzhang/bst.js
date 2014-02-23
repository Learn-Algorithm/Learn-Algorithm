'use strict';

if ( typeof module !== 'undefined' ) {
    module.exports = node;
}


function Node (key) {
    this.key = key;
}


// Get the top level of the tree
Node.prototype.topLevel = function() {
    return this.parent
        ? this.parent.topLevel()
        : this;
};


Node.prototype.hasL = function() {
    return 'l' in this;
};


Node.prototype.hasR = function() {
    return 'r' in this;
};


Node.prototype.valueOf = function() {
    return this.key;
};


// initialize bst node
Node.prototype.create = function(values) {
    if ( !Array.isArray(values) ) {
        return this;
    }

    values.forEach(function (value, i) {
        if ( i === 0 ) {
            this.key = value;
        } else {
            this.insert(value);
        }

    }, this);

    return this;
};


Node.prototype.insert = function(value) {
    if ( value > this ) {
        if ( this.hasR() ) {
            this.r.insert(value);
        } else {
            this.r = node(value);
            this.r.parent = this;
        }

    } else if ( value < this ) {
        if ( this.hasL() ) {
            this.l.insert(value);
        } else {
            this.l = node(value);
            this.l.parent = this;
        }
    }

    return this;
};


// @returns
// - {Node} if match found
// - false if no match found
Node.prototype.search = function(value) {
    if ( value === this.valueOf() ) {
        return this;
    }

    if ( value > this ) {
        if ( this.hasR() ) {
            return this.r.search(value);
        } else {
            return false;
        }

    } else {
        if ( this.hasL() ) {
            return this.l.search(value);
        } else {
            return false;
        }
    }
};


// @returns
// - false: fail to delete
// - {Node}: means the current node is deleted, 
//      and returns the new node who replaced the node
//      if there is one
// - true: other situations
Node.prototype.del = function(value) {
    if ( this.valueOf() === value ) {
        return this._remove();
    }

    if ( value > this ) {
        if ( this.hasR() ) {
            return !!this.r.del(value);
        } else {
            return false;
        }
    
    } else {
        if ( this.hasL() ) {
            return !!this.l.del(value);
        } else {
            return false;
        }
    }
    
};


// Remove itself from the mother tree
Node.prototype._remove = function() {
    var parent = this.parent;
    var l = this.l;
    var r = this.r;

    // leaf node
    if ( !this.hasL() && !this.hasR() ) {
        if ( parent.l === this ) {
            delete parent.l;
        } else {
            delete parent.r;
        }

        delete this.parent;
        return true;

    // only has left sub-tree
    } else if ( this.hasL() ) {
        delete this.l;
        return this._replace(l);

    // only has right sub-tree
    } else if ( this.hasR() ) {
        delete this.r;
        return this._replace(r);

    } else {
        var current = l;

        while (current = current.r){
            if ( !current.hasR() ) {
                break;
            }
        }

        current.r = r;
        r.parent = current;

        delete this.r;
        delete this.l;
        return this._replace(l);
    }
};


// Replace itself with another node
Node.prototype._replace = function(node) {
    var parent = this.parent;

    if ( parent.l === this ) {
        parent.l = node;
    } else {
        parent.r = node;
    }

    node.parent = parent;

    return node;
};


// @returns {Array}
Node.prototype.inOrder = function(host) {
    if ( !host ) {
        host = [];
    }

    if ( this.hasL() ) {
        this.l.inOrder(host);
    }

    host.push(this.valueOf());

    if ( this.hasR() ) {
        this.r.inOrder(host);
    }

    return host;
};


function node (key){
    return new Node(key);
}

node.Node = Node;

