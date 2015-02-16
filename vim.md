# ######### #
#Vi-IMproved#
# ######### #
#
#TODO: writing functions in vim
#TODO: make Shift+Tab (in insert mode) delete 4 spaces

# Open files with split
vim -o file1 file2 # Horizontal
vim -O file1 file2 # Vertical

# Sessions
:mksession ~/mysession.vim

:source ~/mysession.vim
# OR
vim -S ~/mysession.vim

# Auto-Indentation
# insert-mode
# indent line
  CTRL-t
# unindent line
  CTRL-d
# normal mode
# indent
>>
# unindent
<<



# sed
:s/foo/bar/g        Change each 'foo' to 'bar' in the current line.
:%s/foo/bar/g       Change each 'foo' to 'bar' in all the lines.
:5,12s/foo/bar/g    Change each 'foo' to 'bar' for all lines from line 5 to line 12 (inclusive).
:'a,'bs/foo/bar/g   Change each 'foo' to 'bar' for all lines from mark a to mark b inclusive (see Note below).
:.,$s/foo/bar/g     Change each 'foo' to 'bar' for all lines from the current line (.) to the last line ($) inclusive.
:.,+2s/foo/bar/g    Change each 'foo' to 'bar' for the current line (.) and the two next lines (+2).
:g/^baz/s/foo/bar/g Change each 'foo' to 'bar' in each line starting with 'baz'.
:'<,'>s/foo/bar/g   When compiled with +visual, change each 'foo' to 'bar' for all lines within a visual selection.
                    Vim automatically appends the visual selection range ('<,'>) for any ex command when you select
                    an area and enter :. Also, see Note below.

# Tabs
:tabs         #list all tabs including their displayed windows
:tabm 0       #move current tab to first
:tabm         #move current tab to last
:tabm {i}     #move current tab to position i+1

:tabn         #go to next tab
:tabp         #go to previous tab
:tabfirst     #go to first tab
:tablast      #go to last tab

# Switch to previously closed buffer
:buffer #  (<num>)
:b#
# e.g. switch to buffer 3
:b3

# List current buffers
:ls

# See value of variable in vim
:set var?

# See value of all defined variables in vim
:set all

#Replace String ( g = global, often times g is default)
:%s/foo/bar/g

#Dollar signs after everything:
:set nolist

# Relops
:set rnu
:set !rnu

#z-folds
# Create fold from outside of file
vim -c "1,2fold| mkview" file.txt

#Create fold (motion)

zf
#Delete Fold
zd
#Delete All Folds
zE

#Open Fold
zo
<Right arrow Key>
#Close Fold

zc
# Search only in open folds

:set fdo-=search
# Perform commands only on lines in open folds

:folddoopen <command>
# e.g. s/old/new/ge

# ##### #
#vimdiff#
# ##### #

#Get changes from other window into the current window.
do

#Put the changes from current window into the other window.
dp

#Jump to the next change.
]c

#Jump to the previous change.
[c

# Turn it off!
:diffoff

#Switch to the other split window (CTRL-W CTRL-W does the same
#thing, in case you let go of the CTRL key a bit later)
Ctrl W + w

== Plugins ==

# Installing YCM on Mac
# Make sure to brew unlink python
# Why did I have a python installation via homebrew anyway?
