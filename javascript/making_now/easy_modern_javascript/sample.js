var pmsg="";
var message="bye";
switch(message){
	case "hello": pmsg="Hello!!"; break;
	case "bye":   pmsg="Bye!"; break;
	default:      pmsg="I don't know ...."; break;
}


var total=0;
for(var i=0;i<100;i++){
	total+=i;
}
//alert("合計"+total);
//alert("外部のファイルのjavascriptですよ。");

//list 2-11
var ritsu=0.05;
var getTax =function(val){
	return val* ritsu;
}
var price =15000;
ritsu =0.1;
var tax = getTax(price);
//alert("金額："+price+"税額："+tax);

//list2-13
var arr=[98,82,70,86,53];
var total =0;
for(var i =0; i< arr.length; i++){
	total+= arr[i];
}
//alert(total);


//list2-15
var arr={"a":98,"b":82,"c":70,"d":86,"e":53}
arr["sum"]=function(){
var total;
total+=arr["a"];
}