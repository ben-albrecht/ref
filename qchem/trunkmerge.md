= Run Test Suite =

== my/branch ==

== the/trunk ==

== Test Merge via dry run == 


= Merge to Trunk =
# In my/branch (bja_2)
svn commit
svn update .
svn merge ^/trunk

== Resolving Conflicts ==
See `svn status help` to find conflicts

== Compile and Test ==
Verify some jobs using the new features work properly


== Final Commit ==
svn commit -m "merge from trunk to branches/bja_2 for density embedding"

== Check-In Queue ==
* Username -- your Trac/SVN login name
* Source Code Branch Name -- insert branch name awesomefeature
* Reference Branch Name -- corresponding branch name in the test references repository. If there are no changes to the test jobs, leave trunk (default), otherwise it's a good idea to use the same branch name in both qchem and qchem_dailyref repositories.
* Email -- enter your e-mail address. Notifications about the job will be sent there.
* Check-in message -- comment on the check-in: a brief description of the feature, ticket numbers, etc.

