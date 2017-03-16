h=[
	{n: 15, text: "FIZZBAZZ"},
	{n: 5, text: "BAZZ"},
	{n: 3, text: "FIZZ"}
];
(1..(1/0.0)).each{|i| 
	item= h.detect{|x|  i%x[:n] == 0 }; 
	puts (item.nil?)? i: item[:text]; 
}

