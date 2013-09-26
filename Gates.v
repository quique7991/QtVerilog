`timescale 1ns/10ps
module Inverter #(parameter Delay = 6) (
	input wire in,
	output reg out
);

	always @(in)
		#Delay out = ~in;

endmodule

module DLatch #(parameter DelayCLK = 6, parameter DelayD = 7) (
	input wire d,
	input wire clk,
	output reg o
);
	always @(posedge clk)
		o <= #DelayCLK d;

	always @(d)
		begin
			if(clk)
				o <= #DelayD d;
		end

	initial
		o = 0;

endmodule

module DFlipFlop #(parameter DelayClk = 1) (
	input wire d,
	input wire clk,
	output reg o
);

	always @(posedge clk)
		#DelayClk o = d;

	initial
		o = 0;
endmodule

module Mux #(parameter DelSelOut = 21, parameter DelInOut = 17) (
	input wire [3:0] In,
	input wire [1:0] Select,
	output reg out
);

	always @(In)
		begin
			case(Select)
				0: out <= #DelInOut In[0];
				1: out <= #DelInOut In[1];
				2: out <= #DelInOut In[2];
				3: out <= #DelInOut In[3];
				default: out = out;
			endcase				
		end

	always @(Select)
		begin
			case(Select)
				2'b00:  out <= #DelSelOut In[0];
				2'b01:  out <= #DelSelOut In[1];
				2'b10:  out <= #DelSelOut In[2];
				2'b11:  out <= #DelSelOut In[3];
				default: out = out;
			endcase				
		end
		

endmodule
