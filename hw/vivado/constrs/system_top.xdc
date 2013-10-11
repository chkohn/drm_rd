##################
# Primary Clocks #
##################

# Differential input clock from SI570 clock synthesizer on ZC702
# Constrained to 148.5MHz (1080p60 video resolution)
create_clock -period 6.734 -name video_clk [get_ports video_clk_p]

####################
# Generated Clocks #
####################

# Rename auto-generated clocks from MMCM
create_generated_clock -name clk_75mhz [get_pins system_top_i/clk_wiz_1/inst/mmcm_adv_inst/CLKOUT0]
create_generated_clock -name clk_150mhz [get_pins system_top_i/clk_wiz_1/inst/mmcm_adv_inst/CLKOUT1]

################
# Clock Groups #
################

# video_clk is generated by SI570 clock synthesizer and clk_75mhz/clk_150mhz by MMCM
# There is no known phase relationship, hence they are treated  as asynchronous
set_clock_groups -name async_clks -asynchronous -group {clk_75mhz clk_150mhz} -group video_clk

########################
# Physical Constraints #
########################

# Clock Synthesizer (SI570) on ZC702
set_property PACKAGE_PIN AF14 [get_ports video_clk_p]
set_property PACKAGE_PIN AG14 [get_ports video_clk_n]
set_property IOSTANDARD LVDS_25 [get_ports video_clk_*]
set_property DIFF_TERM TRUE [get_ports video_clk_*]

# HDMI Output (ADV7511) on ZC702
set_property PACKAGE_PIN P28 [get_ports hdmio_clk]
set_property PACKAGE_PIN U21 [get_ports hdmio_vsync]
set_property PACKAGE_PIN R22 [get_ports hdmio_hsync]
set_property PACKAGE_PIN V24 [get_ports hdmio_de]
set_property PACKAGE_PIN AC23 [get_ports hdmio_int_b]
set_property PACKAGE_PIN AD26 [get_ports {hdmio_data[0]}]
set_property PACKAGE_PIN AB26 [get_ports {hdmio_data[1]}]
set_property PACKAGE_PIN AA28 [get_ports {hdmio_data[2]}]
set_property PACKAGE_PIN AC26 [get_ports {hdmio_data[3]}]
set_property PACKAGE_PIN AE30 [get_ports {hdmio_data[4]}]
set_property PACKAGE_PIN Y25 [get_ports {hdmio_data[5]}]
set_property PACKAGE_PIN AA29 [get_ports {hdmio_data[6]}]
set_property PACKAGE_PIN AD30 [get_ports {hdmio_data[7]}]
set_property PACKAGE_PIN Y28 [get_ports {hdmio_data[8]}]
set_property PACKAGE_PIN AF28 [get_ports {hdmio_data[9]}]
set_property PACKAGE_PIN V22 [get_ports {hdmio_data[10]}]
set_property PACKAGE_PIN AA27 [get_ports {hdmio_data[11]}]
set_property PACKAGE_PIN U22 [get_ports {hdmio_data[12]}]
set_property PACKAGE_PIN N28 [get_ports {hdmio_data[13]}]
set_property PACKAGE_PIN V21 [get_ports {hdmio_data[14]}]
set_property PACKAGE_PIN AC22 [get_ports {hdmio_data[15]}]
set_property IOSTANDARD LVCMOS25 [get_ports hdmio_*]
set_property IOB TRUE [get_cells -hierarchical vid_out_formatter_i/in_*_mux_reg*]
