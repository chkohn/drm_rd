# This is a generated script based on design: system_top
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
#
# To test this script, run the following commands from Vivado Tcl console:
# source system_top_script.tcl

# If you do not already have a project created,
# you can create a project using the following command:
#    create_project project_1 myproj -part xc7vx485tffg1157-1 -force

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design system_top

# Creating design if needed
if { [get_files *.bd] eq "" } {
   puts "INFO: Currently there are no designs in project, so creating one..."
   create_bd_design system_top
}


# Top level instance
current_bd_instance

# Create interface ports
set DDR [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddrx_rtl:1.0 DDR ]
set FIXED_IO [ create_bd_intf_port -mode Master -vlnv xilinx.com:display_processing_system7:fixedio_rtl:1.0 FIXED_IO ]

# Create ports
set hdmi_data [ create_bd_port -dir O -from 15 -to 0 hdmi_data ]
set hdmi_hsync [ create_bd_port -dir O hdmi_hsync ]
set hdmi_vsync [ create_bd_port -dir O hdmi_vsync ]
set hdmi_de [ create_bd_port -dir O hdmi_de ]
set hdmi_int [ create_bd_port -dir I -type intr hdmi_int ]
set_property -dict [ list CONFIG.SENSITIVITY {LEVEL_HIGH}  ] $hdmi_int
set video_clk [ create_bd_port -dir I -type clk video_clk ]
set_property -dict [ list CONFIG.FREQ_HZ {148500000} CONFIG.PHASE {0.000} CONFIG.CLK_DOMAIN {system_top_video_clk}  ] $video_clk
set hdmi_clk [ create_bd_port -dir O hdmi_clk ]

# Create instance: processing_system7_1, and set properties
set processing_system7_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.2 processing_system7_1 ]
set_property -dict [ list CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ {150} CONFIG.PCW_USE_S_AXI_HP0 {1} CONFIG.PCW_USE_FABRIC_INTERRUPT {1} CONFIG.PCW_EN_CLK1_PORT {1} CONFIG.PCW_EN_RST1_PORT {1} CONFIG.PCW_IRQ_F2P_INTR {1} CONFIG.PCW_ENET0_PERIPHERAL_ENABLE {0} CONFIG.Component_Name {system_top_processing_system7_1_0}  ] $processing_system7_1

# Create instance: axi_interconnect_gp0, and set properties
set axi_interconnect_gp0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.0 axi_interconnect_gp0 ]
set_property -dict [ list CONFIG.NUM_MI {5}  ] $axi_interconnect_gp0

# Create instance: proc_sys_reset, and set properties
set proc_sys_reset [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset ]

# Create instance: v_axi4s_vid_out_1, and set properties
set v_axi4s_vid_out_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_axi4s_vid_out:3.0 v_axi4s_vid_out_1 ]
set_property -dict [ list CONFIG.RAM_ADDR_BITS {5} CONFIG.VTG_MASTER_SLAVE {1}  ] $v_axi4s_vid_out_1

# Create instance: v_tc_1, and set properties
set v_tc_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_tc:6.0 v_tc_1 ]
set_property -dict [ list CONFIG.HAS_AXI4_LITE {true} CONFIG.VIDEO_MODE {1080p}  ] $v_tc_1

# Create instance: v_tpg_1, and set properties
set v_tpg_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_tpg:5.0 v_tpg_1 ]
set_property -dict [ list CONFIG.has_axi4_lite {true} CONFIG.pattern_control {9} CONFIG.s_video_format {2} CONFIG.has_axi4s_slave {false}  ] $v_tpg_1

# Create instance: axi_vdma_1, and set properties
set axi_vdma_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vdma:6.0 axi_vdma_1 ]
set_property -dict [ list CONFIG.c_m_axis_mm2s_tdata_width {32} CONFIG.c_s_axis_s2mm_tdata_width {32} CONFIG.c_mm2s_genlock_mode {3} CONFIG.c_s2mm_genlock_mode {2} CONFIG.c_mm2s_linebuffer_depth {1024} CONFIG.c_s2mm_linebuffer_depth {1024} CONFIG.c_mm2s_max_burst_length {16} CONFIG.c_s2mm_max_burst_length {16}  ] $axi_vdma_1

# Create instance: v_rgb2ycrcb_1, and set properties
set v_rgb2ycrcb_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_rgb2ycrcb:7.0 v_rgb2ycrcb_1 ]
set_property -dict [ list CONFIG.HAS_AXI4_LITE {true}  ] $v_rgb2ycrcb_1

# Create instance: v_cresample_1, and set properties
set v_cresample_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_cresample:4.0 v_cresample_1 ]
set_property -dict [ list CONFIG.has_axi4_lite {true} CONFIG.s_axis_video_format {3} CONFIG.m_axis_video_format {2} CONFIG.convert_type {2}  ] $v_cresample_1

