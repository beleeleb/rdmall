#RD3 10.12.2014
include Makefile.header

DIR = exercises

all:
clean: clean_this_dir
%:
	@for i in $(DIR); do \
		(cd $$i && $(MAKE) $(MFLAGS) $(@)); \
	done 

clean_this_dir:
	$(RM) *~ *.bak
