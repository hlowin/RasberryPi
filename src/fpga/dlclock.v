// dlclock : delay count for counter

`define HZ 2
`define DLCLOCK_HZ (28'd50000000 / (`HZ * 2))

module dlclock(
               input wire clk,
               output reg dlclk
              );

reg [27:0] delay;

initial begin
  delay   <= `DLCLOCK_HZ;
  dlclk   <= 1'b0;
end

always @(posedge clk) begin

  if(delay == 28'd0) begin
    delay   <= `DLCLOCK_HZ;
    case(dlclk)
      1'b0 : dlclk <= 1'b1;
      1'b1 : dlclk <= 1'b0;
      default : dlclk <= 1'bx;
    endcase
  end
  else begin
    delay   <= delay - 28'd1;
  end
end

endmodule