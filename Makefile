all: main.bin

%.bin: %.cc
	g++ $< -o $@ -O2 -std=c++14
	python include_replacer.py $< > __output.cc
	./$@ < data.in

clean:
	rm -rf __output.cc main *.bin *.out *.dSYM
	git checkout -- main.cc

