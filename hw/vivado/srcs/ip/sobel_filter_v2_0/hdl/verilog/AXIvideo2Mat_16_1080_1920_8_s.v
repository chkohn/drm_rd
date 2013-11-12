// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2013.2
// Copyright (C) 2013 Xilinx Inc. All rights reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module AXIvideo2Mat_16_1080_1920_8_s (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_continue,
        ap_idle,
        ap_ready,
        AXI_video_strm_V_data_V_dout,
        AXI_video_strm_V_data_V_empty_n,
        AXI_video_strm_V_data_V_read,
        AXI_video_strm_V_keep_V_dout,
        AXI_video_strm_V_keep_V_empty_n,
        AXI_video_strm_V_keep_V_read,
        AXI_video_strm_V_strb_V_dout,
        AXI_video_strm_V_strb_V_empty_n,
        AXI_video_strm_V_strb_V_read,
        AXI_video_strm_V_user_V_dout,
        AXI_video_strm_V_user_V_empty_n,
        AXI_video_strm_V_user_V_read,
        AXI_video_strm_V_last_V_dout,
        AXI_video_strm_V_last_V_empty_n,
        AXI_video_strm_V_last_V_read,
        AXI_video_strm_V_id_V_dout,
        AXI_video_strm_V_id_V_empty_n,
        AXI_video_strm_V_id_V_read,
        AXI_video_strm_V_dest_V_dout,
        AXI_video_strm_V_dest_V_empty_n,
        AXI_video_strm_V_dest_V_read,
        img_rows_V_read,
        img_cols_V_read,
        img_data_stream_0_V_din,
        img_data_stream_0_V_full_n,
        img_data_stream_0_V_write,
        img_data_stream_1_V_din,
        img_data_stream_1_V_full_n,
        img_data_stream_1_V_write
);

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
input   ap_continue;
output   ap_idle;
output   ap_ready;
input  [15:0] AXI_video_strm_V_data_V_dout;
input   AXI_video_strm_V_data_V_empty_n;
output   AXI_video_strm_V_data_V_read;
input  [1:0] AXI_video_strm_V_keep_V_dout;
input   AXI_video_strm_V_keep_V_empty_n;
output   AXI_video_strm_V_keep_V_read;
input  [1:0] AXI_video_strm_V_strb_V_dout;
input   AXI_video_strm_V_strb_V_empty_n;
output   AXI_video_strm_V_strb_V_read;
input  [0:0] AXI_video_strm_V_user_V_dout;
input   AXI_video_strm_V_user_V_empty_n;
output   AXI_video_strm_V_user_V_read;
input  [0:0] AXI_video_strm_V_last_V_dout;
input   AXI_video_strm_V_last_V_empty_n;
output   AXI_video_strm_V_last_V_read;
input  [0:0] AXI_video_strm_V_id_V_dout;
input   AXI_video_strm_V_id_V_empty_n;
output   AXI_video_strm_V_id_V_read;
input  [0:0] AXI_video_strm_V_dest_V_dout;
input   AXI_video_strm_V_dest_V_empty_n;
output   AXI_video_strm_V_dest_V_read;
input  [11:0] img_rows_V_read;
input  [11:0] img_cols_V_read;
output  [7:0] img_data_stream_0_V_din;
input   img_data_stream_0_V_full_n;
output   img_data_stream_0_V_write;
output  [7:0] img_data_stream_1_V_din;
input   img_data_stream_1_V_full_n;
output   img_data_stream_1_V_write;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg img_data_stream_0_V_write;
reg img_data_stream_1_V_write;
reg    ap_done_reg = 1'b0;
reg   [2:0] ap_CS_fsm = 3'b000;
reg   [11:0] t_V_1_reg_216;
reg   [15:0] axi_data_V_3_reg_227;
reg   [0:0] eol_6_reg_238;
reg   [0:0] eol_reg_249;
wire    AXI_video_strm_V_0_status;
reg    ap_sig_bdd_87;
reg    ap_sig_bdd_95;
reg    ap_sig_bdd_105;
wire   [11:0] i_V_fu_372_p2;
reg   [11:0] i_V_reg_443;
wire   [0:0] exitcond3_fu_378_p2;
reg   [0:0] exitcond3_reg_448;
reg    ap_reg_ppiten_pp1_it0 = 1'b0;
reg   [0:0] sof_load_reg_457;
reg    ap_sig_bdd_137;
reg    ap_reg_ppiten_pp1_it1 = 1'b0;
wire   [11:0] j_V_fu_383_p2;
wire   [0:0] sof_load_load_fu_389_p1;
wire   [0:0] exitcond_fu_367_p2;
reg   [15:0] axi_data_V_reg_148;
reg   [0:0] axi_last_V_reg_160;
reg   [0:0] axi_user_V_reg_172;
reg   [15:0] axi_data_V_4_reg_306;
reg   [15:0] axi_data_V_2_reg_183;
reg   [0:0] axi_last_V_4_reg_318;
reg   [0:0] axi_last_V_2_reg_194;
reg   [11:0] t_V_reg_205;
reg   [15:0] axi_data_V_8_phi_fu_265_p6;
reg   [0:0] axi_last_V_7_phi_fu_280_p6;
reg   [0:0] eol_5_phi_fu_295_p6;
reg   [0:0] eol_1_reg_330;
reg    AXI_video_strm_V_0_update;
reg   [0:0] sof_fu_100;
reg   [2:0] ap_NS_fsm;
reg    ap_sig_bdd_308;
reg    ap_sig_bdd_310;
reg    ap_sig_bdd_265;
parameter    ap_const_logic_1 = 1'b1;
parameter    ap_const_logic_0 = 1'b0;
parameter    ap_ST_st1_fsm_0 = 3'b000;
parameter    ap_ST_st2_fsm_1 = 3'b1;
parameter    ap_ST_st3_fsm_2 = 3'b10;
parameter    ap_ST_st4_fsm_3 = 3'b11;
parameter    ap_ST_pp1_stg0_fsm_4 = 3'b100;
parameter    ap_ST_st7_fsm_5 = 3'b101;
parameter    ap_ST_st8_fsm_6 = 3'b110;
parameter    ap_const_lv1_0 = 1'b0;
parameter    ap_const_lv12_0 = 12'b000000000000;
parameter    ap_const_lv16_0 = 16'b0000000000000000;
parameter    ap_const_lv1_1 = 1'b1;
parameter    ap_const_lv12_1 = 12'b1;
parameter    ap_const_lv32_8 = 32'b1000;
parameter    ap_const_lv32_F = 32'b1111;
parameter    ap_const_lv16_1 = 16'b1;
parameter    ap_true = 1'b1;




