env = Environment(CPPPATH='#include/', CCFLAGS='-g -W -Wall -Werror -std=c99 -pedantic', LIBPATH='#lib/')

SConscript(['lib/SConscript', 'test/SConscript'], 'env')

Alias('libm3.a', 'lib/libm3.a')
Alias('test', 'test/libm3_test')
Default('libm3.a')
