import os
for i in range(0, 10):
    print ""
common = Split("""../ib/libib.a
	       """)

tests = dict()
tests['test_list_select.cc'] = 'test_list_select'
tests['test_driver.cc'] = 'test_driver'
tests['test_cached_display.cc'] = 'test_cached_display'
tests['test_minibus_web.cc'] = 'test_minibus_web'
tests['test_multikey.cc'] = 'test_multikey'
tests['test_moveable.cc'] = 'test_moveable'
tests['test_textentry.cc'] = 'test_textentry'
tests['test_headermain.cc'] = 'test_headermain'
tests['test_vertical_list.cc'] = 'test_vertical_list'
tests['test_hotkeys.cc'] = 'test_hotkeys'
tests['test_hotkey_entry.cc'] = 'test_hotkey_entry'
tests['test_list_select_multi.cc'] = 'test_list_select_multi'
tests['test_list_select_multi_max.cc'] = 'test_list_select_multi_max'

libs = Split("""pthread
	        ncurses
		microhttpd
	     """)
env = Environment(CXX="ccache clang++ -I../.. -I..", CPPFLAGS="-D_FILE_OFFSET_BITS=64 -Wall -g --std=c++11 -pthread", LIBS=libs, CPPPATH="..")
env['ENV']['TERM'] = 'xterm'


Decider('MD5')
for i in tests:
	env.Program(source = ['tests/' + i] + common, target = tests[i])