/// the current state (ap_CS_fsm) of the state machine. ///
always @ (posedge ap_clk)
begin : ap_ret_ap_CS_fsm
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_st1_fsm_0;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

/// ap_done_reg assign process. ///
always @ (posedge ap_clk)
begin : ap_ret_ap_done_reg
    if (ap_rst == 1'b1) begin
        ap_done_reg <= ap_const_logic_0;
    end else begin
        if ((ap_const_logic_1 == ap_continue)) begin
            ap_done_reg <= ap_const_logic_0;
        end else if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & ~(ap_const_lv1_0 == exitcond_fu_367_p2))) begin
            ap_done_reg <= ap_const_logic_1;
        end
    end
end

/// ap_reg_ppiten_pp1_it0 assign process. ///
always @ (posedge ap_clk)
begin : ap_ret_ap_reg_ppiten_pp1_it0
    if (ap_rst == 1'b1) begin
        ap_reg_ppiten_pp1_it0 <= ap_const_logic_0;
    end else begin
        if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & ~(ap_const_lv1_0 == exitcond3_fu_378_p2))) begin
            ap_reg_ppiten_pp1_it0 <= ap_const_logic_0;
        end else if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond_fu_367_p2))) begin
            ap_reg_ppiten_pp1_it0 <= ap_const_logic_1;
        end
    end
end

