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


# Hierarchical cell: EMIO_GPIO
proc create_hier_cell_EMIO_GPIO { parentCell nameHier } {

  if { $parentCell eq "" || $nameHier eq "" } {
     puts "ERROR: create_hier_cell_EMIO_GPIO() - Empty argument(s)!"
     return
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins

  # Create pins
  create_bd_pin -dir O -from 0 -to 0 Dout
  create_bd_pin -dir O -from 0 -to 0 Dout1
  create_bd_pin -dir I -from 1 -to 0 Din

  # Create instance: xlslice_1, and set properties
  set xlslice_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_1 ]
  set_property -dict [ list CONFIG.DIN_WIDTH {2}  ] $xlslice_1

  # Create instance: xlslice_2, and set properties
  set xlslice_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlslice:1.0 xlslice_2 ]
  set_property -dict [ list CONFIG.DIN_TO {1} CONFIG.DIN_FROM {1} CONFIG.DIN_WIDTH {2}  ] $xlslice_2

  # Create port connections
  connect_bd_net -net xlslice_1_dout [get_bd_pins Dout] [get_bd_pins xlslice_1/Dout]
  connect_bd_net -net xlslice_2_dout [get_bd_pins Dout1] [get_bd_pins xlslice_2/Dout]
  connect_bd_net -net processing_system7_1_gpio_o [get_bd_pins Din] [get_bd_pins xlslice_2/Din] [get_bd_pins xlslice_1/Din]
  
  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: video_capture
proc create_hier_cell_video_capture { parentCell nameHier } {

  if { $parentCell eq "" || $nameHier eq "" } {
     puts "ERROR: create_hier_cell_video_capture() - Empty argument(s)!"
     return
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:axis_rtl:1.0 video_out
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ctrl
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ctrl1

  # Create pins
  create_bd_pin -dir I -type clk s_axi_aclk
  create_bd_pin -dir I -type clk aclk
  create_bd_pin -dir I -from 0 -to 0 video_sel
  create_bd_pin -dir I -from 15 -to 0 io_hdmii_video
  create_bd_pin -dir I clk
  create_bd_pin -dir I -from 0 -to 0 video_clk_2
  create_bd_pin -dir O irq

  # Create instance: v_tpg_1, and set properties
  set v_tpg_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_tpg:5.0 v_tpg_1 ]
  set_property -dict [ list CONFIG.has_axi4s_slave {true} CONFIG.pattern_control {9} CONFIG.enable_motion {true}  ] $v_tpg_1

  # Create instance: v_vid_in_axi4s_1, and set properties
  set v_vid_in_axi4s_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_vid_in_axi4s:3.0 v_vid_in_axi4s_1 ]
  set_property -dict [ list CONFIG.C_M_AXIS_VIDEO_FORMAT {0}  ] $v_vid_in_axi4s_1

  # Create instance: vsrc_sel_1, and set properties
  set vsrc_sel_1 [ create_bd_cell -type ip -vlnv xilinx.com:user:vsrc_sel:1.0 vsrc_sel_1 ]

  # Create instance: v_tc_1, and set properties
  set v_tc_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_tc:6.0 v_tc_1 ]
  set_property -dict [ list CONFIG.VIDEO_MODE {1080p} CONFIG.enable_detection {true} CONFIG.horizontal_sync_detection {false} CONFIG.auto_generation_mode {false} CONFIG.vertical_sync_detection {false}  ] $v_tc_1

  # Create instance: fmc_imageon_hdmi_in_1, and set properties
  set fmc_imageon_hdmi_in_1 [ create_bd_cell -type ip -vlnv avnet.com:FMC_IMAGEON:fmc_imageon_hdmi_in:2.01.a fmc_imageon_hdmi_in_1 ]

  # Create interface connections
  connect_bd_intf_net -intf_net v_vid_in_axi4s_1_video_out [get_bd_intf_pins v_vid_in_axi4s_1/video_out] [get_bd_intf_pins v_tpg_1/video_in]
  connect_bd_intf_net -intf_net v_tpg_1_video_out [get_bd_intf_pins video_out] [get_bd_intf_pins v_tpg_1/video_out]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m01_axi [get_bd_intf_pins ctrl] [get_bd_intf_pins v_tpg_1/ctrl]
  connect_bd_intf_net -intf_net Conn1 [get_bd_intf_pins ctrl1] [get_bd_intf_pins v_tc_1/ctrl]

  # Create port connections
  connect_bd_net -net processing_system7_1_fclk_clk0 [get_bd_pins s_axi_aclk] [get_bd_pins v_tpg_1/s_axi_aclk] [get_bd_pins v_tc_1/s_axi_aclk]
  connect_bd_net -net processing_system7_1_fclk_clk1 [get_bd_pins aclk] [get_bd_pins v_tpg_1/aclk] [get_bd_pins v_vid_in_axi4s_1/aclk]
  connect_bd_net -net fmc_imageon_hdmi_in_1_video_data [get_bd_pins fmc_imageon_hdmi_in_1/video_data] [get_bd_pins v_vid_in_axi4s_1/vid_data]
  connect_bd_net -net v_tc_1_active_video_out [get_bd_pins v_tc_1/active_video_out] [get_bd_pins vsrc_sel_1/de_1]
  connect_bd_net -net v_tc_1_hsync_out [get_bd_pins v_tc_1/hsync_out] [get_bd_pins vsrc_sel_1/hsync_1]
  connect_bd_net -net v_tc_1_vsync_out [get_bd_pins v_tc_1/vsync_out] [get_bd_pins vsrc_sel_1/vsync_1]
  connect_bd_net -net vsrc_sel_1_video_clk [get_bd_pins vsrc_sel_1/video_clk] [get_bd_pins v_vid_in_axi4s_1/vid_io_in_clk] [get_bd_pins v_tc_1/clk] [get_bd_pins fmc_imageon_hdmi_in_1/clk]
  connect_bd_net -net vsrc_sel_1_hsync [get_bd_pins vsrc_sel_1/hsync] [get_bd_pins v_vid_in_axi4s_1/vid_hsync] [get_bd_pins v_vid_in_axi4s_1/vid_hblank]
  connect_bd_net -net vsrc_sel_1_vsync [get_bd_pins vsrc_sel_1/vsync] [get_bd_pins v_vid_in_axi4s_1/vid_vsync] [get_bd_pins v_vid_in_axi4s_1/vid_vblank]
  connect_bd_net -net vsrc_sel_1_de [get_bd_pins vsrc_sel_1/de] [get_bd_pins v_vid_in_axi4s_1/vid_active_video]
  connect_bd_net -net fmc_imageon_hdmi_in_1_video_vblank [get_bd_pins fmc_imageon_hdmi_in_1/video_vblank] [get_bd_pins v_tc_1/vblank_in] [get_bd_pins vsrc_sel_1/vsync_2]
  connect_bd_net -net fmc_imageon_hdmi_in_1_video_hblank [get_bd_pins fmc_imageon_hdmi_in_1/video_hblank] [get_bd_pins v_tc_1/hblank_in] [get_bd_pins vsrc_sel_1/hsync_2]
  connect_bd_net -net fmc_imageon_hdmi_in_1_video_de [get_bd_pins fmc_imageon_hdmi_in_1/video_de] [get_bd_pins v_tc_1/active_video_in] [get_bd_pins vsrc_sel_1/de_2]
  connect_bd_net -net video_sel_1 [get_bd_pins video_sel] [get_bd_pins vsrc_sel_1/video_sel]
  connect_bd_net -net io_hdmii_video_1 [get_bd_pins io_hdmii_video] [get_bd_pins fmc_imageon_hdmi_in_1/io_hdmii_video]
  connect_bd_net -net clk_1 [get_bd_pins clk] [get_bd_pins vsrc_sel_1/video_clk_2]
  connect_bd_net -net v_tc_1_irq [get_bd_pins irq] [get_bd_pins v_tc_1/irq]
  connect_bd_net -net video_clk_2_1 [get_bd_pins video_clk_2] [get_bd_pins vsrc_sel_1/video_clk_1]
  
  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: video_display
