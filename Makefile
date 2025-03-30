smooth_sort_test: 
	gcc ./sorting_algz.c ./tests.c ./main.c -o smooth_sort
	./smooth_sort smooth > smooth_sort_result.txt
	rm smooth
	
patience_sort_test: 
	gcc ./sorting_algz.c ./tests.c ./main.c -o patience_sort
	./patience_sort patience > patience_sort_result.txt
	rm patience

gnome_sort_test: 
	gcc ./sorting_algz.c ./tests.c ./main.c -o gnome_sort
	./gnome_sort gnome > gnome_sort_result.txt
	rm gnome

test: 
	gcc ./sorting_algz.c ./tests.c ./main.c -o test
	./test test > test.txt
	rm test