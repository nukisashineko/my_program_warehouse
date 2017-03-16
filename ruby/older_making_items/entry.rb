require 'tk'

Food=Struct.new(:name,:value)
Dish=Struct.new(:array,:name,:peoplecount,:value)

def list_box_add_end_Item(list_box,tmp,i)
list_box.insert('end', "#{i} #{tmp.name}=#{tmp.value}"); 
end
def list_box_add_end_classname(list_box,tmp)
list_box.insert('end', "#{tmp.name}"); 
end
def list_box_add_end_Food(list_box,tmp)
list_box.insert('end', "   #{tmp.name}=#{tmp.value}yen"); 
end
def list_box_add_end_Dish(list_box,tmp)
list_box.insert('end', "#{tmp.name}=#{tmp.value}yen /#{peoplecount} = #{(tmp.value/peoplecount).floor}"); 
end


def entry_clear(x)
	x.value=""
end

def make_input(list_box,array)
t = TkToplevel.new
label=TkLabel.new(t){
	text "Will be puted food's values below."
	pack
}

dish=Dish.new([])
dish_name = TkEntry.new(t).pack
n = TkEntry.new(t).pack
v = TkEntry.new(t).pack

TkButton.new(t){
	text 'add food to dish'
	command {
	 dish.array<< tmp=Food.new(n.value,v.value)
	 n.focus
	 entry_clear(n)
	 entry_clear(v)
	 list_box_add_end_Item(list_box,tmp,dish.array.size)
	}
	pack
}

TkButton.new(t){
	text 'change dish'
	command {
	 array<<dish
	 dish=Dish.new([],dish_name.value,nil)
	 entry_clear(dish_name)
	 n.focus
	 list_box_add_end_classname(list_box,dish)
	}
	pack
}

TkButton.new(t){
	text 'calculate'
	command {
	 caluculate(array) 
#	 t.destroy
	}
	pack
}

end
def make_see_value
array=[]
l = TkListbox.new.pack

make_input(l,array)

Tk.mainloop
end

def input_people_count(dish)
	t = TkToplevel.new
	TkLabel.new(t){
	 text "How many  dividing #{dish.name}."
	 pack
	}
	TkEntry.new(t){
		pack
	}
	e=TkEntry.new(t)
	e.focus
	e.bind 'Return', proc { dish.peoplecount=e.value.to_i; t.destroy; }

end
def input_all_people_count(array)
	array.each{|x| input_people_count(x)}
end
def sum_dish(dish)
	s=0
	dish.array.each{|x| s+=x.value}
	s
end
def sum_array(array)
	s1=s2=0
	array.each{|x| p x;s1+=x.value; s2+=(x.value/x.peoplecount).floor; }
	[s1,s2]
end


def caluculate(array)
	array.each{|x|x.value=sum_dish(x)}
	yen,yen_per_people=sum_array(array)
#still this line is cauculate

	t = TkToplevel.new
	TkLabel.new(t){
	 text "How much is the #{dish.name}."
	 pack
	}
	l = TkListbox.new(t)
	array.each do |d|
		list_box_add_end_Dish(d)
		d.each{|x| list_box_add_end_Food(x)}
	end
	TkLabel.new(t){
		text "all sum #{yen}yen .... one will pay #{yen_per_people}yen "
	}
	e=TkEntry.new(t)
	e.focus
	e.bind 'Return', proc { t.destroy;  }
end


make_see_value



until name == [] do
v=value.pop
n=name.pop
TkLabel.new(nil, 'text'=>"#{n}=#{v}").pack
end


TkButton.new(nil, 'text'=>'next goods',
 'command'=>proc{ name << entry.value.to_s; value << entry2.value.to_i; entry.value=entry2.value=""; }).pack
TkButton.new(nil, 'text'=>'end', 'command'=>proc{  TkRoot.new.destroy }).pack
Tk.mainloop


puts "Hello, #{name} value=#{value.class} "
