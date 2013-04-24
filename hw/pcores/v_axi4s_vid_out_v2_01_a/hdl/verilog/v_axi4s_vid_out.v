// $Revision: $ $Date:  $
//-----------------------------------------------------------------------------
//  (c) Copyright 2011 Xilinx, Inc. All rights reserved.
//
//  This file contains confidential and proprietary information
//  of Xilinx, Inc. and is protected under U.S. and
//  international copyright and other intellectual property
//  laws.
//
//  DISCLAIMER
//  This disclaimer is not a license and does not grant any
//  rights to the materials distributed herewith. Except as
//  otherwise provided in a valid license issued to you by
//  Xilinx, and to the maximum extent permitted by applicable
//  law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
//  WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
//  AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
//  BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
//  INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
//  (2) Xilinx shall not be liable (whether in contract or tort,
//  including negligence, or under any other theory of
//  liability) for any loss or damage of any kind or nature
//  related to, arising under or in connection with these
//  materials, including for any direct, or any indirect,
//  special, incidental, or consequential loss or damage
//  (including loss of data, profits, goodwill, or any type of
//  loss or damage suffered as a result of any action brought
//  by a third party) even if such damage or loss was
//  reasonably foreseeable or Xilinx had been advised of the
//  possibility of the same.
//
//  CRITICAL APPLICATIONS
//  Xilinx products are not designed or intended to be fail-
//  safe, or for use in any application requiring fail-safe
//  performance, such as life-support or safety devices or
//  systems, Class III medical devices, nuclear facilities,
//  applications related to the deployment of airbags, or any
//  other applications that could lead to death, personal
//  injury, or severe property or environmental damage
//  (individually and collectively, "Critical
//  Applications"). Customer assumes the sole risk and
//  liability of any use of Xilinx products in Critical
//  Applications, subject only to applicable laws and
//  regulations governing limitations on product liability.
//
//  THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
//  PART OF THIS FILE AT ALL TIMES. 
//
//----------------------------------------------------------
/*
Module Description:

This is the top level of a bridge from AXI4-Streaming to Video Out
(Data, Hsync, Vsync, Data Enable)
------------------------------------------------------------------------------
*/
module v_axi4s_vid_out
#( 
  parameter  C_S_AXIS_VIDEO_DATA_WIDTH = 8,
  parameter  C_S_AXIS_VIDEO_FORMAT = 2,
  parameter  VID_OUT_DATA_WIDTH = 24, 
                                      
  parameter  C_S_AXIS_VIDEO_TDATA_WIDTH = 24, 
  parameter  RAM_ADDR_BITS = 10,    // default depth = 1024(10) min = 32 (5)
  parameter  HYSTERESIS_LEVEL = 12,    // min 12
  parameter  FILL_GUARDBAND = 2,
  parameter  VTG_MASTER_SLAVE = 0 //timing mode, 1= VTG master,0 = VTG is slave
 )
( 
// AXI4-streaming interface
  input   wire                  aclk,                // axi-4 S clock
  input   wire                  rst,                 // general reset
  input   wire                  aclken,              // axi-4 clock enable
  input   wire                  aresetn,             // axi-4 reset active low
  input   wire [C_S_AXIS_VIDEO_TDATA_WIDTH-1:0] s_axis_video_tdata , // axi-4 S data
  input   wire                  s_axis_video_tvalid, // axi-4 S valid 
  output  wire                  s_axis_video_tready, // axi-4 S ready 
  input   wire                  s_axis_video_tuser , // axi-4 S start of field
  input   wire                  s_axis_video_tlast , // axi-4 S end of line
  
// video output interface
  input   wire                  video_out_clk ,    // video clock output
  output  wire                  video_clk ,        // video clock
  output  wire                  video_de         , // video data enable
  output  wire                  video_vsync      , // video vertical sync
  output  wire                  video_hsync      , // video horizontal sync
  output  wire                  video_vblank      , // video vertical blank
  output  wire                  video_hblank      , // video horizontal blank
  output  wire [VID_OUT_DATA_WIDTH-1:0] video_data   ,     // video data at DDR rate
  
// Register/VTG Interface
  input   wire                  vtg_vsync,       // vsync from the video timing generator
  input   wire                  vtg_hsync,
  input   wire                  vtg_vblank,
  input   wire                  vtg_hblank,
  input   wire                  vtg_act_vid,
  output  wire                  vtg_ce,
  output  wire                  vtg_fsync,
  // output status bits
  output  wire                  locked,
  output  wire                  wr_error,
  output  wire                  empty  
);
  v_axi4s_vid_out_v2_01_a_axi4s_vid_out_top
    #(
      .C_S_AXIS_VIDEO_DATA_WIDTH  (C_S_AXIS_VIDEO_DATA_WIDTH   ),
      .C_S_AXIS_VIDEO_FORMAT      (C_S_AXIS_VIDEO_FORMAT       ),
      .VID_OUT_DATA_WIDTH         (VID_OUT_DATA_WIDTH          ),
      .C_S_AXIS_VIDEO_TDATA_WIDTH (C_S_AXIS_VIDEO_TDATA_WIDTH  ),
      .RAM_ADDR_BITS              (RAM_ADDR_BITS               ),
      .HYSTERESIS_LEVEL           (HYSTERESIS_LEVEL            ),
      .FILL_GUARDBAND             (FILL_GUARDBAND              ),
      .VTG_MASTER_SLAVE           (VTG_MASTER_SLAVE            )
    )
    axi4s_vid_out_top_i (
      .aclk ( aclk ),
      .rst ( rst ),
      .aclken ( aclken ),
      .aresetn ( aresetn ),
      .s_axis_video_tdata ( s_axis_video_tdata ),
      .s_axis_video_tvalid ( s_axis_video_tvalid ),
      .s_axis_video_tready ( s_axis_video_tready ),
      .s_axis_video_tuser ( s_axis_video_tuser ),
      .s_axis_video_tlast ( s_axis_video_tlast ),
      .video_out_clk ( video_out_clk ),
      .video_clk ( video_clk ),
      .video_de ( video_de ),
      .video_vsync ( video_vsync ),
      .video_hsync ( video_hsync ),
      .video_vblank ( video_vblank ),
      .video_hblank ( video_hblank ),
      .video_data ( video_data ),
      .vtg_vsync ( vtg_vsync ),
      .vtg_hsync ( vtg_hsync ),
      .vtg_vblank ( vtg_vblank ),
      .vtg_hblank ( vtg_hblank ),
      .vtg_act_vid ( vtg_act_vid ),
      .vtg_ce ( vtg_ce ),
      .vtg_fsync ( vtg_fsync ),
      .locked ( locked ),
      .wr_error ( wr_error ),
      .empty ( empty )
    );


endmodule