proc create_hier_cell_video_display { parentCell nameHier } {

  if { $parentCell eq "" || $nameHier eq "" } {
     puts "ERROR: create_hier_cell_video_display() - Empty argument(s)!"
     return
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:axis_rtl:1.0 S_AXIS
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ctrl
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ctrl1
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ctrl2
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S_AXI_LITE
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M_AXI_MM2S
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 ctrl3
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M_AXI_MM2S1
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S_AXI_LITE1

  # Create pins
  create_bd_pin -dir I -type clk s_axi_lite_aclk
  create_bd_pin -dir I -type clk vid_io_out_clk
  create_bd_pin -dir I -type clk m_axi_mm2s_aclk
  create_bd_pin -dir O -type intr mm2s_introut
  create_bd_pin -dir O irq
  create_bd_pin -dir O irq1
  create_bd_pin -dir O vid_hsync
  create_bd_pin -dir O vid_active_video
  create_bd_pin -dir O vid_vsync
  create_bd_pin -dir O -from 15 -to 0 vid_data
  create_bd_pin -dir O mm2s_introut1
  create_bd_pin -dir O vid_clk

  # Create instance: axis_subset_converter_1, and set properties
  set axis_subset_converter_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axis_subset_converter:1.0 axis_subset_converter_1 ]
  set_property -dict [ list CONFIG.S_TDATA_NUM_BYTES {4} CONFIG.M_TDATA_NUM_BYTES {3} CONFIG.S_HAS_TSTRB {0} CONFIG.S_HAS_TKEEP {0} CONFIG.M_HAS_TSTRB {0} CONFIG.M_HAS_TKEEP {0} CONFIG.TDATA_REMAP {tdata[23:16],tdata[7:0],tdata[15:8]}  ] $axis_subset_converter_1

  # Create instance: v_osd_1, and set properties
  set v_osd_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_osd:6.0 v_osd_1 ]
  set_property -dict [ list CONFIG.HAS_INTC_IF {false} CONFIG.NUMBER_OF_LAYERS {3} CONFIG.SCREEN_WIDTH {1920} CONFIG.M_AXIS_VIDEO_WIDTH {1920} CONFIG.M_AXIS_VIDEO_HEIGHT {1080} CONFIG.LAYER0_ENABLE {false} CONFIG.LAYER1_ENABLE {false} CONFIG.LAYER1_GLOBAL_ALPHA_VALUE {255}  ] $v_osd_1

  # Create instance: v_axi4s_vid_out_1, and set properties
  set v_axi4s_vid_out_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_axi4s_vid_out:3.0 v_axi4s_vid_out_1 ]
  set_property -dict [ list CONFIG.RAM_ADDR_BITS {11} CONFIG.VTG_MASTER_SLAVE {1}  ] $v_axi4s_vid_out_1

  # Create instance: v_rgb2ycrcb_1, and set properties
  set v_rgb2ycrcb_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_rgb2ycrcb:7.0 v_rgb2ycrcb_1 ]
  set_property -dict [ list CONFIG.HAS_AXI4_LITE {true} CONFIG.Standard_Sel {YUV} CONFIG.Input_Range {0_to_255_for_Computer_Graphics}  ] $v_rgb2ycrcb_1

  # Create instance: v_cresample_1, and set properties
  set v_cresample_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_cresample:4.0 v_cresample_1 ]
  set_property -dict [ list CONFIG.has_axi4_lite {true} CONFIG.s_axis_video_format {3} CONFIG.m_axis_video_format {2}  ] $v_cresample_1

  # Create instance: axi_vdma_2, and set properties
  set axi_vdma_2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vdma:6.0 axi_vdma_2 ]
  set_property -dict [ list CONFIG.c_s_axis_s2mm_tdata_width {32} CONFIG.c_num_fstores {1} CONFIG.c_mm2s_linebuffer_depth {4096} CONFIG.c_s2mm_linebuffer_depth {512} CONFIG.c_include_mm2s {1} CONFIG.c_mm2s_max_burst_length {16} CONFIG.c_include_s2mm {0} CONFIG.c_enable_debug_info_7 {1}  ] $axi_vdma_2

  # Create instance: v_tc_1, and set properties
  set v_tc_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:v_tc:6.0 v_tc_1 ]
  set_property -dict [ list CONFIG.VIDEO_MODE {1080p}  ] $v_tc_1

  # Create instance: vcc, and set properties
  set vcc [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.0 vcc ]

  # Create instance: axi_vdma_3, and set properties
  set axi_vdma_3 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vdma:6.0 axi_vdma_3 ]
  set_property -dict [ list CONFIG.c_m_axis_mm2s_tdata_width {16} CONFIG.c_s_axis_s2mm_tdata_width {32} CONFIG.c_num_fstores {1} CONFIG.c_mm2s_linebuffer_depth {4096} CONFIG.c_s2mm_linebuffer_depth {512} CONFIG.c_include_mm2s {1} CONFIG.c_mm2s_max_burst_length {16} CONFIG.c_include_s2mm {0} CONFIG.c_enable_debug_info_7 {1}  ] $axi_vdma_3

  # Create instance: zc702_hdmi_out_1, and set properties
  set zc702_hdmi_out_1 [ create_bd_cell -type ip -vlnv xilinx.com:user:zc702_hdmi_out:1.3 zc702_hdmi_out_1 ]

  # Create instance: gnd, and set properties
  set gnd [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconstant:1.0 gnd ]
  set_property -dict [ list CONFIG.CONST_VAL {0}  ] $gnd

  # Create interface connections
  connect_bd_intf_net -intf_net axi_vdma_2_m_axis_mm2s [get_bd_intf_pins axi_vdma_2/M_AXIS_MM2S] [get_bd_intf_pins axis_subset_converter_1/S_AXIS]
  connect_bd_intf_net -intf_net v_rgb2ycrcb_1_video_out [get_bd_intf_pins v_cresample_1/video_in] [get_bd_intf_pins v_rgb2ycrcb_1/video_out]
  connect_bd_intf_net -intf_net v_tc_1_vtiming_out [get_bd_intf_pins v_axi4s_vid_out_1/vtiming_in] [get_bd_intf_pins v_tc_1/vtiming_out]
  connect_bd_intf_net -intf_net axis_subset_converter_1_m_axis [get_bd_intf_pins axis_subset_converter_1/M_AXIS] [get_bd_intf_pins v_rgb2ycrcb_1/video_in]
  connect_bd_intf_net -intf_net v_cresample_1_video_out [get_bd_intf_pins v_cresample_1/video_out] [get_bd_intf_pins v_osd_1/video_s0_in]
  connect_bd_intf_net -intf_net v_osd_1_video_out [get_bd_intf_pins v_osd_1/video_out] [get_bd_intf_pins v_axi4s_vid_out_1/video_in]
  connect_bd_intf_net -intf_net axi_vdma_3_m_axis_mm2s [get_bd_intf_pins v_osd_1/video_s2_in] [get_bd_intf_pins axi_vdma_3/M_AXIS_MM2S]
  connect_bd_intf_net -intf_net s_axis_1 [get_bd_intf_pins S_AXIS] [get_bd_intf_pins v_osd_1/video_s1_in]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m05_axi [get_bd_intf_pins ctrl] [get_bd_intf_pins v_osd_1/ctrl]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m06_axi [get_bd_intf_pins ctrl1] [get_bd_intf_pins v_rgb2ycrcb_1/ctrl]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m07_axi [get_bd_intf_pins ctrl2] [get_bd_intf_pins v_cresample_1/ctrl]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m04_axi [get_bd_intf_pins S_AXI_LITE] [get_bd_intf_pins axi_vdma_2/S_AXI_LITE]
  connect_bd_intf_net -intf_net s02_axi_1 [get_bd_intf_pins M_AXI_MM2S] [get_bd_intf_pins axi_vdma_2/M_AXI_MM2S]
  connect_bd_intf_net -intf_net Conn1 [get_bd_intf_pins ctrl3] [get_bd_intf_pins v_tc_1/ctrl]
  connect_bd_intf_net -intf_net Conn2 [get_bd_intf_pins M_AXI_MM2S1] [get_bd_intf_pins axi_vdma_3/M_AXI_MM2S]
  connect_bd_intf_net -intf_net Conn3 [get_bd_intf_pins S_AXI_LITE1] [get_bd_intf_pins axi_vdma_3/S_AXI_LITE]

  # Create port connections
  connect_bd_net -net processing_system7_1_fclk_clk0 [get_bd_pins s_axi_lite_aclk] [get_bd_pins axi_vdma_2/s_axi_lite_aclk] [get_bd_pins v_rgb2ycrcb_1/s_axi_aclk] [get_bd_pins v_cresample_1/s_axi_aclk] [get_bd_pins v_osd_1/s_axi_aclk] [get_bd_pins axi_vdma_3/s_axi_lite_aclk] [get_bd_pins v_tc_1/s_axi_aclk]
  connect_bd_net -net hdmi_clk_1 [get_bd_pins vid_io_out_clk] [get_bd_pins v_axi4s_vid_out_1/vid_io_out_clk] [get_bd_pins v_tc_1/clk] [get_bd_pins zc702_hdmi_out_1/clk]
  connect_bd_net -net processing_system7_1_fclk_clk1 [get_bd_pins m_axi_mm2s_aclk] [get_bd_pins axi_vdma_2/m_axi_mm2s_aclk] [get_bd_pins axi_vdma_2/m_axis_mm2s_aclk] [get_bd_pins v_osd_1/aclk] [get_bd_pins v_rgb2ycrcb_1/aclk] [get_bd_pins v_cresample_1/aclk] [get_bd_pins v_axi4s_vid_out_1/aclk] [get_bd_pins axis_subset_converter_1/aclk] [get_bd_pins axi_vdma_3/m_axi_mm2s_aclk] [get_bd_pins axi_vdma_3/m_axis_mm2s_aclk]
  connect_bd_net -net axi_vdma_2_mm2s_introut [get_bd_pins mm2s_introut] [get_bd_pins axi_vdma_2/mm2s_introut]
  connect_bd_net -net v_osd_1_irq [get_bd_pins irq] [get_bd_pins v_osd_1/irq]
  connect_bd_net -net v_tc_1_irq [get_bd_pins irq1] [get_bd_pins v_tc_1/irq]
  connect_bd_net -net v_axi4s_vid_out_1_vtg_ce [get_bd_pins v_axi4s_vid_out_1/vtg_ce] [get_bd_pins v_tc_1/gen_clken]
  connect_bd_net -net xlconstant_1_const [get_bd_pins vcc/const] [get_bd_pins axis_subset_converter_1/aresetn]
  connect_bd_net -net axi_vdma_3_mm2s_introut [get_bd_pins mm2s_introut1] [get_bd_pins axi_vdma_3/mm2s_introut]
  connect_bd_net -net zc702_hdmi_out_1_io_hdmio_hsync [get_bd_pins vid_hsync] [get_bd_pins zc702_hdmi_out_1/io_hdmio_hsync]
  connect_bd_net -net zc702_hdmi_out_1_io_hdmio_de [get_bd_pins vid_active_video] [get_bd_pins zc702_hdmi_out_1/io_hdmio_de]
  connect_bd_net -net zc702_hdmi_out_1_io_hdmio_vsync [get_bd_pins vid_vsync] [get_bd_pins zc702_hdmi_out_1/io_hdmio_vsync]
  connect_bd_net -net zc702_hdmi_out_1_io_hdmio_video [get_bd_pins vid_data] [get_bd_pins zc702_hdmi_out_1/io_hdmio_video]
  connect_bd_net -net zc702_hdmi_out_1_io_hdmio_clk [get_bd_pins vid_clk] [get_bd_pins zc702_hdmi_out_1/io_hdmio_clk]
  connect_bd_net -net v_axi4s_vid_out_1_vid_hsync [get_bd_pins v_axi4s_vid_out_1/vid_hsync] [get_bd_pins zc702_hdmi_out_1/xsvi_hsync_i]
  connect_bd_net -net v_axi4s_vid_out_1_vid_vblank [get_bd_pins v_axi4s_vid_out_1/vid_vblank] [get_bd_pins zc702_hdmi_out_1/xsvi_vblank_i]
  connect_bd_net -net v_axi4s_vid_out_1_vid_active_video [get_bd_pins v_axi4s_vid_out_1/vid_active_video] [get_bd_pins zc702_hdmi_out_1/xsvi_active_video_i]
  connect_bd_net -net v_axi4s_vid_out_1_vid_vsync [get_bd_pins v_axi4s_vid_out_1/vid_vsync] [get_bd_pins zc702_hdmi_out_1/xsvi_vsync_i]
  connect_bd_net -net v_axi4s_vid_out_1_vid_hblank [get_bd_pins v_axi4s_vid_out_1/vid_hblank] [get_bd_pins zc702_hdmi_out_1/xsvi_hblank_i]
  connect_bd_net -net v_axi4s_vid_out_1_vid_data [get_bd_pins v_axi4s_vid_out_1/vid_data] [get_bd_pins zc702_hdmi_out_1/xsvi_video_data_i]
  connect_bd_net -net gnd_const [get_bd_pins gnd/const] [get_bd_pins zc702_hdmi_out_1/reset] [get_bd_pins zc702_hdmi_out_1/audio_spdif]
  
  # Restore current instance
  current_bd_instance $oldCurInst
}

