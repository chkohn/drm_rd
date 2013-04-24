
#-------------------------------------------
#-------------------------------------------
proc iplevel_update_vid_out_data_width { param_handle } {

    set mhsinst     [xget_hw_parent_handle   $param_handle]
    set data_width  [xget_hw_parameter_value $mhsinst "C_S_AXIS_VIDEO_DATA_WIDTH"]
    set format      [xget_hw_parameter_value $mhsinst "C_S_AXIS_VIDEO_FORMAT"]
    switch $format {
      0   {set num_channels 2}
      1   {set num_channels 3}
      2   {set num_channels 3}
      3   {set num_channels 2}
      4   {set num_channels 3}
      5   {set num_channels 4}
      6   {set num_channels 4}
      7   {set num_channels 2}
      8   {set num_channels 4}
      9   {set num_channels 4}
      10  {set num_channels 4}
      11  {set num_channels 3}
      12  {set num_channels 1}
      13  {set num_channels 1}
   }
   set td_width [expr int($data_width * $num_channels)]
   return $td_width

}

#-------------------------------------------
#-------------------------------------------
proc iplevel_update_s_axis_tdata_width { param_handle } {

    set mhsinst     [xget_hw_parent_handle   $param_handle]
    set data_width  [xget_hw_parameter_value $mhsinst "C_S_AXIS_VIDEO_DATA_WIDTH"]
    set format      [xget_hw_parameter_value $mhsinst "C_S_AXIS_VIDEO_FORMAT"]
    switch $format {
      0   {set num_channels 2}
      1   {set num_channels 3}
      2   {set num_channels 3}
      3   {set num_channels 2}
      4   {set num_channels 3}
      5   {set num_channels 4}
      6   {set num_channels 4}
      7   {set num_channels 2}
      8   {set num_channels 4}
      9   {set num_channels 4}
      10  {set num_channels 4}
      11  {set num_channels 3}
      12  {set num_channels 1}
      13  {set num_channels 1}
   }
   set td_width [expr {int (int((($data_width * $num_channels)+7)/8)*8) }]
   return $td_width

}



