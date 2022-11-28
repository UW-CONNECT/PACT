module shift_reg(input clk, input rst, input din, output [7:0] dout);

//TODO: make 16 bits

//internal signals
reg [7:0] reg_data;

always @(rst)
  begin
    reg_data <= 8'h00;
  end

always @(posedge clk)
  begin
    reg_data <= {reg_data[6:0], din};

  end

assign dout = reg_data;

endmodule
