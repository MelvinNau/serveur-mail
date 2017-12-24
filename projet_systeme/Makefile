REP=$(shell pwd | sed "s%/.*/%%")

CFLAGS=-g -Wall `pkg-config --cflags --libs glib-3.0` -I.
CPPFLAGS=-g -Wall -std=c++11 -pthread -D_REENTRANT  -I.
CPPFLAGSK= -g -Wall  -std=c++11   -I.
LDFLAGS=  
CC=gcc
CPP=g++

PROGC=
PROGCPP=projet_client.cpp projet_serveur.cpp 

EXEC=$(PROGC:.c=.ex) $(PROGCPP:.cpp=.exx)
CLIBS=
CPPLIBS=socklib.cpp readerwriter.cpp bufferedreaderwriter.cpp 

COBJ=$(PROGC:.c=.o)
CPPOBJ=$(PROGCPP:.cpp=.O)
CPPLIBSOBJ=$(CPPLIBS:.cpp=.O)

FICHIERSBAK=$(wildcard *~) $(wildcard *.bak)

all: $(EXEC)

%.ex: %.o $(LIBS)
	$(CC) $(CFLAGS) $< $(CLIBS) $(CLDFLAGS) -o $@

%.exx: %.O $(CPPLIBSOBJ)
	$(CPP) $(CPPFLAGS) $< $(CPPLIBSOBJ) $(CPPLDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c

%.O: %.cpp
	$(CPP) $(CPPFLAGS) $< -c -o $@

%.class: %.java
	javac $<

clean:
	@for i in $(EXEC) $(TEMPORAIRE); \
        do \
                if [ -f $$i ]; then \
                        echo "efface "$$i;\
                        rm $$i; \
                fi; \
        done


grosclean: clean
	@for i in $(FICHIERSBAK); \
        do \
                if [ -f $$i ]; then \
                        echo "efface "$$i;\
                        rm $$i; \
                fi; \
        done \

tgz:: clean
	tar czvf ../$(REP)-`date +%y%m%d`.tgz -C ..  --exclude '*.swp' --exclude '*~' --exclude '.svn' $(REP)

tgz-complet:: clean
	tar czvf ../$(REP)-`date +%y%m%d`.tgz -h -C ..  --exclude '*.swp' --exclude '*~' --exclude '.svn' $(REP)

sujet:: clean
	tar czvf ../$(REP).tar.gz -C ..  --exclude '*.swp' --exclude '*~' --exclude '.svn' --exclude 'get_*.cpp' $(REP)
