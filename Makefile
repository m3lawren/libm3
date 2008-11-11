.PHONY: clean all

all:
	@make -C lib
	@ctags -R * > /dev/null 2>&1

clean:
	@make -C lib clean
