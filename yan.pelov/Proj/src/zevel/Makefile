include ../Makefile.header

MODULE=zevel
CFILE_ROOTS= rec_bin_tree_2 tree_ip mem_check files_search myso
#CPPFILE_ROOTS=cppfoo

# for .h files that don't have a .c or test*.c file:
STAND_ALONE_H_FILES=
STAND_ALONE_CPPH_FILES=
#STAND_ALONE_H_FILES=global_constants.h

# PROJ_LIBS is stuff we wrote that can be debugged and have a *.dbg version
PROJ_LIBS=-l$(MODULE)
# can be expanded as follows:
#PROJ_LIBS=-l$(MODULE) -lwatchdog -lsomeotherthingwewrote

# LIBS is the regular LIBS var of all LIBS we need to link with
LIBS= -lm
# can be expanded as follows:
#LIBS=-lm


include ../Makefile.trailer

# My own executable can be compiled like this:
# debug: watchdog
# release: watchdog.dbg
#watchdog: watchdog.c $(LIB_NAME)
#	   $(CC) $(CFLAGS) $(RELEASE_FLAGS) $< $(LDFLAGS) $(LIBS) -o$(@)
#
#watchdog.dbg: watchdog.c $(DBG_LIB_NAME)
#	   $(CC) $(CFLAGS) $(DEBUG_FLAGS) $< $(LDFLAGS) $(DBG_LIBS) -o$(@)



# DO NOT DELETE
