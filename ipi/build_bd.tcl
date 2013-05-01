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
set hdmi_clk [ create_bd_port -dir O hdmi_clk ]
set hdmi_data [ create_bd_port -dir O -from 15 -to 0 hdmi_data ]
set hdmi_hsync [ create_bd_port -dir O hdmi_hsync ]
set hdmi_vsync [ create_bd_port -dir O hdmi_vsync ]
set hdmi_de [ create_bd_port -dir O hdmi_de ]
set hdmi_int [ create_bd_port -dir I -type intr hdmi_int ]
set_property -dict [ list CONFIG.SENSITIVITY {LEVEL_HIGH}  ] $hdmi_int

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
set_property -dict [ list CONFIG.has_axi4_lite {true} CONFIG.pattern_control {9} CONFIG.s_video_format {2}  ] $v_tpg_1

# Create instance: axi_vdma_1, and set properties
set axi_vdma_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vdma:6.0 axi_vdma_1 ]
set_property -dict [ list CONFIG.c_m_axis_mm2s_tdata_width {32} CONFIG.c_s_axis_s2mm_tdata_width {24} CONFIG.c_mm2s_genlock_mode {1} CONFIG.c_s2mm_genlock_mode {0} CONFIG.c_mm2s_linebuffer_depth {512}  ] $axi_vdma_1

# Create instance: v_rgb2ycrcb_1, and set properties
set v_rgb2ycrcb_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_rgb2ycrcb:7.0 v_rgb2ycrcb_1 ]

# Create instance: v_cresample_1, and set properties
set v_cresample_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_cresample:4.0 v_cresample_1 ]
set_property -dict [ list CONFIG.has_axi4_lite {true} CONFIG.s_axis_video_format {3} CONFIG.m_axis_video_format {2} CONFIG.convert_type {2}  ] $v_cresample_1

# Create instance: axi_interconnect_hp0, and set properties
set axi_interconnect_hp0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.0 axi_interconnect_hp0 ]
set_property -dict [ list CONFIG.NUM_SI {2} CONFIG.NUM_MI {1}  ] $axi_interconnect_hp0

# Create instance: clk_wiz_1, and set properties
set clk_wiz_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:5.0 clk_wiz_1 ]
#set_property -dict [ list CONFIG.USE_PHASE_ALIGNMENT {false} CONFIG.PRIM_SOURCE {Global_buffer} CONFIG.PRIM_IN_FREQ {50.000} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {148.5000} CONFIG.USE_LOCKED {false} CONFIG.USE_RESET {false}] $clk_wiz_1
set_property -dict [ list CONFIG.USE_PHASE_ALIGNMENT {false} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {148.5000} CONFIG.PRIM_SOURCE {Global_buffer} CONFIG.USE_LOCKED {false} CONFIG.USE_RESET {false}  ] $clk_wiz_1

# Create instance: xlconcat_1, and set properties
set xlconcat_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:1.0 xlconcat_1 ]
set_property -dict [ list CONFIG.NUM_PORTS {3}  ] $xlconcat_1

