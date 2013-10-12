##################
# Primary Clocks #
##################

# Differential input clock from SI570 clock synthesizer on ZC702
# Constrained to 148.5MHz (1080p60 video resolution)
create_clock -period 6.734 -name video_clk [get_ports video_clk_p]

# Single-ended input clock coming from external video source via FMC-IMAGEON
# Constrained to 148.5MHz (1080p60 video resolution)
create_clock -period 6.734 -name fmc_imageon_hdmii_clk [get_ports fmc_imageon_hdmii_clk]

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
set_clock_groups -name async_clks -asynchronous -group {clk_75mhz clk_150mhz} -group {video_clk fmc_imageon_hdmii_clk}

# BUFGMUX selects one of the two external clocks for the video capture pipeline
# The two clocks are physically exclusive since they don't exist at the same time
set_clock_groups -name clk_mux -physically_exclusive -group fmc_imageon_hdmii_clk -group video_clk

#####################
# Timing Exceptions #
#####################

# Use fastest clock of the BUFGMUX as the path that timing analysis should be done on
# In this case, both clocks have the same period constraint, so either input 0 or input 1 can be selected
set_case_analysis 0 [get_pins system_top_i/video_capture/vsrc_sel_1/video_sel]

########################
# Physical Constraints #
########################

# Clock Synthesizer (SI570) on ZC702
set_property PACKAGE_PIN Y9 [get_ports video_clk_p]
set_property PACKAGE_PIN Y8 [get_ports video_clk_n]
set_property IOSTANDARD LVDS_25 [get_ports video_clk_*]
set_property DIFF_TERM TRUE [get_ports video_clk_*]

# HDMI Output (ADV7511) on ZC702
set_property PACKAGE_PIN L16 [get_ports hdmio_clk]
set_property PACKAGE_PIN H15 [get_ports hdmio_vsync]
set_property PACKAGE_PIN R18 [get_ports hdmio_hsync]
set_property PACKAGE_PIN T18 [get_ports hdmio_de]
set_property PACKAGE_PIN U14 [get_ports hdmio_int_b]
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

# I2C Chain 2 on FMC-IMAGEON
set_property PACKAGE_PIN AB14 [get_ports fmc_imageon_iic_scl_io]
set_property PACKAGE_PIN AB15 [get_ports fmc_imageon_iic_sda_io]
set_property PACKAGE_PIN Y16 [get_ports fmc_imageon_iic_rst_b]
set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_iic_*]

# HDMI Input (ADV7611) on FMC-IMAGEON
set_property PACKAGE_PIN Y6 [get_ports fmc_imageon_hdmii_clk]
set_property PACKAGE_PIN AB4 [get_ports {fmc_imageon_hdmii_data[0]}]
set_property PACKAGE_PIN AB5 [get_ports {fmc_imageon_hdmii_data[1]}]
set_property PACKAGE_PIN AB11 [get_ports {fmc_imageon_hdmii_data[2]}]
set_property PACKAGE_PIN AB1 [get_ports {fmc_imageon_hdmii_data[3]}]
set_property PACKAGE_PIN U11 [get_ports {fmc_imageon_hdmii_data[4]}]
set_property PACKAGE_PIN AA11 [get_ports {fmc_imageon_hdmii_data[5]}]
set_property PACKAGE_PIN AB2 [get_ports {fmc_imageon_hdmii_data[6]}]
set_property PACKAGE_PIN U12 [get_ports {fmc_imageon_hdmii_data[7]}]
set_property PACKAGE_PIN AA4 [get_ports {fmc_imageon_hdmii_data[8]}]
set_property PACKAGE_PIN Y4 [get_ports {fmc_imageon_hdmii_data[9]}]
set_property PACKAGE_PIN Y10 [get_ports {fmc_imageon_hdmii_data[10]}]
set_property PACKAGE_PIN Y11 [get_ports {fmc_imageon_hdmii_data[11]}]
set_property PACKAGE_PIN AB6 [get_ports {fmc_imageon_hdmii_data[12]}]
set_property PACKAGE_PIN AB7 [get_ports {fmc_imageon_hdmii_data[13]}]
set_property PACKAGE_PIN AB9 [get_ports {fmc_imageon_hdmii_data[14]}]
set_property PACKAGE_PIN AB10 [get_ports {fmc_imageon_hdmii_data[15]}]
set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_hdmii_*]
