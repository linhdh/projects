#############################################################################
#
#	Makefile for building the gpio application
#
#############################################################################

APPNAME		= args

OVEROTOP	?= /home/gumstix/overo-oe
CROSS_COMPILE	?= $(OVEROTOP)/tmp/cross/armv7a/bin/arm-angstrom-linux-gnueabi-

CC		= $(CROSS_COMPILE)gcc

CFLAGS += \
	-std=gnu99 \
	-Wall \
	-Wimplicit \
	-Wpointer-arith \
	-Wswitch \
	-Wredundant-decls \
	-Wreturn-type \
	-Wshadow \
	-Wunused \
	-Wcast-qual \
	-Wnested-externs \
	-Wmissing-prototypes \
	-Wstrict-prototypes \
	-Wmissing-declarations \
	-I ../lib

DEP_OUTPUT_OPTION = -MMD -MF $(@:.o=.d)

OBJ_FILES = args.o

$(APPNAME) : $(OBJ_FILES)
	@echo "Creating executable $@ ..."
	$(CC) -o $@ $^

.PHONY: %.d
%.d: ;

%.o : %.c %.d
	@echo "Compiling $< ..."
	$(COMPILE.c) $(DEP_OUTPUT_OPTION) $(OUTPUT_OPTION) $<

clean:
	rm -rf $(APPNAME) *.o *.d

DEP_FILES = $(strip $(OBJ_FILES:.o=.d))

ifneq ($(DEP_FILES),)
ifeq ($(strip $(filter clean%, $(MAKECMDGOALS))),)
-include $(DEP_FILES)
endif
endif

