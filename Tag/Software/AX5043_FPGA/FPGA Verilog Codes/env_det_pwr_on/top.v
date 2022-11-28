`define SMARTRF_SETTING_IOCFG2     8'h29 // RX Symbol Tick
`define SMARTRF_SETTING_IOCFG0     8'h06 // Asserts when Sync word sent/received until end of packet
`define SMARTRF_SETTING_FIFOTHR    8'h47 // changing from 0x47 to 0x07 only changes the values of TEST1 and TEST2.
`define SMARTRF_SETTING_PKTLEN     8'h01 // variable packet length is allowed so this must be a non 0 number indicating the max packet size that is allowed
`define SMARTRF_SETTING_PKTCTRL1   8'h00 // do not append status, no PQI
`define SMARTRF_SETTING_PKTCTRL0   8'h00 // packet mode with fixed packet length, CRC disabled
`define SMARTRF_SETTING_ADDR       8'h00 // made same as rx
`define SMARTRF_SETTING_CHANNR     8'h00 // made same as rx
`define SMARTRF_SETTING_FSCTRL1    8'h06 // set to 0x06 and not 0x08 so that the IF freq is 152.3MHz, this is the optimal value of
`define SMARTRF_SETTING_FSCTRL0    8'h00 // made same as rx
`define SMARTRF_SETTING_FREQ2      8'h23
`define SMARTRF_SETTING_FREQ1      8'h31
`define SMARTRF_SETTING_FREQ0      8'h3B
`define SMARTRF_SETTING_MDMCFG4    8'hC5 // changes channel b/w, must keep same for Tx and Rx
`define SMARTRF_SETTING_MDMCFG3    8'h43 // changes datarate, must be same for Tx and Rx
`define SMARTRF_SETTING_MDMCFG2    8'h33 // OOK, 20/32 sync word match
`define SMARTRF_SETTING_MDMCFG1    8'h22 // Default value anyway
`define SMARTRF_SETTING_MDMCFG0    8'hF8 // Default value for channel spacing.
`define SMARTRF_SETTING_DEVIATN    8'h35 // Must be approx same as Rx for demodulation to be correct
`define SMARTRF_SETTING_MCSM1      8'h30 // stay in IDLE mode after transmitting a packet
`define SMARTRF_SETTING_MCSM0      8'h18
`define SMARTRF_SETTING_FOCCFG     8'h16 // changes freq offset loop gain, freq compensation loop gain and saturation point for freq offset compensation algorithm
`define SMARTRF_SETTING_AGCCTRL2   8'h03 // Gain control, set to same as rx
`define SMARTRF_SETTING_AGCCTRL1   8'h00 // Chooses relative threshold for carrier sense - Needs to be set later along with MDMCFG1 - 08 disables absolute and relative carrier threshold.
`define SMARTRF_SETTING_AGCCTRL0   8'h91 // made same as rx
`define SMARTRF_SETTING_WORCTRL    8'hFB // event 0 resolution and time out is maximised
`define SMARTRF_SETTING_FREND1     8'hB6 // adjusts currents for rx, made same as rx
`define SMARTRF_SETTING_FREND0     8'h17 // adjusts currents for tx and the value should be given b
`define SMARTRF_SETTING_BSCFG      8'h1C // made same as rx
`define SMARTRF_SETTING_FSCAL3     8'hE9 // made same as rx
`define SMARTRF_SETTING_FSCAL2     8'h2A
`define SMARTRF_SETTING_FSCAL1     8'h00
`define SMARTRF_SETTING_FSCAL0     8'h1F
`define SMARTRF_SETTING_TEST2      8'h81
`define SMARTRF_SETTING_TEST1      8'h35
`define SMARTRF_SETTING_TEST0      8'h09
`define SMARTRF_SETTING_POWER      8'h03 // -30dbm must be stored in the PA Table


module top(input CLK, input PIN_1, output PIN_2, output PIN_3,
           output LED,   // User/boot LED next to power LED
           output USBPU  // USB pull-up resistor
           );



wire clk_10mhz, env_input;
reg power_output;
reg enable;
wire led_test;

SB_PLL40_CORE usb_pll_inst (
  .REFERENCECLK(CLK),
  .PLLOUTCORE(clk_10mhz),
  .RESETB(1'b1),
  .BYPASS(1'b0),
  .LATCHINPUTVALUE(1'b1)
);

// Fin=16, Fout=10;
defparam usb_pll_inst.DIVR = 0;
defparam usb_pll_inst.DIVF = 9;
defparam usb_pll_inst.DIVQ = 4;
defparam usb_pll_inst.FILTER_RANGE = 3'b001;
defparam usb_pll_inst.FEEDBACK_PATH = "SIMPLE";
defparam usb_pll_inst.DELAY_ADJUSTMENT_MODE_FEEDBACK = "FIXED";
defparam usb_pll_inst.FDA_FEEDBACK = 4'b0000;
defparam usb_pll_inst.DELAY_ADJUSTMENT_MODE_RELATIVE = "FIXED";
defparam usb_pll_inst.FDA_RELATIVE = 4'b0000;
defparam usb_pll_inst.SHIFTREG_DIV_MODE = 2'b00;
defparam usb_pll_inst.PLLOUT_SELECT = "GENCLK";
defparam usb_pll_inst.ENABLE_ICEGATE = 1'b1;


assign env_input = PIN_1;
assign PIN_2 = match;
assign PIN_3 = power_output;
assign LED = power_output;

//////////////////////////////////////Simulated Power on Reset///////////////////////////////////////

reg [5:0] rst_cnt = 0;
wire rst_n = &rst_cnt;

always @(posedge clk_10mhz) begin

    rst_cnt <= rst_cnt + !rst_n;

end

/////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////Shift Reg and power_output/////////////////////////////////////

always @ (posedge clk_10mhz or negedge rst_n) begin

  if (!rst_n) begin
    power_output <= 1'b0;
  end

  else if (match) begin
    power_output <= 1'b1;
  end

end

reg [7:0] reg_data;

always @(posedge clk_10mhz or negedge rst_n) begin

    if (!rst_n) begin
      reg_data <= 8'h00;
    end

    else begin
      reg_data <= {reg_data[6:0], env_input};
    end

end

/////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////Comparsion Circuit/////////////////////////////////////////////

wire [7:0] preamble;
wire [7:0] comparison;
wire match;

assign preamble = 8'h0f;

assign comparison = preamble ~^ reg_data;

//**TODO: Make sure we don't take in any other information during the 1s power output is high

assign match = &comparison;
assign led_test = match;

/////////////////////////////////////////////////////////////////////////////////////////////////////


endmodule
