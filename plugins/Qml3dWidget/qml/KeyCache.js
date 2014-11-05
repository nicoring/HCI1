var cache = new Array();


function initCache(){
    cache = new Array();
}

function addKey(key){
    cache[cache.length] = key;
}

function setUpperCase(value){
    for (var i=0; i<cache.length; i++){
        cache[i].upperCase = value;
    }
}
