CC = g++
LD = g++

CFLAGS += -Wall -Wpedantic -Iinclude

SOURCES := $(wildcard src/*.cpp)
OBJS := $(SOURCES:.cpp=.o)
DEPS := $(SOURCES:.cpp=.d)
TEST_OBJS := $(filter-out %main.test.o, $(SOURCES:.cpp=.test.o))
TEST_OBJS += tests/test.o
TEST_DEPS := $(filter-out %main.test.d, $(SOURCES:.cpp=.test.d))
TEST_DEPS += tests/test.d

ifeq ($(OS),Windows_NT)
  CFLAGS += -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code \
            -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra \
            -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security \
            -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor \
            -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel \
            -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
else
  CFLAGS += -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat \
            -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion \
            -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness \
            -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith \
            -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
            -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default \
            -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix \
            -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
            -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer \
            -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
            # -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
endif

all : a

test : atest
	./atest
	gcov $(TEST_OBJS)

tests/test.d : tests/test.cpp
	$(CC) $(CFLAGS) -MM -MT "$(@:.d=.o)" -MF $@ $<

tests/test.o : tests/test.cpp tests/test.d
	$(CC) $(CFLAGS) --coverage -c $< -o $@

-include $(DEPS)
-include $(TEST_DEPS)

a : $(OBJS)
	$(LD) $^ $(LDFLAGS) -o $@

%.d: %.cpp
	$(CC) $(CFLAGS) -MM -MT "$(@:.d=.o)" -MF $@ $<

%.o : %.cpp %.d
	$(CC) $(CFLAGS) -c $< -o $@


atest : $(TEST_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@ -lgcov

%.test.d: %.cpp
	$(CC) $(CFLAGS) -MM -MT "$(@:.d=.o)" -MF $@ $<

%.test.o : %.cpp %.test.d
	$(CC) $(CFLAGS) --coverage -c $< -o $@
	
clean:
	rm -f **/*.o **/*.d a atest **/*.gcda **/*.gcno **/*.gcov
