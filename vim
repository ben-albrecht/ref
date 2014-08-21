# ######### #
#Vi-IMproved#
# ######### #
#
#TODO: writing functions in vim
# FUCK this is hard
#
# Switch to previously closed buffer
:buffer #7

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
#Open Fold

zo
#OR

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
odo 

#Put the changes from current window into the other window.
dp 

#Jump to the next change.
]c 

#Jump to the previous change.
[c 

#Switch to the other split window (CTRL-W CTRL-W does the same
#thing, in case you let go of the CTRL key a bit later)
Ctrl W + w 
