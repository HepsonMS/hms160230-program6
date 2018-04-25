# Project:	Program 6
# File:		Makefile
# Name:		Hepson Sanchez
# Net-ID:	hms160230
# Course:	CS 3377.002
# Date:		4/24/2018

CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 

EXECFILE = exe

OBJS = cdkexample.o

PROJECTNAME = project6

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)


backup:
	@make clean
	@mkdir -p ~/CLASSES/2018Spring/CS3377/backups; chmod 700 ~/CLASSES/2018Spring/CS3377/backups
	@$(eval CURDIRNAME := $(shell basename $(CURDIR)))
	@$(eval MKBKUPNAME := ~/CLASSES/2018Spring/CS3377/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Backing up: $(CURDIRNAME)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcvf $(MKBKUPNAME) ../$(CURDIRNAME) > /dev/null 2> /dev/null
	@chmod 600 $(MKBKUPNAME)
	@echo Done!