# Create instance: axi_interconnect_hp0, and set properties
set axi_interconnect_hp0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.0 axi_interconnect_hp0 ]
set_property -dict [ list CONFIG.NUM_SI {2} CONFIG.NUM_MI {1}  ] $axi_interconnect_hp0

# Create instance: xlconcat_1, and set properties
set xlconcat_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:1.0 xlconcat_1 ]
set_property -dict [ list CONFIG.NUM_PORTS {3}  ] $xlconcat_1

# Create instance: axis_subset_converter_1, and set properties
set axis_subset_converter_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.0 axis_subset_converter_1 ]
set_property -dict [ list CONFIG.S_TDATA_NUM_BYTES {4} CONFIG.M_TDATA_NUM_BYTES {3} CONFIG.S_TUSER_WIDTH {1} CONFIG.M_TUSER_WIDTH {1} CONFIG.S_HAS_TREADY {1} CONFIG.S_HAS_TKEEP {0} CONFIG.S_HAS_TLAST {1} CONFIG.M_HAS_TREADY {1} CONFIG.M_HAS_TLAST {1} CONFIG.TDATA_REMAP {tdata[23:16],tdata[7:0],tdata[15:8]}  ] $axis_subset_converter_1

# Create instance: xlslice_23_16, and set properties
set xlslice_23_16 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_23_16 ]
set_property -dict [ list CONFIG.DIN_TO {16} CONFIG.DIN_FROM {23} CONFIG.DIN_WIDTH {24}  ] $xlslice_23_16

# Create instance: xlslice_15_8, and set properties
set xlslice_15_8 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_15_8 ]
set_property -dict [ list CONFIG.DIN_TO {8} CONFIG.DIN_FROM {15} CONFIG.DIN_WIDTH {24}  ] $xlslice_15_8

# Create instance: xlslice_7_0, and set properties
set xlslice_7_0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_7_0 ]
set_property -dict [ list CONFIG.DIN_FROM {7} CONFIG.DIN_WIDTH {24}  ] $xlslice_7_0

# Create instance: xlconcat_2, and set properties
set xlconcat_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:1.0 xlconcat_2 ]
set_property -dict [ list CONFIG.NUM_PORTS {4}  ] $xlconcat_2

# Create instance: xlconstant_1, and set properties
set xlconstant_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.0 xlconstant_1 ]
set_property -dict [ list CONFIG.CONST_WIDTH {8} CONFIG.CONST_VAL {0}  ] $xlconstant_1

# Create instance: xlconstant_2, and set properties
set xlconstant_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.0 xlconstant_2 ]

# Create interface connections
connect_bd_intf_net -intf_net processing_system7_1_m_axi_gp0 [get_bd_intf_pins processing_system7_1/M_AXI_GP0] [get_bd_intf_pins axi_interconnect_gp0/S00_AXI]
connect_bd_intf_net -intf_net processing_system7_1_axi_periph_m01_axi [get_bd_intf_pins axi_interconnect_gp0/M01_AXI] [get_bd_intf_pins axi_vdma_1/S_AXI_LITE]
connect_bd_intf_net -intf_net v_tc_1_vtiming_out [get_bd_intf_pins v_tc_1/vtiming_out] [get_bd_intf_pins v_axi4s_vid_out_1/vtiming_in]
connect_bd_intf_net -intf_net s00_axi_1 [get_bd_intf_pins axi_interconnect_hp0/S00_AXI] [get_bd_intf_pins axi_vdma_1/M_AXI_MM2S]
connect_bd_intf_net -intf_net axi_vdma_1_m_axi_s2mm [get_bd_intf_pins axi_vdma_1/M_AXI_S2MM] [get_bd_intf_pins axi_interconnect_hp0/S01_AXI]
connect_bd_intf_net -intf_net axi_interconnect_1_m00_axi [get_bd_intf_pins processing_system7_1/S_AXI_HP0] [get_bd_intf_pins axi_interconnect_hp0/M00_AXI]
connect_bd_intf_net -intf_net v_rgb2ycrcb_1_video_out [get_bd_intf_pins v_rgb2ycrcb_1/video_out] [get_bd_intf_pins v_cresample_1/video_in]
connect_bd_intf_net -intf_net v_cresample_1_video_out [get_bd_intf_pins v_cresample_1/video_out] [get_bd_intf_pins v_axi4s_vid_out_1/video_in]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m00_axi [get_bd_intf_pins axi_interconnect_gp0/M00_AXI] [get_bd_intf_pins v_tc_1/ctrl]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m02_axi [get_bd_intf_pins axi_interconnect_gp0/M02_AXI] [get_bd_intf_pins v_tpg_1/ctrl]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m03_axi [get_bd_intf_pins axi_interconnect_gp0/M03_AXI] [get_bd_intf_pins v_cresample_1/ctrl]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m04_axi [get_bd_intf_pins axi_interconnect_gp0/M04_AXI] [get_bd_intf_pins v_rgb2ycrcb_1/ctrl]
connect_bd_intf_net -intf_net axi_vdma_1_m_axis_mm2s [get_bd_intf_pins axi_vdma_1/M_AXIS_MM2S] [get_bd_intf_pins axis_subset_converter_1/S_AXIS]
connect_bd_intf_net -intf_net axis_subset_converter_1_m_axis [get_bd_intf_pins axis_subset_converter_1/M_AXIS] [get_bd_intf_pins v_rgb2ycrcb_1/video_in]
connect_bd_intf_net -intf_net processing_system7_1_ddr [get_bd_intf_ports DDR] [get_bd_intf_pins processing_system7_1/DDR]
connect_bd_intf_net -intf_net processing_system7_1_fixed_io [get_bd_intf_ports FIXED_IO] [get_bd_intf_pins processing_system7_1/FIXED_IO]
connect_bd_intf_net -intf_net v_tpg_1_video_out [get_bd_intf_pins v_tpg_1/video_out] [get_bd_intf_pins axi_vdma_1/S_AXIS_S2MM]

