let recursion = function(arr){
    if(arr.length === 1){
        return arr[0]
    } else{
        return recursion(arr.slice(1))
    }
}
console.log(recursion([1,2,3]))
