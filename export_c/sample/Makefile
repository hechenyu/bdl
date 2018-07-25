RM = rm -f
CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I..
LDFLAGS = -lcbase_dataset_loader 
LDPATH = -L../../lib -Wl,-R../../lib -Wl,--enable-new-dtags

SOURCES = $(shell ls *.c)
PROGS = $(SOURCES:%.c=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS)

%: %.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)

