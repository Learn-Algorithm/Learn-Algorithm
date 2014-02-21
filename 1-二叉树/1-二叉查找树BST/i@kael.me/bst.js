'use strict';

if ( typeof module !== 'undefined' ) {
    module.exports = node;
}


function Node (key) {
    this.key = key;
}


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
            this.l.parent = this;
        }

    } else if ( this < value ) {
        if ( this.hasL() ) {
            this.l.insert(value)
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
    if ( value === this ) {
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


Node.prototype.del = function(first_argument) {
    
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

