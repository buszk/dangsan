CC=clang-10
INCLUDES=-I. -I../staticlib -I../metapagetable
LLVMFLAGS=-I/usr/lib/llvm-10/include  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -fPIC
CFLAGS=-c -Wall -std=c++14 -g $(LLVMFLAGS) -O0 
LDFLAGS=-g -shared -L/usr/lib/llvm-10/lib -lLLVM -lstdc++ -Wl,-znodelete
TARGETDIR=.
OBJDIR=$(TARGETDIR)/obj
#GOLDINSTDIR=$(METALLOC_HOME)/autosetup.dir/install/common
GOLDINSTDIR=/usr/lib/llvm-10
LINKWITHGOLDFLAGS=-Wl,--no-undefined -L $(GOLDINSTDIR)/lib/ -l:LLVMgold.so -Wl,--rpath=$(GOLDINSTDIR)/lib

EXE=$(TARGETDIR)/libplugins.so
EXE2=$(TARGETDIR)/libplugins-opt.so

SRCS    := $(wildcard *.cpp)
OBJS    := $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))
DEPS    := $(OBJS:.o=.d)

all: $(EXE) $(EXE2)

clean:
	rm $(OBJDIR)/*.o
	rm $(OBJDIR)/*.d
	rm $(EXE)
	rm $(EXE2)

$(EXE): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LINKWITHGOLDFLAGS) -o $@

$(EXE2): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

-include $(DEPS)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(INCLUDES) $(CFLAGS) -MMD -o $@ $<
	