/// ap_reg_ppiten_pp1_it1 assign process. ///
always @ (posedge ap_clk)
begin : ap_ret_ap_reg_ppiten_pp1_it1
    if (ap_rst == 1'b1) begin
        ap_reg_ppiten_pp1_it1 <= ap_const_logic_0;
    end else begin
        if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)))) begin
            ap_reg_ppiten_pp1_it1 <= ap_reg_ppiten_pp1_it0;
        end else if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond_fu_367_p2))) begin
            ap_reg_ppiten_pp1_it1 <= ap_const_logic_0;
        end
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if ((ap_ST_st3_fsm_2 == ap_CS_fsm)) begin
        axi_data_V_2_reg_183 <= axi_data_V_reg_148;
    end else if ((ap_ST_st8_fsm_6 == ap_CS_fsm)) begin
        axi_data_V_2_reg_183 <= axi_data_V_4_reg_306;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)))) begin
        axi_data_V_3_reg_227 <= axi_data_V_8_phi_fu_265_p6;
    end else if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond_fu_367_p2))) begin
        axi_data_V_3_reg_227 <= axi_data_V_2_reg_183;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & ~(ap_const_lv1_0 == exitcond3_reg_448))) begin
        axi_data_V_4_reg_306 <= axi_data_V_3_reg_227;
    end else if (((ap_ST_st7_fsm_5 == ap_CS_fsm) & (ap_const_lv1_0 == eol_1_reg_330) & ~ap_sig_bdd_95)) begin
        axi_data_V_4_reg_306 <= AXI_video_strm_V_data_V_dout;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if ((ap_ST_st3_fsm_2 == ap_CS_fsm)) begin
        axi_last_V_2_reg_194 <= axi_last_V_reg_160;
    end else if ((ap_ST_st8_fsm_6 == ap_CS_fsm)) begin
        axi_last_V_2_reg_194 <= axi_last_V_4_reg_318;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & ~(ap_const_lv1_0 == exitcond3_reg_448))) begin
        axi_last_V_4_reg_318 <= eol_6_reg_238;
    end else if (((ap_ST_st7_fsm_5 == ap_CS_fsm) & (ap_const_lv1_0 == eol_1_reg_330) & ~ap_sig_bdd_95)) begin
        axi_last_V_4_reg_318 <= AXI_video_strm_V_last_V_dout;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_st2_fsm_1 == ap_CS_fsm) & (axi_user_V_reg_172 == ap_const_lv1_0) & ~ap_sig_bdd_87)) begin
        axi_user_V_reg_172 <= AXI_video_strm_V_user_V_dout;
    end else if (((ap_ST_st1_fsm_0 == ap_CS_fsm) & ~ap_sig_bdd_105)) begin
        axi_user_V_reg_172 <= ap_const_lv1_0;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & ~(ap_const_lv1_0 == exitcond3_reg_448))) begin
        eol_1_reg_330 <= eol_reg_249;
    end else if (((ap_ST_st7_fsm_5 == ap_CS_fsm) & (ap_const_lv1_0 == eol_1_reg_330) & ~ap_sig_bdd_95)) begin
        eol_1_reg_330 <= AXI_video_strm_V_last_V_dout;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)))) begin
        eol_6_reg_238 <= axi_last_V_7_phi_fu_280_p6;
    end else if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond_fu_367_p2))) begin
        eol_6_reg_238 <= axi_last_V_2_reg_194;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)))) begin
        eol_reg_249 <= eol_5_phi_fu_295_p6;
    end else if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond_fu_367_p2))) begin
        eol_reg_249 <= ap_const_lv1_0;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it0) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & (ap_const_lv1_0 == exitcond3_fu_378_p2) & ~(ap_const_lv1_0 == sof_load_load_fu_389_p1))) begin
        sof_fu_100 <= ap_const_lv1_0;
    end else if ((ap_ST_st3_fsm_2 == ap_CS_fsm)) begin
        sof_fu_100 <= ap_const_lv1_1;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it0) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & (ap_const_lv1_0 == exitcond3_fu_378_p2))) begin
        t_V_1_reg_216 <= j_V_fu_383_p2;
    end else if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond_fu_367_p2))) begin
        t_V_1_reg_216 <= ap_const_lv12_0;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if ((ap_ST_st3_fsm_2 == ap_CS_fsm)) begin
        t_V_reg_205 <= ap_const_lv12_0;
    end else if ((ap_ST_st8_fsm_6 == ap_CS_fsm)) begin
        t_V_reg_205 <= i_V_reg_443;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_st2_fsm_1 == ap_CS_fsm) & (axi_user_V_reg_172 == ap_const_lv1_0) & ~ap_sig_bdd_87)) begin
        axi_data_V_reg_148 <= AXI_video_strm_V_data_V_dout;
        axi_last_V_reg_160 <= AXI_video_strm_V_last_V_dout;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it0) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)))) begin
        exitcond3_reg_448 <= exitcond3_fu_378_p2;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if ((ap_ST_st4_fsm_3 == ap_CS_fsm)) begin
        i_V_reg_443 <= i_V_fu_372_p2;
    end
end

/// assign process. ///
always @(posedge ap_clk)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it0) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & (ap_const_lv1_0 == exitcond3_fu_378_p2))) begin
        sof_load_reg_457 <= sof_fu_100;
    end
