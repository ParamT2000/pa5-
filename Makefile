WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -O3 $(WARNING) $(ERROR) #change back to -g for debugging
#VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose


SRCS = pa5.c sorting.c
OBJS = $(SRCS:%.c=%.o)

pa5: $(OBJS)
	$(GCC) $(TESTFALGS)  $(OBJS) -o pa5

.c.o:
	$(GCC) $(TESTFALGS) -c $*.c



clean: # remove all machine generated files
	rm -f pa5 *.o output?

testQ1M:
	./generate 1000000 1M.b
	./quick 1M.b correct.b
	time ./pa5 -q 1M.b out1M.b
	diff out1M.b correct.b

testQ4M:
	./generate 4000000 4M.b
	./quick 4M.b correct.b
	time ./pa5 -q 4M.b out4M.b
	diff out4M.b correct.b


memCheckQ: pa5
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	./pa5 -q 1M.b out1M.b


