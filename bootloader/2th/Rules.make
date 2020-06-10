unexport O_TARGET
unexport obj-y
unexport subdirs
unexport SUBDIRS

ifdef O_TARGET
$(O_TARGET): $(obj-y)
	rm -f $@
	$(LD) -r -o $@ $^
endif # O_TARGET

%o:%c
	$(CC) $(CFLAGS)  -c -o $@ $< $(DIR_INCLUDE)
%o:%S
	$(CC) $(CFLAGS)  -c -o $@ $< $(DIR_INCLUDE)
	
SUBDIRS = init
.PHONY:subdirs $(SUBDIRS)
subdirs:$(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@