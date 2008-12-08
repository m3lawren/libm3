include = Dir('include')
lib = Dir('lib')

env = Environment(CPPPATH=include, LIBPATH=lib, CCFLAGS='-O2 -g -Wall -Wextra -Wunused -Werror -pedantic -std=c99')

Import('*')

SConscript(['lib/SConscript', 'test/SConscript'], ['env'])

Alias('libm3.a', 'lib/libm3.a')
Alias('test', 'test/libm3_test')
