include ../Makefile.header

MODULE = utils

CFILE_ROOTS = linked_list dlist cdlist queue prio_q sched_prioq bin_tree wd#rec_bin_tree myclient wd watch dict_count barrier buf_mutex prod dlist_safe file_safe reclist sorts      ring_buf stack   hash_table  heap dict_hash dictionary_hash sched_process1 

CPPFILE_ROOTS = 

# for .h files that don't have a .c or test*.c file:
STAND_ALONE_H_FILES = utils sched_prioq_types prio_q_types cdlist_types hash_table_types
STAND_ALONE_CPPH_FILES =

# PROJ_LIBS is stuff we wrote that can be debugged and have a *.dbg version
PROJ_LIBS = -l$(MODULE)
# can be expanded as follows:
#PROJ_LIBS = -l$(MODULE) -lwatchdog -lsomeotherthingwewrote

# LIBS is the regular LIBS var of all LIBS we need to link with
#LIBS = 
# can be expanded as follows:
LIBS = -lm -lpthread -pthread


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

