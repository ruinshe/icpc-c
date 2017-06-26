all:
	g++ main.cc -o main.bin -O2 -std=gnu++0x
	python include_replacer.py main.cc > __output.cc
	./main.bin < data.in

clean:
	rm -rf __output.cc main *.bin *.out *.dSYM
	git checkout -- main.cc

