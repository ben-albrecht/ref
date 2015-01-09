== Subversion ==

# Checkout branch
svn checkout/co

# When you are creating a new file or directory, you need to tell the SVN server about it.
svn add

# When you are creating a new file or directory,
#  you generally need to tell the SVN to apply properties to the file in places that have keywords in a special format such as 
#  Date: 2012-07-29 17:46:27 -0600 (Sun, 29 Jul 2012) .
#  Note that the keyword value won't appear in the file until you do an svn commit (see below).
svn propset

# Typically:
svn propset svn:keywords "Date LastChangedBy" /path/to/filename.xml

# When you do an svn commit the file will be deleted from your local sand box immediately as well as from the repository after committing.
svn delete

# This command prints the status of working directories and files. 
#  If you have made local changes, it'll show your locally modified items.
#  If you use the --verbose switch, it will show revision information on every item.
#  With the --show-updates (-u) switch, it will show any server out-of-date information.
svn status

# Update
svn update/up

# Commit
svn commit/ci

# Diff
svn diff

# svn move SRC DEST or svn mv SRC DEST or svn rename SRC DEST or svn ren SRC DEST.
svn move