# Create interface connections
connect_bd_intf_net -intf_net processing_system7_1_m_axi_gp0 [get_bd_intf_pins processing_system7_1/M_AXI_GP0] [get_bd_intf_pins axi_interconnect_gp0/S00_AXI]
connect_bd_intf_net -intf_net processing_system7_1_axi_periph_m01_axi [get_bd_intf_pins axi_interconnect_gp0/M01_AXI] [get_bd_intf_pins axi_vdma_1/S_AXI_LITE]
connect_bd_intf_net -intf_net v_tc_1_vtiming_out [get_bd_intf_pins v_tc_1/vtiming_out] [get_bd_intf_pins v_axi4s_vid_out_1/vtiming_in]
connect_bd_intf_net -intf_net v_tpg_1_video_out [get_bd_intf_pins v_tpg_1/video_out] [get_bd_intf_pins axi_vdma_1/S_AXIS_S2MM]
connect_bd_intf_net -intf_net s00_axi_1 [get_bd_intf_pins axi_interconnect_hp0/S00_AXI] [get_bd_intf_pins axi_vdma_1/M_AXI_MM2S]
connect_bd_intf_net -intf_net axi_vdma_1_m_axi_s2mm [get_bd_intf_pins axi_vdma_1/M_AXI_S2MM] [get_bd_intf_pins axi_interconnect_hp0/S01_AXI]
connect_bd_intf_net -intf_net axi_interconnect_1_m00_axi [get_bd_intf_pins processing_system7_1/S_AXI_HP0] [get_bd_intf_pins axi_interconnect_hp0/M00_AXI]
connect_bd_intf_net -intf_net axi_vdma_1_m_axis_mm2s [get_bd_intf_pins v_rgb2ycrcb_1/video_in] [get_bd_intf_pins axi_vdma_1/M_AXIS_MM2S]
connect_bd_intf_net -intf_net v_rgb2ycrcb_1_video_out [get_bd_intf_pins v_rgb2ycrcb_1/video_out] [get_bd_intf_pins v_cresample_1/video_in]
connect_bd_intf_net -intf_net v_cresample_1_video_out [get_bd_intf_pins v_cresample_1/video_out] [get_bd_intf_pins v_axi4s_vid_out_1/video_in]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m00_axi [get_bd_intf_pins axi_interconnect_gp0/M00_AXI] [get_bd_intf_pins v_rgb2ycrcb_1/ctrl]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m02_axi [get_bd_intf_pins axi_interconnect_gp0/M02_AXI] [get_bd_intf_pins v_cresample_1/ctrl]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m03_axi [get_bd_intf_pins axi_interconnect_gp0/M03_AXI] [get_bd_intf_pins v_tc_1/ctrl]
connect_bd_intf_net -intf_net axi_interconnect_gp0_m04_axi [get_bd_intf_pins axi_interconnect_gp0/M04_AXI] [get_bd_intf_pins v_tpg_1/ctrl]
connect_bd_intf_net -intf_net processing_system7_1_ddr [get_bd_intf_ports DDR] [get_bd_intf_pins processing_system7_1/DDR]
connect_bd_intf_net -intf_net processing_system7_1_fixed_io [get_bd_intf_ports FIXED_IO] [get_bd_intf_pins processing_system7_1/FIXED_IO]

