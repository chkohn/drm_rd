set_property PACKAGE_PIN L16  [get_ports  hdmi_clk      ]
#set_property PACKAGE_PIN H15  [get_ports  hdmi_vsync    ]
#set_property PACKAGE_PIN R18  [get_ports  hdmi_hsync    ]
#set_property PACKAGE_PIN T18  [get_ports  hdmi_de       ]
#set_property PACKAGE_PIN U14  [get_ports  hdmi_int      ]
set_property PACKAGE_PIN AB21 [get_ports {hdmi_data[0] }]
set_property PACKAGE_PIN AA21 [get_ports {hdmi_data[1] }]
set_property PACKAGE_PIN AB22 [get_ports {hdmi_data[2] }]
set_property PACKAGE_PIN AA22 [get_ports {hdmi_data[3] }]
set_property PACKAGE_PIN V19  [get_ports {hdmi_data[4] }]
set_property PACKAGE_PIN V18  [get_ports {hdmi_data[5] }]
set_property PACKAGE_PIN V20  [get_ports {hdmi_data[6] }]
set_property PACKAGE_PIN U20  [get_ports {hdmi_data[7] }]
set_property PACKAGE_PIN W21  [get_ports {hdmi_data[8] }]
set_property PACKAGE_PIN W20  [get_ports {hdmi_data[9] }]
set_property PACKAGE_PIN W18  [get_ports {hdmi_data[10]}]
set_property PACKAGE_PIN T19  [get_ports {hdmi_data[11]}]
set_property PACKAGE_PIN U19  [get_ports {hdmi_data[12]}]
set_property PACKAGE_PIN R19  [get_ports {hdmi_data[13]}]
set_property PACKAGE_PIN T17  [get_ports {hdmi_data[14]}]
set_property PACKAGE_PIN T16  [get_ports {hdmi_data[15]}]

set_property IOSTANDARD LVCMOS25 [get_ports hdmi_*]

##################################
#### Mapped fmc_imageon_hdmii_video[15:0]
## HDMII_SPDIF - FMC-H29 (LA24_n)
#set_property PACKAGE_PIN U5 [get_ports fmc_imageon_hdmii_spdif]
## HDMII_Y0    - FMC-H32 (LA28_n)
#set_property PACKAGE_PIN AB4 [get_ports {fmc_imageon_hdmii_video[0]}]
## HDMII_Y1    - FMC-H31 (LA28_p)
#set_property PACKAGE_PIN AB5 [get_ports {fmc_imageon_hdmii_video[1]}]
## HDMII_Y2    - FMC-G31 (LA29_n)
#set_property PACKAGE_PIN AB11 [get_ports {fmc_imageon_hdmii_video[2]}]
## HDMII_Y3    - FMC-C27 (LA27_n)
#set_property PACKAGE_PIN AB1 [get_ports {fmc_imageon_hdmii_video[3]}]
## HDMII_Y4    - FMC-D27 (LA26_n)
#set_property PACKAGE_PIN U11 [get_ports {fmc_imageon_hdmii_video[4]}]
## HDMII_Y5    - FMC-G30 (LA29_p)
#set_property PACKAGE_PIN AA11 [get_ports {fmc_imageon_hdmii_video[5]}]
## HDMII_Y6    - FMC-C26 (LA27_p)
#set_property PACKAGE_PIN AB2 [get_ports {fmc_imageon_hdmii_video[6]}]
## HDMII_Y7    - FMC-D26 (LA26_p)
#set_property PACKAGE_PIN U12 [get_ports {fmc_imageon_hdmii_video[7]}]
## HDMII_CBCR0 - FMC-H38 (LA32_n)
#set_property PACKAGE_PIN AA4 [get_ports {fmc_imageon_hdmii_video[8]}]
## HDMII_CBCR1 - FMC-H37 (LA32_p)
#set_property PACKAGE_PIN Y4 [get_ports {fmc_imageon_hdmii_video[9]}]
## HDMII_CBCR2 - FMC-G37 (LA33_n)
#set_property PACKAGE_PIN Y10 [get_ports {fmc_imageon_hdmii_video[10]}]
## HDMII_CBCR3 - FMC-G36 (LA33_p)
#set_property PACKAGE_PIN Y11 [get_ports {fmc_imageon_hdmii_video[11]}]
## HDMII_CBCR4 - FMC-H35 (LA30_n)
#set_property PACKAGE_PIN AB6 [get_ports {fmc_imageon_hdmii_video[12]}]
## HDMII_CBCR5 - FMC-H34 (LA30_p)
#set_property PACKAGE_PIN AB7 [get_ports {fmc_imageon_hdmii_video[13]}]
## HDMII_CBCR6 - FMC-G34 (LA31_n)
#set_property PACKAGE_PIN AB9 [get_ports {fmc_imageon_hdmii_video[14]}]
## HDMII_CBCR7 - FMC-G33 (LA31_p)
#set_property PACKAGE_PIN AB10 [get_ports {fmc_imageon_hdmii_video[15]}]


## HDMII_LLC   - FMC-G2  (CLK1_M2C_p)
#set_property PACKAGE_PIN Y6 [get_ports fmc_imageon_hdmii_clk]

#set_property IOSTANDARD LVCMOS25 [get_ports fmc_imageon_hdmii_*]
