.PHONY: all clean

all:
	$(MAKE) -C src
	$(MAKE) -C tests

clean:
	$(MAKE) -C src clean
	$(MAKE) -C tests clean