# Create port connections
connect_bd_net -net processing_system7_1_fclk_clk0 [get_bd_pins processing_system7_1/FCLK_CLK0] [get_bd_pins processing_system7_1/M_AXI_GP0_ACLK] [get_bd_pins axi_interconnect_gp0/S00_ACLK] [get_bd_pins proc_sys_reset/slowest_sync_clk] [get_bd_pins axi_interconnect_gp0/ACLK] [get_bd_pins axi_interconnect_gp0/M00_ACLK] [get_bd_pins axi_vdma_1/s_axi_lite_aclk] [get_bd_pins axi_interconnect_gp0/M01_ACLK] [get_bd_pins v_cresample_1/s_axi_aclk] [get_bd_pins axi_interconnect_gp0/M02_ACLK] [get_bd_pins v_tc_1/s_axi_aclk] [get_bd_pins axi_interconnect_gp0/M03_ACLK] [get_bd_pins v_tpg_1/s_axi_aclk] [get_bd_pins axi_interconnect_gp0/M04_ACLK] [get_bd_pins v_rgb2ycrcb_1/s_axi_aclk]
connect_bd_net -net processing_system7_1_fclk_reset0_n [get_bd_pins processing_system7_1/FCLK_RESET0_N] [get_bd_pins proc_sys_reset/ext_reset_in]
connect_bd_net -net proc_sys_reset_peripheral_aresetn [get_bd_pins proc_sys_reset/peripheral_aresetn] [get_bd_pins axi_interconnect_gp0/S00_ARESETN] [get_bd_pins axi_interconnect_gp0/M00_ARESETN] [get_bd_pins axi_vdma_1/axi_resetn] [get_bd_pins axi_interconnect_gp0/M01_ARESETN] [get_bd_pins v_cresample_1/s_axi_aresetn] [get_bd_pins axi_interconnect_gp0/M02_ARESETN] [get_bd_pins v_tc_1/s_axi_aresetn] [get_bd_pins axi_interconnect_gp0/M03_ARESETN] [get_bd_pins v_tpg_1/s_axi_aresetn] [get_bd_pins axi_interconnect_gp0/M04_ARESETN] [get_bd_pins v_rgb2ycrcb_1/s_axi_aresetn]
connect_bd_net -net proc_sys_reset_interconnect_aresetn [get_bd_pins proc_sys_reset/interconnect_aresetn] [get_bd_pins axi_interconnect_gp0/ARESETN]
connect_bd_net -net v_axi4s_vid_out_1_vtg_ce [get_bd_pins v_axi4s_vid_out_1/vtg_ce] [get_bd_pins v_tc_1/gen_clken]
connect_bd_net -net processing_system7_1_fclk_reset1_n [get_bd_pins processing_system7_1/FCLK_RESET1_N] [get_bd_pins axi_interconnect_hp0/ARESETN] [get_bd_pins axi_interconnect_hp0/S00_ARESETN] [get_bd_pins axi_interconnect_hp0/M00_ARESETN] [get_bd_pins axi_interconnect_hp0/S01_ARESETN]
connect_bd_net -net processing_system7_1_fclk_clk1 [get_bd_pins processing_system7_1/FCLK_CLK1] [get_bd_pins processing_system7_1/S_AXI_HP0_ACLK] [get_bd_pins axi_vdma_1/m_axi_mm2s_aclk] [get_bd_pins axi_vdma_1/m_axi_s2mm_aclk] [get_bd_pins axi_interconnect_hp0/ACLK] [get_bd_pins axi_interconnect_hp0/S00_ACLK] [get_bd_pins axi_interconnect_hp0/M00_ACLK] [get_bd_pins axi_interconnect_hp0/S01_ACLK] [get_bd_pins v_tpg_1/aclk] [get_bd_pins v_cresample_1/aclk] [get_bd_pins v_rgb2ycrcb_1/aclk] [get_bd_pins axi_vdma_1/s_axis_s2mm_aclk] [get_bd_pins axi_vdma_1/m_axis_mm2s_aclk] [get_bd_pins v_axi4s_vid_out_1/aclk] [get_bd_pins axis_subset_converter_1/aclk]
connect_bd_net -net v_axi4s_vid_out_1_vid_data [get_bd_ports hdmi_data] [get_bd_pins v_axi4s_vid_out_1/vid_data]
connect_bd_net -net v_axi4s_vid_out_1_vid_hsync [get_bd_ports hdmi_hsync] [get_bd_pins v_axi4s_vid_out_1/vid_hsync]
connect_bd_net -net v_axi4s_vid_out_1_vid_vsync [get_bd_ports hdmi_vsync] [get_bd_pins v_axi4s_vid_out_1/vid_vsync]
connect_bd_net -net v_axi4s_vid_out_1_vid_active_video [get_bd_ports hdmi_de] [get_bd_pins v_axi4s_vid_out_1/vid_active_video]
connect_bd_net -net axi_vdma_1_s2mm_introut [get_bd_pins axi_vdma_1/s2mm_introut] [get_bd_pins xlconcat_1/In1]
connect_bd_net -net hdmi_int_1 [get_bd_ports hdmi_int] [get_bd_pins xlconcat_1/In2]
connect_bd_net -net axi_vdma_1_mm2s_introut [get_bd_pins axi_vdma_1/mm2s_introut] [get_bd_pins xlconcat_1/In0]
connect_bd_net -net xlconcat_1_dout [get_bd_pins xlconcat_1/dout] [get_bd_pins processing_system7_1/IRQ_F2P]
connect_bd_net -net video_clk_1 [get_bd_ports video_clk] [get_bd_ports hdmi_clk] [get_bd_pins v_tc_1/clk] [get_bd_pins v_axi4s_vid_out_1/vid_io_out_clk]
connect_bd_net -net v_tpg_1_m_axis_video_tdata [get_bd_pins v_tpg_1/m_axis_video_tdata] [get_bd_pins xlslice_23_16/Din] [get_bd_pins xlslice_15_8/Din] [get_bd_pins xlslice_7_0/Din]
connect_bd_net -net xlslice_15_8_dout [get_bd_pins xlslice_15_8/Dout] [get_bd_pins xlconcat_2/In3]
connect_bd_net -net xlslice_7_0_dout [get_bd_pins xlslice_7_0/Dout] [get_bd_pins xlconcat_2/In2]
connect_bd_net -net xlslice_23_16_dout [get_bd_pins xlslice_23_16/Dout] [get_bd_pins xlconcat_2/In1]
connect_bd_net -net xlconstant_1_const [get_bd_pins xlconstant_1/const] [get_bd_pins xlconcat_2/In0]
connect_bd_net -net xlconcat_2_dout [get_bd_pins xlconcat_2/dout] [get_bd_pins axi_vdma_1/s_axis_s2mm_tdata]
connect_bd_net -net xlconstant_2_const [get_bd_pins xlconstant_2/const] [get_bd_pins axis_subset_converter_1/aresetn]

# Create address segments
create_bd_addr_seg -range 0x10000 -offset 0x43000000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs axi_vdma_1/S_AXI_LITE/Reg] SEG2
create_bd_addr_seg -range 0x10000 -offset 0x43C00000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_tc_1/ctrl/Reg] SEG1
create_bd_addr_seg -range 0x10000 -offset 0x43C10000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_tpg_1/ctrl/Reg] SEG3
create_bd_addr_seg -range 0x10000 -offset 0x43C20000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_cresample_1/ctrl/Reg] SEG4
create_bd_addr_seg -range 0x10000 -offset 0x43C30000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_rgb2ycrcb_1/ctrl/Reg] SEG5
create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces axi_vdma_1/Data_MM2S] [get_bd_addr_segs processing_system7_1/S_AXI_HP0/HP0_DDR_LOWOCM] SEG1
create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces axi_vdma_1/Data_S2MM] [get_bd_addr_segs processing_system7_1/S_AXI_HP0/HP0_DDR_LOWOCM] SEG2
