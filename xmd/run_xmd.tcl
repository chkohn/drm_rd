# tcl script to init arm and run sdk

fpga -debugdevice devicenr 2 -f system_top_wrapper.bit
connect arm hw
source ps7_init.tcl
ps7_init
init_user
dow simple_output.elf
run
disconnect 64
exit
