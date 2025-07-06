bin/testllist: Include/l_list.h Include/l_list.inc src/list_test.cpp | bin
	g++ -o bin/testllist -I Include src/list_test.cpp

test: bin/testllist
	./bin/testllist

bin:
	mkdir bin

clean:
	@rm -rf bin
