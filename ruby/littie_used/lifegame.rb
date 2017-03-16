
H,W = [`tput lines`.to_i-1,`tput cols`.to_i]

life_figure=[" ","o"];
eigth_way= [-1,0,1].repeated_permutation(2).map{|x|x}-[[0,0]]
next_figure = Hash.new(0);
next_figure[[1,2]] = 1;
next_figure[[1,3]] = 1;
next_figure[[0,3]] = 1;

# initarize 
table=[];
H.times{|i| table[i]=[]; W.times{|j| table[i][j]= (rand(5)==1)?1:0; }}
days = 0;
p table
#
while(1) do 
`clear`
print table.map{|row| row.map{|x| life_figure[x];}.join();}.join("\n");
H.times{|i| W.times{|j| 
  around = eigth_way.map{|h,w| (i+h<H && j+w<W)?table[i+h][j+w]:0 }.inject(0){|sum,i| i+sum}
  table[i][j] = next_figure[[table[i][j],around]]
  }
}
printf ("%4d after days"%days).center(W)
days+=1
sleep 0.5
end
