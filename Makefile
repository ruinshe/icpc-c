CXX_FLAGS=-O2 -std=c++14
DEPTOKEN='\# MAKEDEPENDS'


all: main.bin

%.bin: %.o
	g++ $< -o $@ $(CXX_FLAGS)
	./$@ < data.in

%.o: %.cc %.d
	g++ $< -c -o $@ $(CXX_FLAGS)
	python include_replacer.py $< > __output.cc

%.d: %.cc
	@echo $(DEPTOKEN) > $@
	makedepend -Y -f $@ -s $(DEPTOKEN) -- $(CXX_FLAGS) -- $< &> /dev/null

clean:
	rm -rf __output.cc main *.bin *.out *.dSYM *.d *.bak
	git checkout -- main.cc

main.bin: data.in

sinclude main.d