# Create port connections
connect_bd_net -net processing_system7_1_fclk_clk0 [get_bd_pins processing_system7_1/FCLK_CLK0] [get_bd_pins processing_system7_1/M_AXI_GP0_ACLK] [get_bd_pins axi_interconnect_gp0/S00_ACLK] [get_bd_pins proc_sys_reset/slowest_sync_clk] [get_bd_pins axi_interconnect_gp0/ACLK] [get_bd_pins axi_interconnect_gp0/M00_ACLK] [get_bd_pins axi_vdma_1/s_axi_lite_aclk] [get_bd_pins axi_interconnect_gp0/M01_ACLK] [get_bd_pins clk_wiz_1/clk_in1] [get_bd_pins v_rgb2ycrcb_1/s_axi_aclk] [get_bd_pins v_cresample_1/s_axi_aclk] [get_bd_pins axi_interconnect_gp0/M02_ACLK] [get_bd_pins v_tc_1/s_axi_aclk] [get_bd_pins axi_interconnect_gp0/M03_ACLK] [get_bd_pins v_tpg_1/s_axi_aclk] [get_bd_pins axi_interconnect_gp0/M04_ACLK]
connect_bd_net -net processing_system7_1_fclk_reset0_n [get_bd_pins processing_system7_1/FCLK_RESET0_N] [get_bd_pins proc_sys_reset/ext_reset_in]
connect_bd_net -net proc_sys_reset_peripheral_aresetn [get_bd_pins proc_sys_reset/peripheral_aresetn] [get_bd_pins axi_interconnect_gp0/S00_ARESETN] [get_bd_pins axi_interconnect_gp0/M00_ARESETN] [get_bd_pins axi_vdma_1/axi_resetn] [get_bd_pins axi_interconnect_gp0/M01_ARESETN] [get_bd_pins v_rgb2ycrcb_1/s_axi_aresetn] [get_bd_pins v_cresample_1/s_axi_aresetn] [get_bd_pins axi_interconnect_gp0/M02_ARESETN] [get_bd_pins v_tc_1/s_axi_aresetn] [get_bd_pins axi_interconnect_gp0/M03_ARESETN] [get_bd_pins v_tpg_1/s_axi_aresetn] [get_bd_pins axi_interconnect_gp0/M04_ARESETN]
connect_bd_net -net proc_sys_reset_interconnect_aresetn [get_bd_pins proc_sys_reset/interconnect_aresetn] [get_bd_pins axi_interconnect_gp0/ARESETN]
connect_bd_net -net v_axi4s_vid_out_1_vtg_ce [get_bd_pins v_axi4s_vid_out_1/vtg_ce] [get_bd_pins v_tc_1/gen_clken]
connect_bd_net -net processing_system7_1_fclk_reset1_n [get_bd_pins processing_system7_1/FCLK_RESET1_N] [get_bd_pins axi_interconnect_hp0/ARESETN] [get_bd_pins axi_interconnect_hp0/S00_ARESETN] [get_bd_pins axi_interconnect_hp0/M00_ARESETN] [get_bd_pins axi_interconnect_hp0/S01_ARESETN]
connect_bd_net -net processing_system7_1_fclk_clk1 [get_bd_pins processing_system7_1/FCLK_CLK1] [get_bd_pins processing_system7_1/S_AXI_HP0_ACLK] [get_bd_pins axi_vdma_1/m_axi_mm2s_aclk] [get_bd_pins axi_vdma_1/m_axi_s2mm_aclk] [get_bd_pins axi_interconnect_hp0/ACLK] [get_bd_pins axi_interconnect_hp0/S00_ACLK] [get_bd_pins axi_interconnect_hp0/M00_ACLK] [get_bd_pins axi_interconnect_hp0/S01_ACLK]
connect_bd_net -net clk_wiz_1_clk_out1 [get_bd_ports hdmi_clk] [get_bd_pins clk_wiz_1/clk_out1] [get_bd_pins axi_vdma_1/m_axis_mm2s_aclk] [get_bd_pins v_rgb2ycrcb_1/aclk] [get_bd_pins axi_vdma_1/s_axis_s2mm_aclk] [get_bd_pins v_cresample_1/aclk] [get_bd_pins v_tc_1/clk] [get_bd_pins v_axi4s_vid_out_1/vid_io_out_clk] [get_bd_pins v_tpg_1/aclk] [get_bd_pins v_axi4s_vid_out_1/aclk]
connect_bd_net -net v_axi4s_vid_out_1_vid_data [get_bd_ports hdmi_data] [get_bd_pins v_axi4s_vid_out_1/vid_data]
connect_bd_net -net v_axi4s_vid_out_1_vid_hsync [get_bd_ports hdmi_hsync] [get_bd_pins v_axi4s_vid_out_1/vid_hsync]
connect_bd_net -net v_axi4s_vid_out_1_vid_vsync [get_bd_ports hdmi_vsync] [get_bd_pins v_axi4s_vid_out_1/vid_vsync]
connect_bd_net -net v_axi4s_vid_out_1_vid_active_video [get_bd_ports hdmi_de] [get_bd_pins v_axi4s_vid_out_1/vid_active_video]
connect_bd_net -net axi_vdma_1_s2mm_introut [get_bd_pins axi_vdma_1/s2mm_introut] [get_bd_pins xlconcat_1/In1]
connect_bd_net -net hdmi_int_1 [get_bd_ports hdmi_int] [get_bd_pins xlconcat_1/In2]
connect_bd_net -net axi_vdma_1_mm2s_introut [get_bd_pins axi_vdma_1/mm2s_introut] [get_bd_pins xlconcat_1/In0]
connect_bd_net -net xlconcat_1_dout [get_bd_pins xlconcat_1/dout] [get_bd_pins processing_system7_1/IRQ_F2P]

# Create address segments
create_bd_addr_seg -range 0x10000 -offset 0x43000000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs axi_vdma_1/S_AXI_LITE/Reg] SEG2
create_bd_addr_seg -range 0x10000 -offset 0x43010000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_cresample_1/ctrl/Reg] SEG3
create_bd_addr_seg -range 0x10000 -offset 0x43020000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_tc_1/ctrl/Reg] SEG4
create_bd_addr_seg -range 0x10000 -offset 0x43030000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_rgb2ycrcb_1/ctrl/Reg] SEG1
create_bd_addr_seg -range 0x10000 -offset 0x43040000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs v_tpg_1/ctrl/Reg] SEG5
create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces axi_vdma_1/Data_MM2S] [get_bd_addr_segs processing_system7_1/S_AXI_HP0/HP0_DDR_LOWOCM] SEG1
create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces axi_vdma_1/Data_S2MM] [get_bd_addr_segs processing_system7_1/S_AXI_HP0/HP0_DDR_LOWOCM] SEG2
