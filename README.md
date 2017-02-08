# minibus
a set of ncurses widgets for console apps

widgets/ListSelect
------------------

Pass a vector<string> and it calls a callback when closed giving the current
selected item's index.


io/Key
------

A wrapper for the return value of getch().

driver/MinibusDriver
--------------------

A driver that takes a set of widget/state/nextstate triples and handles keyboard
input and drawing the screen.

Todo
----

Other widgets: scrolling list, grepping list, form with edit fields. System
monitor, debug log with access keys

Socket interaction for remote client or html front end.
