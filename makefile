

lpatch: lpatch.cpp
	g++ -o lpatch lpatch.cpp -I ./lua-5.4.4/src ./lua-5.4.4/src/liblua.a -ldl

clean :
	rm -f lpatch
