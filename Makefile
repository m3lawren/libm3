.PHONY: clean all

all:
	@ctags -R * > /dev/null 2>&1
	@make -C lib
	@make -C test

clean:
	@make -C lib clean
	@make -C test clean
