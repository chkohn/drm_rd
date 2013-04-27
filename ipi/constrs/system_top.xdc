
# I2C_MUX_SCL  - FMC-G18 (LA16_p)
set_property PACKAGE_PIN AB14 [get_ports fmc_imageon_iic_0_scl_io]
set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_iic_0_scl_io]
set_property SLEW SLOW [get_ports fmc_imageon_iic_0_scl_io]
set_property DRIVE 8 [get_ports fmc_imageon_iic_0_scl_io]

# I2C_MUX_SDA  - FMC-G19 (LA16_n)
set_property PACKAGE_PIN AB15 [get_ports fmc_imageon_iic_0_sda_io]
set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_iic_0_sda_io]
set_property SLEW SLOW [get_ports fmc_imageon_iic_0_sda_io]
set_property DRIVE 8 [get_ports fmc_imageon_iic_0_sda_io]

# I2C_MUX_RST# - FMC-D9  (LA01_n_CC)
set_property PACKAGE_PIN Y16 [get_ports fmc_imageon_iic_0_Reset_pin]
set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_iic_0_Reset_pin]
set_property SLEW SLOW [get_ports fmc_imageon_iic_0_Reset_pin]
set_property DRIVE 8 [get_ports fmc_imageon_iic_0_Reset_pin]

##################################
### Mapped fmc_imageon_hdmii_video[15:0]
# HDMII_SPDIF - FMC-H29 (LA24_n)
set_property PACKAGE_PIN U5 [get_ports fmc_imageon_hdmii_spdif]
# HDMII_Y0    - FMC-H32 (LA28_n)
set_property PACKAGE_PIN AB4 [get_ports {fmc_imageon_hdmii_video[0]}]
# HDMII_Y1    - FMC-H31 (LA28_p)
set_property PACKAGE_PIN AB5 [get_ports {fmc_imageon_hdmii_video[1]}]
# HDMII_Y2    - FMC-G31 (LA29_n)
set_property PACKAGE_PIN AB11 [get_ports {fmc_imageon_hdmii_video[2]}]
# HDMII_Y3    - FMC-C27 (LA27_n)
set_property PACKAGE_PIN AB1 [get_ports {fmc_imageon_hdmii_video[3]}]
# HDMII_Y4    - FMC-D27 (LA26_n)
set_property PACKAGE_PIN U11 [get_ports {fmc_imageon_hdmii_video[4]}]
# HDMII_Y5    - FMC-G30 (LA29_p)
set_property PACKAGE_PIN AA11 [get_ports {fmc_imageon_hdmii_video[5]}]
# HDMII_Y6    - FMC-C26 (LA27_p)
set_property PACKAGE_PIN AB2 [get_ports {fmc_imageon_hdmii_video[6]}]
# HDMII_Y7    - FMC-D26 (LA26_p)
set_property PACKAGE_PIN U12 [get_ports {fmc_imageon_hdmii_video[7]}]
# HDMII_CBCR0 - FMC-H38 (LA32_n)
set_property PACKAGE_PIN AA4 [get_ports {fmc_imageon_hdmii_video[8]}]
# HDMII_CBCR1 - FMC-H37 (LA32_p)
set_property PACKAGE_PIN Y4 [get_ports {fmc_imageon_hdmii_video[9]}]
# HDMII_CBCR2 - FMC-G37 (LA33_n)
set_property PACKAGE_PIN Y10 [get_ports {fmc_imageon_hdmii_video[10]}]
# HDMII_CBCR3 - FMC-G36 (LA33_p)
set_property PACKAGE_PIN Y11 [get_ports {fmc_imageon_hdmii_video[11]}]
# HDMII_CBCR4 - FMC-H35 (LA30_n)
set_property PACKAGE_PIN AB6 [get_ports {fmc_imageon_hdmii_video[12]}]
# HDMII_CBCR5 - FMC-H34 (LA30_p)
set_property PACKAGE_PIN AB7 [get_ports {fmc_imageon_hdmii_video[13]}]
# HDMII_CBCR6 - FMC-G34 (LA31_n)
set_property PACKAGE_PIN AB9 [get_ports {fmc_imageon_hdmii_video[14]}]
# HDMII_CBCR7 - FMC-G33 (LA31_p)
set_property PACKAGE_PIN AB10 [get_ports {fmc_imageon_hdmii_video[15]}]


