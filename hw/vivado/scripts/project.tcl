set version "2013.2"
set project_name "zynq_v4l2_rd_${version}"
set project_dir "project"
set ip_dir "srcs/ip"
set hdl_dir "srcs/hdl"
set ui_dir "srcs/ui"
set constrs_dir "constrs"
set scripts_dir "scripts"
set bd_name "system_top"
set part "xc7z020clg484-1"
set board "xilinx.com:zynq:zc702:3.0"

# set up project
create_project $project_name $project_dir -part $part -force
set_property board $board [current_project]

# set up IP repo
set_property ip_repo_paths $ip_dir [current_fileset]
update_ip_catalog -rebuild

# set up bd design
create_bd_design $bd_name
source $scripts_dir/build_bd_design.tcl
validate_bd_design
save_bd_design
close_bd_design $bd_name

# set implementation settings
set_property STEPS.PLACE_DESIGN.ARGS.DIRECTIVE SSI_ExtraTimingOpt [get_runs impl_1]
set_property STEPS.ROUTE_DESIGN.ARGS.DIRECTIVE MoreGlobalIterations [get_runs impl_1]

# add hdl sources and xdc constraints to project
add_files -fileset sources_1 -norecurse $hdl_dir/${bd_name}_wrapper.v
add_files -fileset constrs_1 -norecurse $constrs_dir/$bd_name.xdc
update_compile_order -fileset sources_1
update_compile_order -fileset sim_1

# apply UI file
file copy -force $ui_dir/bd_9edf8fa5.ui $project_dir/$project_name.srcs/sources_1/bd/$bd_name/ui/bd_9edf8fa5.ui

# re-open bd design with layout and comments
open_bd_design $project_dir/$project_name.srcs/sources_1/bd/$bd_name/$bd_name.bd
