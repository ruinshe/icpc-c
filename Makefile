CXX_FLAGS=-O2 -g -std=c++17 -isystem . -Itestlib # -DIDEA_TIME_EVALUATE -D__DEBUG__
DEPTOKEN='\# MAKEDEPENDS'
include config.mk

all: run_solution
generate_and_run: run_generator run_solution
generate_and_sol: run_generator run_standard run_solution FORCE

%.bin: %.o
	@g++ $< -o $@ $(CXX_FLAGS)

run_solution: main.bin cmd/diff FORCE
	./$< < data.in > user.out
	python include_replacer.py main.cc > __output.cc
	cmd/diff data.in user.out data.out

run_standard: sol.bin FORCE
	./$< < data.in > data.out
	head -n 2 data.out

run_generator: generator.bin FORCE
	./$< $$RANDOM$$RANDOM$$RANDOM$$RANDOM > data.in

prepare_data: clean
	scrapy runspider data-downloader.py -a contestId=${CID} -a problemId=${PID}

%.o: %.cc # %.d
	g++ $< -c -o $@ $(CXX_FLAGS)

%.m: %.cc %.d FORCE
	g++ -E $< |grep -v ^#|indent > $@

main.m:

# %.d: %.cc
# 	@echo $(DEPTOKEN) > $@
# 	@makedepend -Y -f $@ -s $(DEPTOKEN) -- -O2 -std=C++17 -- $< &> /dev/null

clean:
	rm -rf __output.cc main *.bin *.dSYM *.d *.bak *.o *.m sol.* user.out
	git checkout -- main.cc generator.cc

main.bin: data.in

cmd/diff: cmd/diff.cc cmd/testlib.h
	g++ -o $@ --std=gnu++0x $<

FORCE:

sinclude main.d
sinclude generator.d
