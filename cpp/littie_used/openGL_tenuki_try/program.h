#define key_board_func2(y,new_y) \
	y=new_y;\
	printf("%s=%f\n",#y,y);\

#define key_board_func(key_char,y,new_y) \
if(key==key_char){\
	printf("key=%c,",key_char);\
	key_board_func2(y,new_y);\
}
