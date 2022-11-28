module top_tb();


  reg clk;

  reg stm_pin_1;
  wire mon_pin_2,
       mon_pin_3,
       mon_pin_4,
       mon_pin_5,
       mon_pin_6,
       mon_LED,
       mon_USB_PU;


  initial begin
      $dumpfile("test_tb.vcd");
      $dumpvars(0,top_tb);
  end


  always begin
    #5 clk = ~clk;
  end



  top i_DUT(.CLK(clk), .PIN_1(stm_pin_1), .PIN_2(mon_pin_2), .PIN_3(mon_pin_3),
            .PIN_4(mon_pin_4), .PIN_5(mon_pin_5), .PIN_6(mon_pin_6), .LED(mon_LED),   // User/boot LED next to power LED
           .USBPU(mon_USB_PU)  // USB pull-up resistor
           );

  initial begin
    clk = 1'b0;
    repeat(2000)
      @(posedge clk);
  end
endmodule
