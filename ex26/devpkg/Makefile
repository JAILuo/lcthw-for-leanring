# PREFIX?=/usr/local
# CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1  -I${PREFIX}/apr/include/apr-util-1 -D_LARGEFILE64_SOURCE=1
# LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

# all: devpkg

# devpkg: bstrlib.o db.o shell.o commands.o

# install: all
# 	install -d $(DESTDIR)/$(PREFIX)/bin/
# 	install devpkg $(DESTDIR)/$(PREFIX)/bin/

# clean:
# 	rm -f *.o
# 	rm -f devpkg
# 	rm -rf *.dSYM

PREFIX ?= /usr/local
CFLAGS = -g -Wall -I${PREFIX}/apr/include/apr-1 -I${PREFIX}/apr/include/apr-util-1 -D_LARGEFILE64_SOURCE=1 -Wl,-R$(PREFIX)/apr/lib
LDFLAGS = -L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

all: devpkg

devpkg: bstrlib.o db.o shell.o commands.o main.o
	gcc $(CFLAGS) -o devpkg bstrlib.o db.o shell.o commands.o main.o $(LDFLAGS)

install: devpkg
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 755 devpkg $(DESTDIR)$(PREFIX)/bin/

bstrlib.o: bstrlib.c bstrlib.h
	gcc $(CFLAGS) -c bstrlib.c

db.o: db.c db.h
	gcc $(CFLAGS) -c db.c

shell.o: shell.c shell.h
	gcc $(CFLAGS) -c shell.c

commands.o: commands.c commands.h
	gcc $(CFLAGS) -c commands.c

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o devpkg
