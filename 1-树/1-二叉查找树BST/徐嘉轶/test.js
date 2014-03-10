bst = require("./bst");

asserts = function(funcs){
    funcs.forEach(function(func,i){
        if(func()){
            console.log("pass",i);
        }else{
            console.log("fail",i);
            console.log(func.toString());
        }
    });
}

var tree = bst.create([6,3,1,8,2,7,0]);

// before delete 8
//       6
//     3   8
//   1    7
// 0  2


// after delete 8
//       6
//     3   7
//   1
// 0  2

// after delete 1
//       6
//     3   7
//   2
// 0

function toList(tree){
    var list = [];
    tree.inOrder(function(node){
        list.push(node.value);
    });
    var result = list.join(",");
    return result;
}


asserts([function(){
    return toList(tree) == "0,1,2,3,6,7,8";
},function(){
    return tree.search(1);
},function(){
    return !tree.search(50);
},function(){
    tree.delete(8);
    return !tree.search(8);
},function(){
    return !tree.delete(50);
},function(){
    return toList(tree) == "0,1,2,3,6,7";
},function(){
    return tree.search(1);
},function(){
    tree.delete(1);
    return !tree.search(1);
},function(){
    return toList(tree) == "0,2,3,6,7";
}])