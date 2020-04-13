
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla 
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)  #change back to -g for debugging
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
	./quick 1M.b correct.b
	time ./pa5 -q 1M.b out1M.b
	diff out1M.b correct.b

testQ3M:
	time ./quick 3M.b correct.b
	time ./pa5 -q 3M.b outQ3M.b
	time ./pa5 -m 3M.b outM3M.b
	diff correct.b outQ3M.b 
	diff correct.b outM3M.b

testQ4M:
	./quick 4M.b correct.b
	time ./pa5 -q 4M.b out4M.b
	diff out4M.b correct.b

testM10:
	#./quick 10.b correct.b
	./pa5 -q 10.b correct.b
	time ./pa5 -m 10.b out10.b
	diff out10.b correct.b 

testM1M:
	#./quick 10.b correct.b
	./pa5 -q 1M.b correct.b
	time ./pa5 -m 1M.b out1M.b
	diff out1M.b correct.b 

testM2M: 
	./pa5 -q 2M.b correct.b
	time ./pa5 -m 2M.b out2M.b
	diff out2M.b correct.b 

testM8M: 
	./pa5 -q 8M.b correct.b
	time ./pa5 -m 8M.b out8M.b
	diff out8M.b correct.b 

testM100M:
	#./generate -s 4 100000000 100M.b
	./quick 100M.b correct.b
	time ./pa5 -m 100M.b out100M.b 
	diff out100M.b correct.b

#memory checking stuff
memCheckQ: pa5
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	./pa5 -q 3M.b out3M.b

memCheckM: pa5
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	./pa5 -m 8M.b out8M.b