end

/// AXI_video_strm_V_0_update assign process. ///
always @ (ap_CS_fsm or eol_reg_249 or ap_sig_bdd_87 or ap_sig_bdd_95 or exitcond3_reg_448 or sof_load_reg_457 or ap_sig_bdd_137 or ap_reg_ppiten_pp1_it1 or axi_user_V_reg_172 or eol_1_reg_330)
begin
    if ((((ap_ST_st2_fsm_1 == ap_CS_fsm) & (axi_user_V_reg_172 == ap_const_lv1_0) & ~ap_sig_bdd_87) | ((ap_ST_st7_fsm_5 == ap_CS_fsm) & (ap_const_lv1_0 == eol_1_reg_330) & ~ap_sig_bdd_95) | ((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_lv1_0 == sof_load_reg_457) & (ap_const_lv1_0 == eol_reg_249) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1))))) begin
        AXI_video_strm_V_0_update = ap_const_logic_1;
    end else begin
        AXI_video_strm_V_0_update = ap_const_logic_0;
    end
end

/// ap_done assign process. ///
always @ (ap_done_reg or ap_CS_fsm or exitcond_fu_367_p2)
begin
    if (((ap_const_logic_1 == ap_done_reg) | ((ap_ST_st4_fsm_3 == ap_CS_fsm) & ~(ap_const_lv1_0 == exitcond_fu_367_p2)))) begin
        ap_done = ap_const_logic_1;
    end else begin
        ap_done = ap_const_logic_0;
    end
end

/// ap_idle assign process. ///
always @ (ap_start or ap_CS_fsm)
begin
    if ((~(ap_const_logic_1 == ap_start) & (ap_ST_st1_fsm_0 == ap_CS_fsm))) begin
        ap_idle = ap_const_logic_1;
    end else begin
        ap_idle = ap_const_logic_0;
    end
end

/// ap_ready assign process. ///
always @ (ap_CS_fsm or exitcond_fu_367_p2)
begin
    if (((ap_ST_st4_fsm_3 == ap_CS_fsm) & ~(ap_const_lv1_0 == exitcond_fu_367_p2))) begin
        ap_ready = ap_const_logic_1;
    end else begin
        ap_ready = ap_const_logic_0;
    end
end

/// axi_data_V_8_phi_fu_265_p6 assign process. ///
always @ (AXI_video_strm_V_data_V_dout or axi_data_V_3_reg_227 or sof_load_reg_457 or ap_sig_bdd_308 or ap_sig_bdd_310 or ap_sig_bdd_265)
begin
    if (ap_sig_bdd_265) begin
        if (ap_sig_bdd_310) begin
            axi_data_V_8_phi_fu_265_p6 = ap_const_lv16_0;
        end else if (~(ap_const_lv1_0 == sof_load_reg_457)) begin
            axi_data_V_8_phi_fu_265_p6 = axi_data_V_3_reg_227;
        end else if (ap_sig_bdd_308) begin
            axi_data_V_8_phi_fu_265_p6 = AXI_video_strm_V_data_V_dout;
        end else begin
            axi_data_V_8_phi_fu_265_p6 = ap_const_lv16_1;
        end
    end else begin
        axi_data_V_8_phi_fu_265_p6 = ap_const_lv16_1;
    end
end

/// axi_last_V_7_phi_fu_280_p6 assign process. ///
always @ (AXI_video_strm_V_last_V_dout or eol_6_reg_238 or sof_load_reg_457 or ap_sig_bdd_308 or ap_sig_bdd_310 or ap_sig_bdd_265)
begin
    if (ap_sig_bdd_265) begin
        if (ap_sig_bdd_310) begin
            axi_last_V_7_phi_fu_280_p6 = ap_const_lv1_0;
        end else if (~(ap_const_lv1_0 == sof_load_reg_457)) begin
            axi_last_V_7_phi_fu_280_p6 = eol_6_reg_238;
        end else if (ap_sig_bdd_308) begin
            axi_last_V_7_phi_fu_280_p6 = AXI_video_strm_V_last_V_dout;
        end else begin
            axi_last_V_7_phi_fu_280_p6 = ap_const_lv1_1;
        end
    end else begin
        axi_last_V_7_phi_fu_280_p6 = ap_const_lv1_1;
    end
end

