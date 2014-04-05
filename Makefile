
INCS=-I.
SRCS=demo.cpp Callflow.cpp
callflow.out : $(SRCS)
	g++ $(INCS) $(SRCS) -o $@
