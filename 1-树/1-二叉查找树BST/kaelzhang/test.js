'use strict';

var node = require('./bst');
var expect = require('chai').expect;

var input = [
                10,
        5,                  15,
    // 3 has l and r
    3, 
            // 7 only has l
  1,  4,    7,
                       // 13 only has 14
           6,          13,
                                 // 17 has nothing
                         14,     17 ];

function check (node) {
    var pass = true;

    pass = pass && ( !node.hasL() || node > node.l && check(node.l) );
    pass = pass && ( !node.hasR() || node < node.r && check(node.r) );

    return pass;
}


function clone (array) {
    return [].concat(array);
}


function asend (array) {
    return clone(array).sort(function (a, b) {
        return a - b;
    });
}


describe("Basic methods", function(){
    it("check bst: .create(), .insert()", function(){
        var tree = node().create(input);
        expect(check(tree)).to.equal(true);
    });

    it(".inOrder()", function(){
        var tree = node().create(input);
        expect(tree.inOrder()).to.deep.equal(asend(input));
    });

    it(".search()", function(){
        var tree = node().create(input);

        input.forEach(function (value) {
            expect(!tree.search(value)).to.equal(false);
        });
    });
});

// var ENUM = [
//     {
//         value: 3,
//         type: 'has both l and r'
//     },

//     {
//         value: 7,
//         type: 'only has l'
//     },

//     {
//         value: 13,
//         type: 'only has r'
//     },

//     {
//         value: 17,
//         type: 'has neither'
//     }
// ]

describe(".del(value)", function(){
    [3, 7, 13, 17].forEach(function (key) {
        it(".del(" + key + ")", function(){
            var tree = node().create(input);
            tree.del(key);
            expect(check(tree)).to.equal(true);
            expect(tree.inOrder().indexOf(key)).to.equal(-1);
        });
    });
});