# Hierarchical cell: video_processing
proc create_hier_cell_video_processing { parentCell nameHier } {

  if { $parentCell eq "" || $nameHier eq "" } {
     puts "ERROR: create_hier_cell_video_processing() - Empty argument(s)!"
     return
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj

  # Create cell and set as current instance
  set hier_obj [create_bd_cell -type hier $nameHier]
  current_bd_instance $hier_obj

  # Create interface pins
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S_AXI_CONTROL_BUS
  create_bd_intf_pin -mode Slave -vlnv xilinx.com:interface:aximm_rtl:1.0 S_AXI_LITE
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M_AXI_MM2S
  create_bd_intf_pin -mode Master -vlnv xilinx.com:interface:aximm_rtl:1.0 M_AXI_S2MM

  # Create pins
  create_bd_pin -dir I -type clk s_axi_lite_aclk
  create_bd_pin -dir O -type intr mm2s_introut
  create_bd_pin -dir I -type clk s_axis_s2mm_aclk
  create_bd_pin -dir O -type intr s2mm_introut
  create_bd_pin -dir O -type intr interrupt
  create_bd_pin -dir I -from 0 -to 0 aresetn

  # Create instance: axi_vdma_m2m, and set properties
  set axi_vdma_m2m [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vdma:6.0 axi_vdma_m2m ]
  set_property -dict [ list CONFIG.c_m_axis_mm2s_tdata_width {16} CONFIG.c_s_axis_s2mm_tdata_width {16} CONFIG.c_num_fstores {1} CONFIG.c_use_mm2s_fsync {0} CONFIG.c_mm2s_genlock_mode {3} CONFIG.c_s2mm_genlock_mode {2} CONFIG.c_mm2s_linebuffer_depth {4096} CONFIG.c_s2mm_linebuffer_depth {4096} CONFIG.c_include_mm2s {1} CONFIG.c_enable_debug_info_7 {1} CONFIG.c_enable_debug_info_15 {1}  ] $axi_vdma_m2m

  # Create instance: sobel_filter_1, and set properties
  set sobel_filter_1 [ create_bd_cell -type ip -vlnv xilinx.com:hls:sobel_filter:1.0 sobel_filter_1 ]

  # Create interface connections
  connect_bd_intf_net -intf_net sobel_filter_1_output_stream [get_bd_intf_pins axi_vdma_m2m/S_AXIS_S2MM] [get_bd_intf_pins sobel_filter_1/OUTPUT_STREAM]
  connect_bd_intf_net -intf_net axi_vdma_m2m_m_axis_mm2s [get_bd_intf_pins axi_vdma_m2m/M_AXIS_MM2S] [get_bd_intf_pins sobel_filter_1/INPUT_STREAM]
  connect_bd_intf_net -intf_net s_axi_control_bus_1 [get_bd_intf_pins S_AXI_CONTROL_BUS] [get_bd_intf_pins sobel_filter_1/S_AXI_CONTROL_BUS]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m02_axi [get_bd_intf_pins S_AXI_LITE] [get_bd_intf_pins axi_vdma_m2m/S_AXI_LITE]
  connect_bd_intf_net -intf_net axi_vdma_m2m_m_axi_mm2s [get_bd_intf_pins M_AXI_MM2S] [get_bd_intf_pins axi_vdma_m2m/M_AXI_MM2S]
  connect_bd_intf_net -intf_net axi_vdma_m2m_m_axi_s2mm [get_bd_intf_pins M_AXI_S2MM] [get_bd_intf_pins axi_vdma_m2m/M_AXI_S2MM]

  # Create port connections
  connect_bd_net -net processing_system7_1_fclk_clk0 [get_bd_pins s_axi_lite_aclk] [get_bd_pins axi_vdma_m2m/s_axi_lite_aclk]
  connect_bd_net -net axi_vdma_m2m_mm2s_introut [get_bd_pins mm2s_introut] [get_bd_pins axi_vdma_m2m/mm2s_introut]
  connect_bd_net -net processing_system7_1_fclk_clk1 [get_bd_pins s_axis_s2mm_aclk] [get_bd_pins axi_vdma_m2m/s_axis_s2mm_aclk] [get_bd_pins axi_vdma_m2m/m_axi_s2mm_aclk] [get_bd_pins axi_vdma_m2m/m_axis_mm2s_aclk] [get_bd_pins axi_vdma_m2m/m_axi_mm2s_aclk] [get_bd_pins sobel_filter_1/aclk]
  connect_bd_net -net axi_vdma_m2m_s2mm_introut [get_bd_pins s2mm_introut] [get_bd_pins axi_vdma_m2m/s2mm_introut]
  connect_bd_net -net sobel_filter_1_interrupt [get_bd_pins interrupt] [get_bd_pins sobel_filter_1/interrupt]
  connect_bd_net -net aresetn_1 [get_bd_pins aresetn] [get_bd_pins sobel_filter_1/aresetn]
  
  # Restore current instance
  current_bd_instance $oldCurInst
}


# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     puts "ERROR: Unable to find parent cell <$parentCell>!"
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     puts "ERROR: Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set DDR [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:ddrx_rtl:1.0 DDR ]
  set FIXED_IO [ create_bd_intf_port -mode Master -vlnv xilinx.com:display_processing_system7:fixedio_rtl:1.0 FIXED_IO ]
  set fmc_imageon_iic [ create_bd_intf_port -mode Master -vlnv xilinx.com:interface:iic_rtl:1.0 fmc_imageon_iic ]

  # Create ports
  set hdmio_hsync [ create_bd_port -dir O hdmio_hsync ]
  set hdmio_vsync [ create_bd_port -dir O hdmio_vsync ]
  set hdmio_de [ create_bd_port -dir O hdmio_de ]
  set hdmio_data [ create_bd_port -dir O -from 15 -to 0 hdmio_data ]
  set hdmio_int_b [ create_bd_port -dir I -type intr hdmio_int_b ]
  set_property -dict [ list CONFIG.SENSITIVITY {LEVEL_HIGH}  ] $hdmio_int_b
  set video_clk [ create_bd_port -dir I -type clk video_clk ]
  set_property -dict [ list CONFIG.FREQ_HZ {148500000} CONFIG.PHASE {0.000} CONFIG.CLK_DOMAIN {system_hdmi_clk}  ] $video_clk
  set hdmio_clk [ create_bd_port -dir O hdmio_clk ]
  set fmc_imageon_hdmii_data [ create_bd_port -dir I -from 15 -to 0 fmc_imageon_hdmii_data ]
  set fmc_imageon_hdmii_clk [ create_bd_port -dir I -type clk fmc_imageon_hdmii_clk ]
  set_property -dict [ list CONFIG.FREQ_HZ {148500000} CONFIG.PHASE {0.000} CONFIG.CLK_DOMAIN {system_top_fmc_imageon_hdmii_clk}  ] $fmc_imageon_hdmii_clk
  set fmc_imageon_iic_rst_b [ create_bd_port -dir O fmc_imageon_iic_rst_b ]

  # Create instance: processing_system7_1, and set properties
  set processing_system7_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.2 processing_system7_1 ]
  set_property -dict [ list CONFIG.PCW_FPGA0_PERIPHERAL_FREQMHZ {100} CONFIG.PCW_FPGA1_PERIPHERAL_FREQMHZ {50} CONFIG.PCW_USE_S_AXI_HP0 {1} CONFIG.PCW_USE_S_AXI_HP2 {1} CONFIG.PCW_USE_FABRIC_INTERRUPT {1} CONFIG.PCW_EN_CLK1_PORT {0} CONFIG.PCW_IRQ_F2P_INTR {1} CONFIG.PCW_I2C1_PERIPHERAL_ENABLE {1} CONFIG.PCW_GPIO_EMIO_GPIO_ENABLE {1} CONFIG.PCW_GPIO_EMIO_GPIO_IO {2}  ] $processing_system7_1

  # Create instance: axi_interconnect_hp0, and set properties
  set axi_interconnect_hp0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.0 axi_interconnect_hp0 ]
  set_property -dict [ list CONFIG.NUM_SI {3} CONFIG.NUM_MI {1}  ] $axi_interconnect_hp0

  # Create instance: axi_interconnect_hp2, and set properties
  set axi_interconnect_hp2 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.0 axi_interconnect_hp2 ]
  set_property -dict [ list CONFIG.NUM_SI {3} CONFIG.NUM_MI {1}  ] $axi_interconnect_hp2

  # Create instance: axi_vdma_1, and set properties
  set axi_vdma_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_vdma:6.0 axi_vdma_1 ]
  set_property -dict [ list CONFIG.c_m_axis_mm2s_tdata_width {16} CONFIG.c_s_axis_s2mm_tdata_width {16} CONFIG.c_include_s2mm_dre {0} CONFIG.c_num_fstores {1} CONFIG.c_use_s2mm_fsync {2} CONFIG.c_mm2s_genlock_mode {3} CONFIG.c_s2mm_genlock_mode {2} CONFIG.c_mm2s_linebuffer_depth {4096} CONFIG.c_s2mm_linebuffer_depth {4096} CONFIG.c_include_mm2s {1} CONFIG.c_mm2s_max_burst_length {16} CONFIG.c_s2mm_max_burst_length {16} CONFIG.c_enable_debug_info_7 {1} CONFIG.c_enable_debug_info_15 {1}  ] $axi_vdma_1

  # Create instance: pl_interrupts, and set properties
  set pl_interrupts [ create_bd_cell -type ip -vlnv xilinx.com:ip:xlconcat:1.0 pl_interrupts ]
  set_property -dict [ list CONFIG.NUM_PORTS {11}  ] $pl_interrupts

  # Create instance: video_processing
  create_hier_cell_video_processing [current_bd_instance .] video_processing

  # Create instance: video_display
  create_hier_cell_video_display [current_bd_instance .] video_display

  # Create instance: video_capture
  create_hier_cell_video_capture [current_bd_instance .] video_capture

  # Create instance: clk_wiz_1, and set properties
  set clk_wiz_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:clk_wiz:5.0 clk_wiz_1 ]
  set_property -dict [ list CONFIG.CLKOUT2_USED {true} CONFIG.CLKOUT1_REQUESTED_OUT_FREQ {75.000} CONFIG.CLKOUT2_REQUESTED_OUT_FREQ {150.000} CONFIG.PRIM_SOURCE {No_buffer} CONFIG.USE_RESET {false}  ] $clk_wiz_1

  # Create instance: proc_sys_reset_1, and set properties
  set proc_sys_reset_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:proc_sys_reset:5.0 proc_sys_reset_1 ]

  # Create instance: axi_interconnect_gp0, and set properties
  set axi_interconnect_gp0 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_interconnect:2.0 axi_interconnect_gp0 ]
  set_property -dict [ list CONFIG.NUM_MI {12}  ] $axi_interconnect_gp0

  # Create instance: axi_perf_mon_1, and set properties
  set axi_perf_mon_1 [ create_bd_cell -type ip -vlnv xilinx.com:ip:axi_perf_mon:4.0 axi_perf_mon_1 ]
  set_property -dict [ list CONFIG.C_SLOT_1_AXI_PROTOCOL {AXI3} CONFIG.C_SLOT_0_AXI_PROTOCOL {AXI3} CONFIG.C_NUM_OF_COUNTERS {4} CONFIG.C_NUM_MONITOR_SLOTS {2}  ] $axi_perf_mon_1

  # Create instance: EMIO_GPIO
  create_hier_cell_EMIO_GPIO [current_bd_instance .] EMIO_GPIO

  # Create interface connections
  connect_bd_intf_net -intf_net axi_interconnect_1_m00_axi [get_bd_intf_pins processing_system7_1/S_AXI_HP0] [get_bd_intf_pins axi_interconnect_hp0/M00_AXI]
