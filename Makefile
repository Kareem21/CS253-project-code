export opts= \
            -fno-diagnostics-show-option -fstack-protector-all -g -O9 \
            -std=c++14 -Wctor-dtor-privacy -Werror -Wextra -Wfatal-errors \
            -Winit-self -Wlogical-op -Wold-style-cast -Wpedantic -Wshadow \
            -Wunused-const-variable=1 -Wzero-as-null-pointer-constant \
            -Wduplicated-cond -Wduplicated-branches -Walloc-zero -Walloca
CXXFLAGS=-Wall $$opts

assignment=hw8
lib=$(assignment).a

$(lib): Alpha.o PGM.o Image.o
	$(AR) -rcs $@ $?

Alpha.o:: Alpha.cc Alpha.h Image.h
PGM.o:: PGM.cc PGM.h Image.h
Image.o:: Image.cc Image.h

tar:
	tar -cv $(MAKEFILE_LIST) Alpha.h Alpha.cc PGM.h PGM.cc Image.h Image.cc constants.h type.h >$(assignment).tar

test: $(lib)
	$(CXX) $(CXXFLAGS) test.cc $(lib)
	./a.out

clean:
	rm -f $(assignment) $(assignment).{a,tar} *.o *.gch a.out
