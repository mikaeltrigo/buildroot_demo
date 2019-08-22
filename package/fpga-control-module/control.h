#define CHAR_DEV_NAME   "fpga-control"

#define FPGA_START_ADD  0x40000000
#define FPGA_END_ADD    0x40010000

#ifdef FAKE_FPGA
#define FPGA_MEM_SIZE 1024
#else
#define FPGA_MEM_SIZE   (FPGA_END_ADD - FPGA_START_ADD)
#endif