connect_bd_intf_net -intf_net axi_interconnect_1_m00_axi [get_bd_intf_pins processing_system7_1/S_AXI_HP0] [get_bd_intf_pins axi_perf_mon_1/SLOT_0_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_hp1_m00_axi [get_bd_intf_pins axi_interconnect_hp2/M00_AXI] [get_bd_intf_pins processing_system7_1/S_AXI_HP2]
connect_bd_intf_net -intf_net axi_interconnect_hp1_m00_axi [get_bd_intf_pins axi_interconnect_hp2/M00_AXI] [get_bd_intf_pins axi_perf_mon_1/SLOT_1_AXI]
  connect_bd_intf_net -intf_net axi_vdma_1_m_axi_s2mm [get_bd_intf_pins axi_vdma_1/M_AXI_S2MM] [get_bd_intf_pins axi_interconnect_hp0/S00_AXI]
  connect_bd_intf_net -intf_net v_tpg_1_video_out [get_bd_intf_pins axi_vdma_1/S_AXIS_S2MM] [get_bd_intf_pins video_capture/video_out]
  connect_bd_intf_net -intf_net axi_vdma_m2m_m_axi_mm2s [get_bd_intf_pins video_processing/M_AXI_MM2S] [get_bd_intf_pins axi_interconnect_hp2/S00_AXI]
  connect_bd_intf_net -intf_net axi_vdma_m2m_m_axi_s2mm [get_bd_intf_pins video_processing/M_AXI_S2MM] [get_bd_intf_pins axi_interconnect_hp2/S01_AXI]
  connect_bd_intf_net -intf_net axi_vdma_1_m_axi_mm2s [get_bd_intf_pins axi_vdma_1/M_AXI_MM2S] [get_bd_intf_pins axi_interconnect_hp0/S01_AXI]
  connect_bd_intf_net -intf_net s02_axi_1 [get_bd_intf_pins axi_interconnect_hp0/S02_AXI] [get_bd_intf_pins video_display/M_AXI_MM2S]
  connect_bd_intf_net -intf_net axi_vdma_1_m_axis_mm2s [get_bd_intf_pins axi_vdma_1/M_AXIS_MM2S] [get_bd_intf_pins video_display/S_AXIS]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m08_axi [get_bd_intf_pins video_display/ctrl3] [get_bd_intf_pins axi_interconnect_gp0/M08_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m07_axi [get_bd_intf_pins video_display/ctrl2] [get_bd_intf_pins axi_interconnect_gp0/M07_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m06_axi [get_bd_intf_pins video_display/ctrl1] [get_bd_intf_pins axi_interconnect_gp0/M06_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m05_axi [get_bd_intf_pins video_display/ctrl] [get_bd_intf_pins axi_interconnect_gp0/M05_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m04_axi [get_bd_intf_pins video_display/S_AXI_LITE] [get_bd_intf_pins axi_interconnect_gp0/M04_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m03_axi [get_bd_intf_pins video_processing/S_AXI_CONTROL_BUS] [get_bd_intf_pins axi_interconnect_gp0/M03_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m02_axi [get_bd_intf_pins video_processing/S_AXI_LITE] [get_bd_intf_pins axi_interconnect_gp0/M02_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m01_axi [get_bd_intf_pins video_capture/ctrl] [get_bd_intf_pins axi_interconnect_gp0/M01_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m00_axi [get_bd_intf_pins axi_vdma_1/S_AXI_LITE] [get_bd_intf_pins axi_interconnect_gp0/M00_AXI]
  connect_bd_intf_net -intf_net processing_system7_1_m_axi_gp0 [get_bd_intf_pins processing_system7_1/M_AXI_GP0] [get_bd_intf_pins axi_interconnect_gp0/S00_AXI]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m09_axi [get_bd_intf_pins axi_interconnect_gp0/M09_AXI] [get_bd_intf_pins axi_perf_mon_1/s_axi]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m10_axi [get_bd_intf_pins axi_interconnect_gp0/M10_AXI] [get_bd_intf_pins video_display/S_AXI_LITE1]
  connect_bd_intf_net -intf_net s02_axi_2 [get_bd_intf_pins axi_interconnect_hp2/S02_AXI] [get_bd_intf_pins video_display/M_AXI_MM2S1]
  connect_bd_intf_net -intf_net axi_interconnect_gp0_m11_axi [get_bd_intf_pins axi_interconnect_gp0/M11_AXI] [get_bd_intf_pins video_capture/ctrl1]
  connect_bd_intf_net -intf_net processing_system7_1_ddr [get_bd_intf_ports DDR] [get_bd_intf_pins processing_system7_1/DDR]
  connect_bd_intf_net -intf_net processing_system7_1_fixed_io [get_bd_intf_ports FIXED_IO] [get_bd_intf_pins processing_system7_1/FIXED_IO]
  connect_bd_intf_net -intf_net processing_system7_1_iic_1 [get_bd_intf_ports fmc_imageon_iic] [get_bd_intf_pins processing_system7_1/IIC_1]

  # Create port connections
  connect_bd_net -net processing_system7_1_fclk_clk0 [get_bd_pins clk_wiz_1/clk_out1] [get_bd_pins processing_system7_1/M_AXI_GP0_ACLK] [get_bd_pins axi_vdma_1/s_axi_lite_aclk] [get_bd_pins video_processing/s_axi_lite_aclk] [get_bd_pins video_display/s_axi_lite_aclk] [get_bd_pins video_capture/s_axi_aclk] [get_bd_pins proc_sys_reset_1/slowest_sync_clk] [get_bd_pins axi_interconnect_gp0/ACLK] [get_bd_pins axi_interconnect_gp0/M08_ACLK] [get_bd_pins axi_interconnect_gp0/M07_ACLK] [get_bd_pins axi_interconnect_gp0/M06_ACLK] [get_bd_pins axi_interconnect_gp0/M05_ACLK] [get_bd_pins axi_interconnect_gp0/M04_ACLK] [get_bd_pins axi_interconnect_gp0/M02_ACLK] [get_bd_pins axi_interconnect_gp0/M01_ACLK] [get_bd_pins axi_interconnect_gp0/M00_ACLK] [get_bd_pins axi_interconnect_gp0/S00_ACLK] [get_bd_pins axi_perf_mon_1/s_axi_aclk] [get_bd_pins axi_interconnect_gp0/M09_ACLK] [get_bd_pins axi_interconnect_gp0/M10_ACLK] [get_bd_pins axi_interconnect_gp0/M11_ACLK]
  connect_bd_net -net processing_system7_1_fclk_clk1 [get_bd_pins clk_wiz_1/clk_out2] [get_bd_pins processing_system7_1/S_AXI_HP0_ACLK] [get_bd_pins processing_system7_1/S_AXI_HP2_ACLK] [get_bd_pins axi_interconnect_hp0/ACLK] [get_bd_pins axi_interconnect_hp0/S00_ACLK] [get_bd_pins axi_interconnect_hp0/M00_ACLK] [get_bd_pins axi_interconnect_hp0/S01_ACLK] [get_bd_pins axi_interconnect_hp0/S02_ACLK] [get_bd_pins axi_interconnect_hp2/ACLK] [get_bd_pins axi_interconnect_hp2/S00_ACLK] [get_bd_pins axi_interconnect_hp2/M00_ACLK] [get_bd_pins axi_interconnect_hp2/S01_ACLK] [get_bd_pins axi_vdma_1/m_axi_s2mm_aclk] [get_bd_pins axi_vdma_1/s_axis_s2mm_aclk] [get_bd_pins axi_vdma_1/m_axi_mm2s_aclk] [get_bd_pins axi_vdma_1/m_axis_mm2s_aclk] [get_bd_pins video_processing/s_axis_s2mm_aclk] [get_bd_pins video_display/m_axi_mm2s_aclk] [get_bd_pins video_capture/aclk] [get_bd_pins axi_interconnect_gp0/M03_ACLK] [get_bd_pins axi_perf_mon_1/slot_0_axi_aclk] [get_bd_pins axi_perf_mon_1/core_aclk] [get_bd_pins axi_perf_mon_1/slot_1_axi_aclk] [get_bd_pins axi_interconnect_hp2/S02_ACLK]
  connect_bd_net -net s00_aresetn_1 [get_bd_pins proc_sys_reset_1/interconnect_aresetn] [get_bd_pins axi_interconnect_hp0/S02_ARESETN] [get_bd_pins axi_interconnect_hp0/S01_ARESETN] [get_bd_pins axi_interconnect_hp0/M00_ARESETN] [get_bd_pins axi_interconnect_hp0/S00_ARESETN] [get_bd_pins axi_interconnect_hp0/ARESETN] [get_bd_pins axi_interconnect_hp2/ARESETN] [get_bd_pins axi_interconnect_hp2/S01_ARESETN] [get_bd_pins axi_interconnect_hp2/M00_ARESETN] [get_bd_pins axi_interconnect_hp2/S00_ARESETN] [get_bd_pins axi_interconnect_gp0/ARESETN] [get_bd_pins axi_interconnect_gp0/M08_ARESETN] [get_bd_pins axi_interconnect_gp0/M07_ARESETN] [get_bd_pins axi_interconnect_gp0/M06_ARESETN] [get_bd_pins axi_interconnect_gp0/M05_ARESETN] [get_bd_pins axi_interconnect_gp0/M04_ARESETN] [get_bd_pins axi_interconnect_gp0/M03_ARESETN] [get_bd_pins axi_interconnect_gp0/M02_ARESETN] [get_bd_pins axi_interconnect_gp0/M00_ARESETN] [get_bd_pins axi_interconnect_gp0/M01_ARESETN] [get_bd_pins axi_interconnect_gp0/S00_ARESETN] [get_bd_pins axi_interconnect_gp0/M09_ARESETN] [get_bd_pins axi_perf_mon_1/s_axi_aresetn] [get_bd_pins axi_perf_mon_1/slot_0_axi_aresetn] [get_bd_pins axi_perf_mon_1/core_aresetn] [get_bd_pins axi_perf_mon_1/slot_1_axi_aresetn] [get_bd_pins video_processing/aresetn] [get_bd_pins axi_interconnect_hp2/S02_ARESETN] [get_bd_pins axi_interconnect_gp0/M10_ARESETN] [get_bd_pins axi_interconnect_gp0/M11_ARESETN]
  connect_bd_net -net axi_vdma_m2m_mm2s_introut [get_bd_pins video_processing/mm2s_introut] [get_bd_pins pl_interrupts/In7]
  connect_bd_net -net axi_vdma_m2m_s2mm_introut [get_bd_pins video_processing/s2mm_introut] [get_bd_pins pl_interrupts/In8]
  connect_bd_net -net xlconcat_1_dout [get_bd_pins pl_interrupts/dout] [get_bd_pins processing_system7_1/IRQ_F2P]
  connect_bd_net -net axi_vdma_1_mm2s_introut [get_bd_pins axi_vdma_1/mm2s_introut] [get_bd_pins pl_interrupts/In2]
  connect_bd_net -net axi_vdma_1_s2mm_introut [get_bd_pins axi_vdma_1/s2mm_introut] [get_bd_pins pl_interrupts/In3]
  connect_bd_net -net sobel_filter_1_interrupt [get_bd_pins video_processing/interrupt] [get_bd_pins pl_interrupts/In6]
  connect_bd_net -net axi_vdma_2_mm2s_introut [get_bd_pins video_display/mm2s_introut] [get_bd_pins pl_interrupts/In1]
  connect_bd_net -net v_osd_1_irq [get_bd_pins video_display/irq] [get_bd_pins pl_interrupts/In4]
  connect_bd_net -net v_axi4s_vid_out_1_vid_hsync [get_bd_ports hdmio_hsync] [get_bd_pins video_display/vid_hsync]
  connect_bd_net -net v_axi4s_vid_out_1_vid_vsync [get_bd_ports hdmio_vsync] [get_bd_pins video_display/vid_vsync]
  connect_bd_net -net v_axi4s_vid_out_1_vid_active_video [get_bd_ports hdmio_de] [get_bd_pins video_display/vid_active_video]
  connect_bd_net -net v_axi4s_vid_out_1_vid_data [get_bd_ports hdmio_data] [get_bd_pins video_display/vid_data]
  connect_bd_net -net hdmi_int_1 [get_bd_ports hdmio_int_b] [get_bd_pins pl_interrupts/In0]
  connect_bd_net -net hdmi_clk_1 [get_bd_ports video_clk] [get_bd_pins video_display/vid_io_out_clk] [get_bd_pins video_capture/video_clk_2]
  connect_bd_net -net video_display_irq1 [get_bd_pins video_display/irq1] [get_bd_pins pl_interrupts/In5]
  connect_bd_net -net processing_system7_1_fclk_clk2 [get_bd_pins processing_system7_1/FCLK_CLK0] [get_bd_pins clk_wiz_1/clk_in1]
  connect_bd_net -net processing_system7_1_fclk_reset0_n [get_bd_pins processing_system7_1/FCLK_RESET0_N] [get_bd_pins proc_sys_reset_1/ext_reset_in]
  connect_bd_net -net clk_wiz_1_locked [get_bd_pins clk_wiz_1/locked] [get_bd_pins proc_sys_reset_1/dcm_locked]
  connect_bd_net -net video_display_mm2s_introut1 [get_bd_pins video_display/mm2s_introut1] [get_bd_pins pl_interrupts/In9]
  connect_bd_net -net io_hdmii_video_1 [get_bd_ports fmc_imageon_hdmii_data] [get_bd_pins video_capture/io_hdmii_video]
  connect_bd_net -net clk_1 [get_bd_ports fmc_imageon_hdmii_clk] [get_bd_pins video_capture/clk]
  connect_bd_net -net processing_system7_1_gpio_o [get_bd_pins processing_system7_1/GPIO_O] [get_bd_pins EMIO_GPIO/Din]
  connect_bd_net -net xlslice_2_dout [get_bd_pins EMIO_GPIO/Dout1] [get_bd_pins video_capture/video_sel]
  connect_bd_net -net video_capture_irq [get_bd_pins video_capture/irq] [get_bd_pins pl_interrupts/In10]
  connect_bd_net -net emio_gpio_dout [get_bd_ports fmc_imageon_iic_rst_b] [get_bd_pins EMIO_GPIO/Dout]
  connect_bd_net -net video_display_vid_clk [get_bd_ports hdmio_clk] [get_bd_pins video_display/vid_clk]

  # Create address segments
  create_bd_addr_seg -range 0x10000 -offset 0x40050000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_capture/v_tpg_1/ctrl/Reg] SEG2
  create_bd_addr_seg -range 0x10000 -offset 0x40010000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_display/v_tc_1/ctrl/Reg] SEG9
  create_bd_addr_seg -range 0x10000 -offset 0x40020000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_display/v_cresample_1/ctrl/Reg] SEG8
  create_bd_addr_seg -range 0x10000 -offset 0x40030000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_display/v_rgb2ycrcb_1/ctrl/Reg] SEG7
  create_bd_addr_seg -range 0x10000 -offset 0x40040000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_display/v_osd_1/ctrl/Reg] SEG6
  create_bd_addr_seg -range 0x10000 -offset 0x40060000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs axi_vdma_1/S_AXI_LITE/Reg] SEG1
  create_bd_addr_seg -range 0x10000 -offset 0x40000000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_display/axi_vdma_2/S_AXI_LITE/Reg] SEG5
  create_bd_addr_seg -range 0x10000 -offset 0x40070000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_processing/axi_vdma_m2m/S_AXI_LITE/Reg] SEG3
  create_bd_addr_seg -range 0x10000 -offset 0x40080000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_processing/sobel_filter_1/S_AXI_CONTROL_BUS/Reg] SEG4
  create_bd_addr_seg -range 0x10000 -offset 0x40090000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs axi_perf_mon_1/s_axi/Reg] SEG10
  create_bd_addr_seg -range 0x10000 -offset 0x400A0000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_display/axi_vdma_3/S_AXI_LITE/Reg] SEG11
  create_bd_addr_seg -range 0x10000 -offset 0x400B0000 [get_bd_addr_spaces processing_system7_1/Data] [get_bd_addr_segs video_capture/v_tc_1/ctrl/Reg] SEG12
  create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces axi_vdma_1/Data_MM2S] [get_bd_addr_segs processing_system7_1/S_AXI_HP0/HP0_DDR_LOWOCM] SEG1
  create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces axi_vdma_1/Data_S2MM] [get_bd_addr_segs processing_system7_1/S_AXI_HP0/HP0_DDR_LOWOCM] SEG2
  create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces video_processing/axi_vdma_m2m/Data_MM2S] [get_bd_addr_segs processing_system7_1/S_AXI_HP2/HP2_DDR_LOWOCM] SEG4
  create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces video_processing/axi_vdma_m2m/Data_S2MM] [get_bd_addr_segs processing_system7_1/S_AXI_HP2/HP2_DDR_LOWOCM] SEG5
  create_bd_addr_seg -range 0x40000000 -offset 0x0 [get_bd_addr_spaces video_display/axi_vdma_2/Data_MM2S] [get_bd_addr_segs processing_system7_1/S_AXI_HP0/HP0_DDR_LOWOCM] SEG3
  

  # Restore current instance
  current_bd_instance $oldCurInst
}


#####################################################
# Main Flow
#####################################################

create_root_design ""