# HDMII_LLC   - FMC-G2  (CLK1_M2C_p)
set_property PACKAGE_PIN Y6 [get_ports fmc_imageon_hdmii_clk]

set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_hdmii_*]

#################################
## Mapped fmc_imageon_hdmio_video[15:0]
# HDMIO_SPDIF - FMC-H28 (LA24_p)
set_property PACKAGE_PIN U6 [get_ports fmc_imageon_hdmio_spdif]
# HDMIO_Y0    - FMC-G28 (LA25_n)
set_property PACKAGE_PIN AB12 [get_ports {fmc_imageon_hdmio_video[0]}]
# HDMIO_Y1    - FMC-G27 (LA25_p)
set_property PACKAGE_PIN AA12 [get_ports {fmc_imageon_hdmio_video[1]}]
# HDMIO_Y2    - FMC-H26 (LA21_n)
set_property PACKAGE_PIN V4 [get_ports {fmc_imageon_hdmio_video[2]}]
# HDMIO_Y3    - FMC-D24 (LA23_n)
set_property PACKAGE_PIN W12 [get_ports {fmc_imageon_hdmio_video[3]}]
# HDMIO_Y4    - FMC-H25 (LA21_p)
set_property PACKAGE_PIN V5 [get_ports {fmc_imageon_hdmio_video[4]}]
# HDMIO_Y5    - FMC-G25 (LA22_n)
set_property PACKAGE_PIN U9 [get_ports {fmc_imageon_hdmio_video[5]}]
# HDMIO_Y6    - FMC-C23 (LA18_n_CC)
set_property PACKAGE_PIN AA8 [get_ports {fmc_imageon_hdmio_video[6]}]
# HDMIO_Y7    - FMC-D23 (LA23_p)
set_property PACKAGE_PIN V12 [get_ports {fmc_imageon_hdmio_video[7]}]
# HDMIO_CBCR0 - FMC-G24 (LA22_p)
set_property PACKAGE_PIN U10 [get_ports {fmc_imageon_hdmio_video[8]}]
# HDMIO_CBCR1 - FMC-H23 (LA19_n)
set_property PACKAGE_PIN T6 [get_ports {fmc_imageon_hdmio_video[9]}]
# HDMIO_CBCR2 - FMC-C22 (LA18_p_CC)
set_property PACKAGE_PIN AA9 [get_ports {fmc_imageon_hdmio_video[10]}]
# HDMIO_CBCR3 - FMC-D21 (LA17_n_CC)
set_property PACKAGE_PIN AA6 [get_ports {fmc_imageon_hdmio_video[11]}]
# HDMIO_CBCR4 - FMC-H22 (LA19_p)
set_property PACKAGE_PIN R6 [get_ports {fmc_imageon_hdmio_video[12]}]
# HDMIO_CBCR5 - FMC-G22 (LA20_n)
set_property PACKAGE_PIN U4 [get_ports {fmc_imageon_hdmio_video[13]}]
# HDMIO_CBCR6 - FMC-D20 (LA17_p_CC)
set_property PACKAGE_PIN AA7 [get_ports {fmc_imageon_hdmio_video[14]}]
# HDMIO_CBCR7 - FMC-G21 (LA20_p)
set_property PACKAGE_PIN T4 [get_ports {fmc_imageon_hdmio_video[15]}]


# HDMIO_CLK   - FMC-G3  (CLK1_M2C_n)
set_property PACKAGE_PIN Y5 [get_ports fmc_imageon_hdmio_clk]

set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_hdmio_*]


#set_clock_groups -asynchronous -group clk_fpga_0 -group CLKOUT0
