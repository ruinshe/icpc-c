CXX_FLAGS=-O2 -g -std=c++17 -Wall -isystem . -Itestlib -DIDEA_TIME_EVALUATE
DEPTOKEN='\# MAKEDEPENDS'
include config.mk

all: run_solution
generate_and_run: run_generator run_solution
generate_and_sol: run_generator run_standard run_solution FORCE
generate_and_interaction: run_generator run_interaction FORCE

%.bin: %.o
	g++ $< -o $@ $(CXX_FLAGS)

run_solution: main.bin cmd/diff.bin FORCE
	./$< < data.in > user.out
	python include_replacer.py main.cc > __output.cc
	cmd/diff.bin data.in user.out data.out

run_standard: sol.bin FORCE
	./$< < data.in > data.out
	head -c 10 data.out

run_generator: generator.bin FORCE
	./$< $$RANDOM$$RANDOM$$RANDOM$$RANDOM > data.in 2>data.out

prepare_data: clean
	scrapy runspider data-downloader.py -a contestId=${CID} -a problemId=${PID}

%.o: %.cc %.d
	g++ $< -c -o $@ $(CXX_FLAGS)

%.m: %.cc %.d FORCE
	g++ -E $<  | grep -v ^# | indent > $@

%.d: %.cc
	g++ $(CXX_FLAGS) -MM $< > $@

clean:
	rm -rf __output.cc main *.bin *.dSYM *.d *.bak *.o *.m user.*
	git checkout -- main.cc generator.cc cmd/diff.cc cmd/interaction.cc

run_interaction: main.bin cmd/interaction.bin
	rm -f user.pipe
	mkfifo user.pipe
	cmd/interaction.bin data.in data.out < user.pipe | ./main.bin | tee user.pipe > user.out
	python include_replacer.py main.cc > __output.cc

FORCE:

sinclude main.d
sinclude generator.d
sinclude sol.d
sinclude cmd/diff.d
sinclude cmd/interaction.d