/// eol_5_phi_fu_295_p6 assign process. ///
always @ (AXI_video_strm_V_last_V_dout or eol_6_reg_238 or eol_reg_249 or sof_load_reg_457 or ap_sig_bdd_308 or ap_sig_bdd_310 or ap_sig_bdd_265)
begin
    if (ap_sig_bdd_265) begin
        if (ap_sig_bdd_310) begin
            eol_5_phi_fu_295_p6 = eol_reg_249;
        end else if (~(ap_const_lv1_0 == sof_load_reg_457)) begin
            eol_5_phi_fu_295_p6 = eol_6_reg_238;
        end else if (ap_sig_bdd_308) begin
            eol_5_phi_fu_295_p6 = AXI_video_strm_V_last_V_dout;
        end else begin
            eol_5_phi_fu_295_p6 = ap_const_lv1_1;
        end
    end else begin
        eol_5_phi_fu_295_p6 = ap_const_lv1_1;
    end
end

/// img_data_stream_0_V_write assign process. ///
always @ (ap_CS_fsm or exitcond3_reg_448 or ap_sig_bdd_137 or ap_reg_ppiten_pp1_it1)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)))) begin
        img_data_stream_0_V_write = ap_const_logic_1;
    end else begin
        img_data_stream_0_V_write = ap_const_logic_0;
    end
end

/// img_data_stream_1_V_write assign process. ///
always @ (ap_CS_fsm or exitcond3_reg_448 or ap_sig_bdd_137 or ap_reg_ppiten_pp1_it1)
begin
    if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)))) begin
        img_data_stream_1_V_write = ap_const_logic_1;
    end else begin
        img_data_stream_1_V_write = ap_const_logic_0;
    end
end
always @ (ap_CS_fsm or ap_sig_bdd_87 or ap_sig_bdd_95 or ap_sig_bdd_105 or ap_reg_ppiten_pp1_it0 or ap_sig_bdd_137 or ap_reg_ppiten_pp1_it1 or exitcond_fu_367_p2 or axi_user_V_reg_172 or eol_1_reg_330)
begin
    case (ap_CS_fsm)
        ap_ST_st1_fsm_0 : 
            if (~ap_sig_bdd_105) begin
                ap_NS_fsm = ap_ST_st2_fsm_1;
            end else begin
                ap_NS_fsm = ap_ST_st1_fsm_0;
            end
        ap_ST_st2_fsm_1 : 
            if (((axi_user_V_reg_172 == ap_const_lv1_0) & ~ap_sig_bdd_87)) begin
                ap_NS_fsm = ap_ST_st2_fsm_1;
            end else if ((~ap_sig_bdd_87 & ~(axi_user_V_reg_172 == ap_const_lv1_0))) begin
                ap_NS_fsm = ap_ST_st3_fsm_2;
            end else begin
                ap_NS_fsm = ap_ST_st2_fsm_1;
            end
        ap_ST_st3_fsm_2 : 
            ap_NS_fsm = ap_ST_st4_fsm_3;
        ap_ST_st4_fsm_3 : 
            if (~(ap_const_lv1_0 == exitcond_fu_367_p2)) begin
                ap_NS_fsm = ap_ST_st1_fsm_0;
            end else begin
                ap_NS_fsm = ap_ST_pp1_stg0_fsm_4;
            end
        ap_ST_pp1_stg0_fsm_4 : 
            if (~((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & ~(ap_const_logic_1 == ap_reg_ppiten_pp1_it0))) begin
                ap_NS_fsm = ap_ST_pp1_stg0_fsm_4;
            end else if (((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1) & ~(ap_sig_bdd_137 & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1)) & ~(ap_const_logic_1 == ap_reg_ppiten_pp1_it0))) begin
                ap_NS_fsm = ap_ST_st7_fsm_5;
            end else begin
                ap_NS_fsm = ap_ST_pp1_stg0_fsm_4;
            end
        ap_ST_st7_fsm_5 : 
            if (((ap_const_lv1_0 == eol_1_reg_330) & ~ap_sig_bdd_95)) begin
                ap_NS_fsm = ap_ST_st7_fsm_5;
            end else if ((~ap_sig_bdd_95 & ~(ap_const_lv1_0 == eol_1_reg_330))) begin
                ap_NS_fsm = ap_ST_st8_fsm_6;
            end else begin
                ap_NS_fsm = ap_ST_st7_fsm_5;
            end
        ap_ST_st8_fsm_6 : 
            ap_NS_fsm = ap_ST_st4_fsm_3;
        default : 
            ap_NS_fsm = 'bx;
    endcase
