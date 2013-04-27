set project_name "zc702_adv7511_xil_v"
set project_dir "project"
set repo_dir "../ipi/Avnet_repository"
set bd_name "system_top"
set part "xc7z020clg484-1"
set board "xilinx.com:zynq:zc702:c"

create_project $project_name $project_dir -part $part -force
set_property board $board [current_project]
set_property target_language VHDL [current_project]
create_bd_design $bd_name
#TODO add check if repo_dir is set
set_property ip_repo_paths $repo_dir [current_fileset]
update_ip_catalog
source ./build_bd.tcl
regenerate_bd_layout
save_bd_design
make_wrapper -files [get_files $bd_name.bd] -top
import_files -force -norecurse ./$project_dir/$project_name.srcs/sources_1/bd/$bd_name/hdl/${bd_name}_wrapper.vhd
update_compile_order -fileset sources_1
update_compile_order -fileset sim_1
add_files -fileset constrs_1 -norecurse ./constrs/$bd_name.xdc
import_files -fileset constrs_1 ./constrs/$bd_name.xdc
