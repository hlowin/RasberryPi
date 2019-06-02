// counter : 16bit counter

module counter(
               input wire clk,
               input wire rst,
               output reg [7:0] count
              );

initial begin
  count <= 8'h00;
end

always @(posedge clk or negedge rst) begin

  if(rst == 1'b0) begin
    count <= 8'h00;
  end
  else if(clk == 1'b1) begin
    if(count >= 8'h0F) begin
      count <= 8'h00;
    end
    else begin
      count <= count + 8'h01;
    end
  end

end

endmodule