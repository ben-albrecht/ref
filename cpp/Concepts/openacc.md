
General OpenACC usage, acts on the next scope (e.g. for loop)
OpenACC directive, tells compiler to break up next scope (e.g. for loop)
into separate GPU Streaming Multiprocessors (SMs)
#pragma acc kernels[clauses..]

Data Directive / Data Regions (usage detailed in examples)
#pragma acc data [clauses..]
  Possible Clauses:
    #pragma acc data copy(list){  }
      Copies 'list' from host (CPU) to device (GPU) so that
      'list' is not copied back and forth numerous times
      *Be Careful!* Things done by CPU to 'list' inside this scope
      will be overwritten when 'list' is copied back.

Parallel Regions


  Device Tuning
    #pragma acc parallel loop \
         device_type(nvidia) num_gangs(200) ...\
         device_type(radeon) num_gangs(400) ...

Aug-13-2013
    

PSC OpenACC Workshop
    By John Urbanic
        Parallel Computing Specialist with PSC
OpenACC was developed by Cray, CAPS, Nvidia and PGI.
It began development in 2010 by PGI, and was into existence by 2011

"Parallel Computing:"
    FLOPS vs. Memory Size
    Currently ~TFLOPS (10^12) with a PFLOPS (10^15) limit, aiming towards exascale (10^18) FLOPS
    Currently ~MWORDS (10^6) with a TWORDS (10^15) limit 

    Performance Benchmarks:
        Serial Benchmarks took a right turn ~2004 (fell off linear fit)

    Biggest culprit in performance growth decline
        Memory speeds are slow

    Moore's Law
      Density of transistors on a CPU chip doubles every 2 years (also measured in feature size, frequency, and CPU power)
      It is not dead, and will continue for at least through 2018
      It cannot continue forever (transistors will reach single-atom width)
      The Problem:
        CPU power dissipation trend is the least sustainable, which is why we do parallel computing now
        Since 2004, clock rates have leveled off
        Watts per sq cm dissipated have reached hotter than a hot plate (~60-70 watts/cm^2)
      The Solution: 
        P = C * V^2 * Frequency
        Frequency ~ Voltage
        Power ~ Voltage^3
        C ~ Transistor Switching
        We need a way to get more performance from same amount of transistors without altering power
        Parallelizing cores increases efficiency:
            (15% reduction in voltage, frequency, double area (2 cores instead of 1),
            180% increase in performance, same amount of power)        

    Shared Memory vs. Distributed Memory
      Shared: OpenMP; All cores referring to global memory (implicit communication)
      Distributed: MPI; Each core has its own cpu/memory (explicit communication)

    Accelerated Computing (considered an alternative type of computing infrastructure)
      OpenACC;
      Accelerator = GPU computing, Xeon-Phi machines (Intel)
      Memory transfer over a memory bus to GPU (rate limiting step typically)
      
    Everything is multi-core now.
    Terminology
      Cores: On an intel chip, # of cores = # of PEs
      Nodes: Physical blade or motherboard which often carries multiple processors
      Processors: Processors can be multi-core, so processors != PEs often
      PE: Processing Element - Smallest useful computing device

    Motherboards:
      dual/quad socket boards common in HPC, but not typical in PCs

    Network types: (Low -> High connectivity) - Matters for Parallelism
        Ethernet (sucks)
        Complete Connectivity (everything goes to everything)
        Crossbar (central network hub - only modest sized clusters use)
        Binary Tree (Larger clusters, top end of network still stressed)
        Fat Trees (Higher level of trees have greater bandwidth)
        3-D Torus (ends wrap around and are connected, no real boundary)
      Most large clusters use a Fat tree or 3-D Torus

    GPU Architecture
      2 Main Components:
        Global memory:
            - analogous to RAM in CPU
            - accessible to GPU and CPU
            - mem up to 24GB, bandwidth up to 288GB/s, ECC on/off
        Streaming Multiprocessors (SMs):
            -Perform computations  
            -Each SM has control units, registers, execution pipelines, and caches

    3 Main Architectures of HPC:
        Multicore: Maintain complex cores and replicate (sustained)
        Manycore/Embedded: Many simpler cores from embedded (falling off)
        GPU/Accelerator: Highly specialized GPUs (growing)
        
    By 2018, bit movement will be largest constraint in performance growth (takes too much power)
    By 2020, the human brain (20W) will still be many million times more efficient than top supercomputers (20-30MW)

    Other Topics:
        1. Scaling
        2. Amdahl's Law
            -If there is x% of code that is serial,
            program can not be parallelized to increase speed to faster than 100/x original speed
        3. Paradigms
            -MPI has been the only parallel paradigm that has stuck around uninterrupted by paradigm shifts
                -low-level hard to code
            -Data Parallel (fortran90), based on data array operations.
                -treat arrays as single variables, but does the individual operations parallelized over processors
                -Forces code into nice array operations (irregular meshes poor with this)
            -OpenMP very closely related to OpenACC
            -PGAS (Partitioned Global Address Synchronization) Co-array synchronization 
            -Frameworks, e.g. Charm++
            -Hybrid Coding is combination of several types of parallelization, e.g. OpenACC+MPI or OpenMP+MPI
        4. Data Decomposition
        5. Load Balancing

