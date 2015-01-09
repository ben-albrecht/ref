== General ==

# Storage usage
du -c
du -cs <directory>

== Torque PBS ==
# List jobs
jobs -l

# List my jobs
qstat -u bja39

# Check job status
checkjob <ID>
showstart <ID>

# show queue info
qstat -q <queue>
qstat -Q <queue>
frank-avail <queue>



# Summary of balance
showq -w user=bja39
mybalance -h

# Watch wall progress (updated every 10 sec)
watch --interval=10 qstat -u bja39

# Kill job on wall
qdel [Job number]

# Interactive node
qsub -I -q ishared  -l nodes=1:ppn=8,walltime=0:10:00
