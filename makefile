compiler = clang
linked_list_path = src/linked_list
tree_path = src/tree
target_path = target
compiler_cmd = $(compiler) $(DBG_FLAG)

ifeq ($(DEBUG), 1) 
	DBG_FLAG = -g
endif

target:
	mkdir $(target_path)/

build_tree: target $(tree_path)/tree.c build_linked_list
	$(compiler_cmd) -c $(tree_path)/tree.c -o $(target_path)/tree.o

build_linked_list: target $(linked_list_path)/linked_list.c
	$(compiler_cmd) -c $(linked_list_path)/linked_list.c -o $(target_path)/linked_list.o 

build_test: target $(test_path)
	$(compiler_cmd) -o $(target_path)/more_c.test.o -c src/main.test.c

build_program: target build_linked_list build_tree
	$(compiler_cmd) -o $(target_path)/main.o src/main.c -c 

run: target build_linked_list build_program build_tree
	$(compiler_cmd) -o $(target_path)/more_c $(target_path)/main.o $(target_path)/linked_list.o  $(target_path)/tree.o
	./$(target_path)/more_c
	
run_test: target build_linked_list build_test build_tree
	$(compiler_cmd) -o $(target_path)/more_c.test $(target_path)/more_c.test.o $(target_path)/linked_list.o  $(target_path)/tree.o
	./$(target_path)/more_c.test

clean:
	rm -rf $(target_path)/