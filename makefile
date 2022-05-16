test:test.o git_bisect.o golden_bisect.o bisect_base.o
	g++ test.o git_bisect.o golden_bisect.o bisect_base.o -o test

test.o:test.cpp
	g++ test.cpp -c  -o test.o
git_bisect.o:git_bisect.cpp
	g++ git_bisect.cpp -c  -o git_bisect.o
golden_bisect.o:git_bisect.cpp
	g++ golden_bisect.cpp -c  -o golden_bisect.o
bisect_base.o:bisect_base.cpp
	g++ bisect_base.cpp -c  -o bisect_base.o

clean:
	del *.o -rf