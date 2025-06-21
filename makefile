bin/testllist: include/l_list.h include/l_list.inc src/list_test.cpp | bin
	g++ -o bin/testllist -I include src/list_test.cpp

test: bin/testllist
	./bin/testllist

bin/temp: include/l_list.h include/l_list.inc temp.cpp | bin
	g++ -o bin/temp -I include temp.cpp

temp: bin/temp
	./bin/temp

bin:
	mkdir bin

clean:
	@rm -rf bin
