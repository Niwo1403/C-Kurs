# Path to termbox, must be set like this on andorra
TERMBOX ?= $(HOME)/termbox/DESTDIR/usr
# Many more warnings, not all "good"
WARNINGS=-Wall \
         -Wextra \
         -pedantic \
         -Wchkp \
         -Wmissing-include-dirs \
         -Wswitch-default \
         -Wunused-parameter \
         -Wuninitialized \
         -Wfloat-equal \
         -Wshadow \
         -Wunsafe-loop-optimizations \
         -Wbad-function-cast \
         -Wcast-align \
        # -Wwrite-strsings \
         -Wconversion \
         -Wlogical-op \
         -Wredundant-decls \
         -Wnested-externs \
         -Wstrict-prototypes \
         -Wmissing-prototypes \
         -Wstrict-aliasing \
         -Wold-style-definition
        # -Wnull-dereference \
        # -Wduplicated-cond

# C11, don't use builtin functions
CFLAGS=-std=gnu99 -fno-builtin
# Generate dependency files
# Add termbox path to include dir
CPPFLAGS=$(WARNINGS) -isystem$(TERMBOX)/include -MMD -MF $*.d
# Link with termbox
LDLIBS=-ltermbox -pthread
# Add termbox path to library dir
# Also add termbox path to dynamic linking search path
LDFLAGS=-L$(TERMBOX)/lib -Wl,-rpath,$(TERMBOX)/lib

# if not called with `make DEBUG=` compile in debug mode
DEBUG ?= y
ifeq ($(DEBUG), y)
CFLAGS += -Og -g3
else
CPPFLAGS += -DNDEBUG -O3
endif

# if not called with `make DEBUG=` compile in debug mode
all: map

# if not called with `make DEBUG=` compile in debug mode
obj-y += map.o
# Append submodules to list, eg.:
#     obj-y += mod1/module.o
#     -include mod1/*.d
# and then include that Makefile:
#include mod1/objs.mk

# Build program from object list
map: $(obj-y)

# Manual GNU-style pattern-rule, equivalent to .c.o suffix rule
%: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)
# Include generated dependency rules, ignore if not existing
-include *.d
# Also recompile if dependency files have changed
%.o: %.c %.d
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
# If dependency files don't exist (first build), ignore (otherwise previous rule
# would fail)
%.d: ;

# Remove final binary, objects and dependency files
clean:
	@$(RM) -v map $(obj-y) $(obj-y:.o=.d)

# Don't use (builtin) suffix rules
.SUFFIXES:
# These aren't "real" build targets
.PHONY: clean all
# Don't remove intermediate files
.PRECIOUS: $(obj-y) $(obj-y:.o=.d)
