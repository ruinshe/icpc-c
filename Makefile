CXX_FLAGS=-O2 -g -std=gnu++0x -isystem . -DIDEA_TIME_EVALUATE -Itestlib
DEPTOKEN='\# MAKEDEPENDS'
include config.mk

all: run_solution pbcopy
generate_and_run: run_generator run_solution

%.bin: %.o
	@g++ $< -o $@ $(CXX_FLAGS)

run_solution: main.bin FORCE
	@echo "running solution..."
	@./$<
	@python include_replacer.py main.cc > __output.cc

run_generator: generator.bin FORCE
	@echo "generating data..."
	@./$< $$RANDOM$$RANDOM$$RANDOM$$RANDOM > data.in

prepare_data:
	scrapy runspider data-downloader.py -a contestId=${CID} -a problemId=${PID}

%.o: %.cc %.d
	@g++ $< -c -o $@ $(CXX_FLAGS)

%.m: %.cc %.d FORCE
	g++ -E $< |grep -v ^#|indent > $@

main.m:

%.d: %.cc
	@echo $(DEPTOKEN) > $@
	@makedepend -Y -f $@ -s $(DEPTOKEN) -- -O2 -std=gnu++0x -- $< &> /dev/null

clean:
	@rm -rf __output.cc main *.bin *.out *.dSYM *.d *.bak *.o *.m
	@git checkout -- main.cc generator.cc

main.bin: data.in

pbcopy:
	@pbcopy < __output.cc

FORCE:

sinclude main.d
sinclude generator.d

