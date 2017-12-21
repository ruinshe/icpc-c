CXX_FLAGS=-O2 -std=gnu++0x -isystem .
DEPTOKEN='\# MAKEDEPENDS'

all: main.bin pbcopy

%.bin: %.o FORCE
	g++ $< -o $@ $(CXX_FLAGS)
	./$@ < data.in

%.o: %.cc %.d
	g++ $< -c -o $@ $(CXX_FLAGS)
	python include_replacer.py $< > __output.cc

%.m: %.cc %.d FORCE
	g++ -E $< |grep -v ^#|indent > $@

main.m:

%.d: %.cc
	@echo $(DEPTOKEN) > $@
	makedepend -Y -f $@ -s $(DEPTOKEN) -- -O2 -std=gnu++0x -- $< &> /dev/null

clean:
	rm -rf __output.cc main *.bin *.out *.dSYM *.d *.bak *.o *.m
	git checkout -- main.cc

main.bin: data.in

pbcopy:
	pbcopy < __output.cc

FORCE:

sinclude main.d
