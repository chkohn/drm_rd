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
create_generated_clock -name clk_75mhz [get_pins system_i/clk_wiz_1/U0/mmcm_adv_inst/CLKOUT0]
create_generated_clock -name clk_150mhz [get_pins system_i/clk_wiz_1/U0/mmcm_adv_inst/CLKOUT1]

################
# Clock Groups #
################

# video_clk is generated by SI570 clock synthesizer and clk_75mhz/clk_150mhz by MMCM
# There is no known phase relationship, hence they are treated  as asynchronous
set_clock_groups -name async_clks -asynchronous -group {clk_75mhz clk_150mhz} -group video_clk

#############
# I/O Delay #
#############

#  2ns of output delay for HDMI output
set_output_delay -clock video_clk -min 2.000 [get_ports hdmio_data*]

########################
# Physical Constraints #
########################

set_property PACKAGE_PIN Y9 [get_ports video_clk_p]
set_property PACKAGE_PIN Y8 [get_ports video_clk_n]
set_property IOSTANDARD LVDS_25 [get_ports video_clk_*]

set_property PACKAGE_PIN L16 [get_ports hdmio_clk]
set_property PACKAGE_PIN H15 [get_ports hdmio_vsync]
set_property PACKAGE_PIN R18 [get_ports hdmio_hsync]
set_property PACKAGE_PIN T18 [get_ports hdmio_de]
set_property PACKAGE_PIN U14 [get_ports hdmio_int]
set_property PACKAGE_PIN AB21 [get_ports {hdmio_data[0]}]
set_property PACKAGE_PIN AA21 [get_ports {hdmio_data[1]}]
set_property PACKAGE_PIN AB22 [get_ports {hdmio_data[2]}]
set_property PACKAGE_PIN AA22 [get_ports {hdmio_data[3]}]
set_property PACKAGE_PIN V19 [get_ports {hdmio_data[4]}]
set_property PACKAGE_PIN V18 [get_ports {hdmio_data[5]}]
set_property PACKAGE_PIN V20 [get_ports {hdmio_data[6]}]
set_property PACKAGE_PIN U20 [get_ports {hdmio_data[7]}]
set_property PACKAGE_PIN W21 [get_ports {hdmio_data[8]}]
set_property PACKAGE_PIN W20 [get_ports {hdmio_data[9]}]
set_property PACKAGE_PIN W18 [get_ports {hdmio_data[10]}]
set_property PACKAGE_PIN T19 [get_ports {hdmio_data[11]}]
set_property PACKAGE_PIN U19 [get_ports {hdmio_data[12]}]
set_property PACKAGE_PIN R19 [get_ports {hdmio_data[13]}]
set_property PACKAGE_PIN T17 [get_ports {hdmio_data[14]}]
set_property PACKAGE_PIN T16 [get_ports {hdmio_data[15]}]
set_property IOSTANDARD LVCMOS25 [get_ports hdmio_*]
