CC       = pgcc
CUDA_PATH = /usr/local/pgi/linux86-64/2012/cuda/4.0
CCFLAGS  = -I$(CUDA_PATH)/include -L$(CUDA_PATH)/lib64 -lcudart -lcufft
ACCFLAGS = -acc -ta=nvidia -Minfo=accel -Minline
OMPFLAGS = -fast -mp -Minfo=mp

BIN =  cufft_acc

all: $(BIN)

cufft_acc: cufft_acc.c
	$(CC) $(CCFLAGS) $(ACCFLAGS) -o $@ $<
	
clean:
	$(RM) $(BIN)
