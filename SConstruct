include = Dir('include')
lib = Dir('lib')

env = Environment(CPPPATH=include, CCFLAGS='-O2 -g -Wall -Wextra -Werror -std=c99 -pedantic', LIBPATH=lib)

SConscript(['SConscript'], ['env'])

Default('test')
