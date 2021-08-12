prefix = /usr/local

all: src/electro

src/electro: src/electrotest.c src/electrotest.h
	@echo "CFLAGS=$(CFLAGS)" | \
		fold -s -w 70 | \
		sed -e 's/^/# /'
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDCFLAGS) -o $@ $^

install: src/electro
	install -D src/hello \
		$(DESTDIR)$(prefix)/bin/electro

clean:
	-rm -f src/electro

distclean: clean

uninstall:
	-rm -f $(DESTDIR)$(prefix)/bin/electro

.PHONY: all install clean distclean uninstall
