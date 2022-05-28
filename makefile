project	= gui_lib
project_tmp_dir	= tmp/data

src_dir	= src/gui_impl src/example
inc_dir	= src/gui_library/frame src/gui_library/common src/gui_library/functional src/gui_library/graphic src/gui_library/gui src/gui_library/system src/gui_impl
out_dir	= tmp/bin

cc	= clang++
ld	= clang++
build_dir	= tmp/build
cc_flags	= -Wall -Wextra -std=c++17
cc_env		= -DPATH_SAVING_DIRECTORY=\"${project_tmp_dir}\"
ld_flags	= -lsfml-graphics -lsfml-window -lsfml-system
cc_debug	= -Og -g -D MAKE_LOG
cc_release	= -O2 -D NDEBUG
out_bin_release	= ${out_dir}/${project}
out_bin_debug	= ${out_dir}/${project}_debug

VPATH = ${src_dir}

BUILD	= debug
VERBOSE := false # change this to see all output
ifeq (${VERBOSE},true)
    HIDE = 
else
    HIDE = @
endif

obj_release	= ${addprefix ${build_dir}/, ${patsubst %.cpp, %_release.o, ${notdir ${wildcard ${addsuffix /*.cpp, ${src_dir}}}}}}
obj_debug	= ${addprefix ${build_dir}/, ${patsubst %.cpp, %_debug.o, ${notdir ${wildcard ${addsuffix /*.cpp, ${src_dir}}}}}}

out_bin	= ${out_bin_${BUILD}}
out_obj	= ${obj_${BUILD}}

.PHONY: all
all:
	@echo "dunger 2022"
	@echo "use help to get available"

.PHONY: help
help:
	@echo "You may choose:"
	@echo "    build - generate binary to out_dir, uses build_dir for temp files"
	@echo "    run - run generated binary"
	@echo "You may set flags:"
	@echo "    VERBOSE=true - disable shutting down commands"
	@echo "    BUILD=release - change compile options"
	@echo "You may change:"
	@echo "    out_dir, build_dir"

.PHONY: build
build: ${out_bin}

.PHONY: run
run:
	${out_bin}

.PHONY: dev
dev:
	@clear
	@time -p ${MAKE} ${out_bin}
	${out_bin}

${out_bin}: ${out_dir} ${build_dir} ${out_obj} ${project_tmp_dir}
	@echo linking $@
	${HIDE}${ld} ${out_obj} -o $@ ${ld_flags}

${build_dir}/%_${BUILD}.o: %.cpp
	@echo compiling $@
	${HIDE}${cc} -MMD -MF${build_dir}/$*.d -c $< -o $@ ${addprefix -I,${inc_dir}} ${cc_flags} ${cc_env} ${cc_${BUILD}}

include ${wildcard ${build_dir}/*.d}

${build_dir}:
	mkdir -p $@

${out_dir}:
	mkdir -p $@

${project_tmp_dir}:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf ${out_dir} ${build_dir}

.PHONY: clean_all
clean_all:
	rm -rf ${out_dir} ${build_dir} ${project_tmp_dir}