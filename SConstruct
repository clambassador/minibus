import os
for i in range(0, 10):
    print ""
common = Split("""../ib/libib.a
	       """)
tests = dict()
tests['test_list_select.cc'] = 'test_list_select'
tests['test_driver.cc'] = 'test_driver'
tests['test_cached_display.cc'] = 'test_cached_display'

libs = Split("""pthread
	        ncurses
	     """)
env = Environment(CXX="ccache clang++ -I../.. -I..", CPPFLAGS="-D_FILE_OFFSET_BITS=64 -Wall -g --std=c++11 -pthread", LIBS=libs, CPPPATH="..")
env['ENV']['TERM'] = 'xterm'


Decider('MD5')
for i in tests:
	env.Program(source = ['tests/' + i] + common, target = tests[i])

