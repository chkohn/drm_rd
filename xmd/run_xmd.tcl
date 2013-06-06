# tcl script to init arm and run sdk

fpga -debugdevice devicenr 2 -f system.bit
connect arm hw
source ps7_init.tcl
ps7_init
ps7_post_config
dow simple_output.elf
run
disconnect 64
exit
