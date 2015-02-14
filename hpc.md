# Frank Info
== Job Queues ==
Initial = 100900 (investor = 100000)

Priority = Initial
 + 200 * number of CPUs
 + 100 * XFactor
 +  10 * minutes in Idle state

* XFactor =  1 + <Queued Time> / <Requested Wall time>

* Priority only increases for top 10 jobs in status = Q per queue.
* There is a max number of CPUs allowed to be run per user per queue
    * shared = 96
    * shared_large = 96
    * shared_heavy = 2 jobs max, 16 cores per jobs
    * distributed = 144
    * dist_small = 288
    * dist_big = 288
    * dist_fast = 192
    * dist_ivy 160
    * mem48g = no limit!!

    * ib = 128


== Queue Info ==
=== Recommended ===
* mem48g ppn=[1-12] mem=[4-48gb]
* dist_ivy ppn=16
* dist_big ppn=16
* dist_small ppn=16
* dist_fast ppn=16
* test

* request access to shared_heavy and ib


## Dumped data

=== Shared Memory ===
Queue: shared
Max: 144 hours
15 quad-socket 12-core AMD Magny Cours (6172) 2.1 GHz CPU (48 core) nodes. They have 125 GB of memory and 1 TB of local disk.

Queue: shared_large
8 dual-socket 8-core Intel Sandy Bridge (E5-2670) 2.6 GHz (16 core) nodes. They have 63 GB of memory and 2 TB of local disk.

shared_heavy
2 dual-socket 8-core Intel Sandy Bridge (E5-2670) 2.6 GHz (16 core) nodes. They have 126 GB of memory and 3 TB of local disk. Queue:

shared_amd
2 quad-socket 16-core AMD Interlagos (Opteron 6276) 2.3 GHz nodes. They have 256 GB of RAM and 2 TB of local scratch. Queue:


=== Distributed Memory ===
Queues: distributed, jordan
40 dual-socket 6-core Intel Westmere (X5650) 2.67 GHz CPU (12 core) nodes and 48 GB of memory. All nodes are connected by QDR InfiniBand.

Queue: dist_small
36 dual-socket 8-core Intel Sandy Bridge (E5-2670) 2.6 GHz (16 core) nodes. They have 31 GB of memory, 1 TB of local disk and are connected by QDR InfiniBand.

Queue: dist_big
36 dual-socket 8-core Intel Sandy Bridge (E5-2670) 2.6 GHz (16 core) nodes. They have 63 GB of memory, 1 TB of local disk and are connected by QDR InfiniBand.

Queue: dist_amd, amd_compbio
36 quad-socket 16-core AMD Interlagos (Opteron 6276) 2.3 GHz nodes. They have 128 GB of RAM. All nodes are connected by QDR Infiniband and have 2 TB of local scratch. Queues:

Queue: shared_amd, amd_compbio
24 quad-socket 16-core AMD Interlagos (Opteron 6276) 2.3 GHz nodes. They have 256 GB of RAM. Both nodes are connected by QDR Infiniband and have 2 TB of local scratch. Queues:

Queue: dist_fast
24 dual-socket 8-core Intel Sandy Bridge (E5-2670) 2.6 GHz (16 core) nodes. They have 128 GB of memory, 1 TB of local disk and are connected by FDR InfiniBand. Queue:

Queue: dist_ivy
20 dual-socket 8-core Intel Ivy Bridge (E5-2650v2) 2.6 GHz (16 core) nodes. They have 64 GB of memory, 1 TB of local disk and are connected by FDR InfiniBand. Queue:

===  Legacy and Specialty Hardware ===
Queues: mem24g, mem48g, ib, one_day.
110 dual-socket 4-core Intel Nehalem CPU (12 core) nodes with varying amounts of memory and local disk.

Queue: test
Max: 1 hour

=== GPU ===
Queue: gpu
12 NVIDIA Tesla C2050 GPGPUs (1.15 GHz) each with 448 cores and 2 GB of memory.

Queue: gpu
4 NVIDIA Telsa C2075 GPGPUs (1.15 GHz) each with 448 cores and 6 GB of memory.

Queue: gpu
24 NVIDIA GTX Titan GPGPUs (837 MHz) each with 2688 cores and 6 GB of memory.


# Commands

## Storage usage
du -c
du -cs <directory>

== Torque PBS ==
## List jobs
jobs -l

## List my jobs
qstat -u bja39

## Check job status
checkjob <ID>
showstart <ID>

## show queue info
qstat -q <queue>
qstat -Q <queue>
frank-avail <queue>



## Summary of balance
showq -w user=bja39
mybalance -h

## Watch wall progress (updated every 10 sec)
watch --interval=10 qstat -u bja39

## Kill job on wall
qdel [Job number]

## Interactive node
qsub -I -q ishared  -l nodes=1:ppn=8,walltime=0:10:00
