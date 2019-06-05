// main : main module

// PIN ASSIGN 
// in_clk      : PIN_R8
// in_rst      : PIN_J15
// in_func     : PIN_E1
// out_led[0]  : PIN_A15
// out_led[1]  : PIN_A13
// out_led[2]  : PIN_B13
// out_led[3]  : PIN_A11
// out_led[4]  : PIN_D1
// out_led[5]  : PIN_F3
// out_led[6]  : PIN_B1
// out_led[7]  : PIN_L3
// out_dip     : PIN_N12
// out_seg[0]  : PIN_T10
// out_seg[1]  : PIN_P11
// out_seg[2]  : PIN_N9
// out_seg[3]  : PIN_R16
// out_seg[4]  : PIN_L16
// out_seg[5]  : PIN_P15
// out_seg[6]  : PIN_R14
// out_seg[7]  : PIN_N16

// Raspberry Pi
// out_func(GPIO_029:PIN_B11) <-> GPIO02


module main(
//  input  wire       in_clk,
  input  wire       in_rst,
  input  wire       in_func,
  input  wire [3:0] in_data,
//  output wire       out_dip,
  output wire [7:0] out_seg,
  output wire [7:0] out_led,
  output wire       out_func
);

// assign out_dip = in_clk;

// wire [7:0] count;
// assign out_led = count;

wire [7:0] seg;
assign out_seg = seg;

assign out_func = in_func;

wire [7:0] data;
assign data = 8'h00 + in_data; 
assign out_led = data;

// counter counter0(.clk(in_clk), .rst(in_rst), .count(count));
seg seg0(.data(data), .seg(seg));

endmodule