end
assign AXI_video_strm_V_0_status = (AXI_video_strm_V_data_V_empty_n & AXI_video_strm_V_keep_V_empty_n & AXI_video_strm_V_strb_V_empty_n & AXI_video_strm_V_user_V_empty_n & AXI_video_strm_V_last_V_empty_n & AXI_video_strm_V_id_V_empty_n & AXI_video_strm_V_dest_V_empty_n);
assign AXI_video_strm_V_data_V_read = AXI_video_strm_V_0_update;
assign AXI_video_strm_V_dest_V_read = AXI_video_strm_V_0_update;
assign AXI_video_strm_V_id_V_read = AXI_video_strm_V_0_update;
assign AXI_video_strm_V_keep_V_read = AXI_video_strm_V_0_update;
assign AXI_video_strm_V_last_V_read = AXI_video_strm_V_0_update;
assign AXI_video_strm_V_strb_V_read = AXI_video_strm_V_0_update;
assign AXI_video_strm_V_user_V_read = AXI_video_strm_V_0_update;

/// ap_sig_bdd_105 assign process. ///
always @ (ap_start or ap_done_reg)
begin
    ap_sig_bdd_105 = ((ap_start == ap_const_logic_0) | (ap_done_reg == ap_const_logic_1));
end

/// ap_sig_bdd_137 assign process. ///
always @ (img_data_stream_0_V_full_n or img_data_stream_1_V_full_n or eol_reg_249 or AXI_video_strm_V_0_status or exitcond3_reg_448 or sof_load_reg_457)
begin
    ap_sig_bdd_137 = (((AXI_video_strm_V_0_status == ap_const_logic_0) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_lv1_0 == sof_load_reg_457) & (ap_const_lv1_0 == eol_reg_249)) | ((ap_const_lv1_0 == exitcond3_reg_448) & (img_data_stream_0_V_full_n == ap_const_logic_0)) | ((ap_const_lv1_0 == exitcond3_reg_448) & (img_data_stream_1_V_full_n == ap_const_logic_0)));
end

/// ap_sig_bdd_265 assign process. ///
always @ (ap_CS_fsm or exitcond3_reg_448 or ap_reg_ppiten_pp1_it1)
begin
    ap_sig_bdd_265 = ((ap_ST_pp1_stg0_fsm_4 == ap_CS_fsm) & (ap_const_lv1_0 == exitcond3_reg_448) & (ap_const_logic_1 == ap_reg_ppiten_pp1_it1));
end

/// ap_sig_bdd_308 assign process. ///
always @ (eol_reg_249 or sof_load_reg_457)
begin
    ap_sig_bdd_308 = ((ap_const_lv1_0 == sof_load_reg_457) & (ap_const_lv1_0 == eol_reg_249));
end

/// ap_sig_bdd_310 assign process. ///
always @ (eol_reg_249 or sof_load_reg_457)
begin
    ap_sig_bdd_310 = ((ap_const_lv1_0 == sof_load_reg_457) & ~(ap_const_lv1_0 == eol_reg_249));
end

/// ap_sig_bdd_87 assign process. ///
always @ (AXI_video_strm_V_0_status or axi_user_V_reg_172)
begin
    ap_sig_bdd_87 = ((AXI_video_strm_V_0_status == ap_const_logic_0) & (axi_user_V_reg_172 == ap_const_lv1_0));
end

/// ap_sig_bdd_95 assign process. ///
always @ (AXI_video_strm_V_0_status or eol_1_reg_330)
begin
    ap_sig_bdd_95 = ((AXI_video_strm_V_0_status == ap_const_logic_0) & (ap_const_lv1_0 == eol_1_reg_330));
end
assign exitcond3_fu_378_p2 = (t_V_1_reg_216 == img_cols_V_read? 1'b1: 1'b0);
assign exitcond_fu_367_p2 = (t_V_reg_205 == img_rows_V_read? 1'b1: 1'b0);
assign i_V_fu_372_p2 = (t_V_reg_205 + ap_const_lv12_1);
assign img_data_stream_0_V_din = axi_data_V_8_phi_fu_265_p6[7:0];
assign img_data_stream_1_V_din = {{axi_data_V_8_phi_fu_265_p6[ap_const_lv32_F : ap_const_lv32_8]}};
assign j_V_fu_383_p2 = (t_V_1_reg_216 + ap_const_lv12_1);
assign sof_load_load_fu_389_p1 = sof_fu_100;


endmodule //AXIvideo2Mat_16_1080_1920_8_s
