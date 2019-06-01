// seg : convert counter value to 7segment led display

module seg(
           input wire [7:0] count,
           output reg [7:0] seg
          );

always @(count) begin

  case(count)
    8'h00   : seg <= ~8'h3F;
    8'h01   : seg <= ~8'h06;
    8'h02   : seg <= ~8'h5B;
    8'h03   : seg <= ~8'h4F;
    8'h04   : seg <= ~8'h66;
    8'h05   : seg <= ~8'h6D;
    8'h06   : seg <= ~8'h7D;
    8'h07   : seg <= ~8'h07;
    8'h08   : seg <= ~8'h7F;
    8'h09   : seg <= ~8'h6F;
    8'h0A   : seg <= ~8'h77;
    8'h0B   : seg <= ~8'h7C;
    8'h0C   : seg <= ~8'h39;
    8'h0D   : seg <= ~8'h5E;
    8'h0E   : seg <= ~8'h79;
    8'h0F   : seg <= ~8'h71;
    default : seg <= ~8'h00;
  endcase
end

endmodule