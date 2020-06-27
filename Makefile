OPEN_SPIEL :=src/open_spiel
ABSEIL :=$(OPEN_SPIEL)/abseil-cpp
BRIDGE :=$(OPEN_SPIEL)/games/bridge/double_dummy_solver
PYBIND :=src/pybind11
OPEN_SPIEL_DEPS :=$(ABSEIL) $(BRIDGE)


# Build Rules
#============
default: build.Release/Makefile build
	cd build.Release && $(MAKE)
.PHONY: default

build.%:
	mkdir $@

build.%/Makefile: | $(OPEN_SPIEL) $(OPEN_SPIEL_DEPS) build.%
	cd build.$* && ../scripts/generate_build.sh $*

build: | build.Release
	ln -s build.Release $@

$(OPEN_SPIEL):
	-git clone -b 'master' --single-branch --depth 1 \
		https://github.com/deepmind/open_spiel.git .open_spiel-tmp
	mv .open_spiel-tmp/open_spiel $@
	rm -rf .open_spiel-tmp

$(ABSEIL): $(OPEN_SPIEL)
	-git clone -b '20200225.1' --single-branch --depth 1 \
		https://github.com/abseil/abseil-cpp.git $@

$(BRIDGE): $(OPEN_SPIEL)
	-git clone -b 'develop' --single-branch --depth 1 \
		https://github.com/jblespiau/dds.git $@

# This is currently unused but could be useful for later enabling optional
# access to OpenSpiel's Python interface.
$(PYBIND):
	-git clone -b 'v2.2.4' --single-branch --depth 1 \
		https://github.com/pybind/pybind11.git $@


# Meta Rules
#===========
print-%:
	@echo $* = $($*)
.PHONY: print-%
