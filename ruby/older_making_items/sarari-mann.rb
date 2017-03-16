cost_matrix = [
[ 0, 7, 12, 8, 11, 7 ],
[ 3, 0, 10, 7, 13, 2 ],
[ 4, 8, 0, 9, 12, 3 ],
[ 6, 6, 9, 0, 10, 7 ],
[ 7, 7, 11, 10, 0, 5 ],
[ 9, 7, 8, 9, 10, 0 ]
]


temp=[*0..5].permutation.map{|x|
[x.each_cons(2).map{|i,j|
	cost_matrix[i][j]
}.inject(:+),x]
}
p min=temp.map{|x|x[0]}.min
p temp.assoc(min)[1]