"Introduction to OpenACC"
    It is a directive based standard to allow developers to take
    advantage of accelerators such as GPUs
    
    Directive
        Suggestion made to compiler
        #pragma acc kernels
        Before a for loop, suggests to a compiler (with the proper 
        flags) to divide this loop along multiple cores
        Alternatives to directive-based GPU implementations:
            - Programming Languages (CUDA) - Maximum flexibility
            - Libraries (drop-in) - Minimum Flexibility
        Advantages of directive-based approach:
            -High level, no OpenCL, CUDA, etc.
            -Single source, no forking off separate GPU code
            -Efficient - Would gain nearly nothing by writing pure CUDA code (because the compilers are THAT good)
            -Performance portable
            -Incremental (complete rewrite of program is not necessary)
        
    Pragmas in C
        A comment that a compiler will ignore unless given a certain flag and told to look for it 

"General OpenACC Usage for C"
    #pragma acc kernels [clause ...]
    The next structured block or line is what this pragma statement applies to 
    
    restrict keyword for pointers:


    Compiling
        pgcc –acc -ta=nvidia -Minfo=accel foo.c
        -acc   =>
        -ta    => Architecture
        -Minfo => Want additional information about how well code was accelerated

    Why we can't put acc kernals on every for loop:
        - Data Dependency
            If loop iterations have partial or full dependency on other iterations,
            human intervention is required
            Compiler will throw compiler errors at us if it even suspects data dependencies
                Overcome this by:
                    1. Making data independence more obvious to compiler
                    2. Remove unneccessary data dependence in code
                    3. Override compiler's judgement (independent clause) and risk failure
            restrict keyword is a way to get around the fact that a pointer could point to something 
            that is would impose data dependence
            >float *restrict ptr
            #Meaning: “for the lifetime of ptr, only it or a value directly derived from it 
            # (such as ptr + 1) will be used to access the object to which it points”
        - Data movement
            Moving data across the PCI bus (CPI <=> GPU) is VERY SLOW
            CPU <=> CPU memory is fast
            GPU <=> GPU memory is the fastest
            Host: CPU chip
            Device: GPU card
            Overcome this by:
              Data management
                #pragma acc data [clause...]
                clauses
                  copy
                  copyin 
                  copyout
                  create

                  present (data is already present)
                  present_or_copy
                  present_or_copyin
                  present_or_copyout
                  present_or_create

"Advanced OpenACC"
    At some point, we may want to further optimize our code with compiler
    which requires knowledge of specific GPU architecture.
    GPU Families:
        -Fermi
        -Kepler     
    GPU Architectures change very quickly
    
    OpenACC Task Granularity
        3 levels: gang > worker > vector
        Each gang has a number of workers
        Each worker has a vector capability (e.g. SSE instructions on an intel chip)
        A GPU thread gets run on a core.
    
    Warps -> Threads
        All threads in a warp must execute the same operation
        A result of this is that if-loops execute poorly in GPUs

Questions - 


1. How do we utilize OpenACC with c++ objects?

2. Could one use OpenACC exclusively through OpenMP4.0?

3. How will Nvdia purchasing PGI affect OpenACC?


