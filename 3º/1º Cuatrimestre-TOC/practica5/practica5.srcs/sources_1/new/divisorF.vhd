----------------------------------------------------------------------------------
-- Company:        Universidad Complutense de Madrid
-- Engineer:       
-- 
-- Create Date:    
-- Design Name:    Practica 1b 
-- Module Name:    divisor - rtl
-- Project Name:   Practica 1b 
-- Target Devices: Spartan-3 
-- Tool versions:  ISE 14.1
-- Description:    Creacion de un reloj de 1 Hz a partir de un reloj de 100 MHz
-- Dependencies: 
-- Revision: 
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity divisorF is
  port (
    rst        : in  std_logic;         -- asynch reset
    clk_100mhz : in  std_logic;         -- 100 MHz input clock
    clk_1hz    : out std_logic;         -- 1 Hz output clock
    count1_en  : out std_logic;          
    count2_en  : out std_logic
    );
end divisorF;

architecture rtl of divisorF is

  signal cntr_reg    : unsigned(24 downto 0);
  signal clk_1hz_reg : std_logic;
  
  signal count1_reg : unsigned(24 downto 0);
  signal count1_aux : std_logic;
  
  signal count2_reg : unsigned(24 downto 0);
  signal count2_aux : std_logic;
  
begin

  p_cntr : process(rst, clk_100mhz)
  begin
    if (rst = '1') then
      cntr_reg    <= (others => '0');
      count1_reg    <= (others => '0');
      count2_reg    <= (others => '0');
      clk_1hz_reg <= '0';
      count1_aux <= '0';
      count2_aux <= '0';
    elsif rising_edge(clk_100mhz) then
      if cntr_reg = (24 downto 0 => '1') then
        cntr_reg    <= (others => '0');
        clk_1hz_reg <= not clk_1hz_reg;
      else
        cntr_reg    <= cntr_reg + 1;
        clk_1hz_reg <= clk_1hz_reg;
      end if;
      if count1_reg = "1001101001101100011010001" then
        count1_reg <= (others => '0');
        count1_aux <= not count1_aux;
      else
        count1_reg <= count1_reg + 1;
        count1_aux <= count1_aux;
      end if;
      if count2_reg = "0001101101100011010011111" then
        count2_reg <= (others => '0');
        count2_aux <= not count2_aux;
      else
        count2_reg <= count2_reg + 1;
        count2_aux <= count2_aux;
      end if;
    end if;
  end process p_cntr;

  output_clock : clk_1hz <= clk_1hz_reg;
  count1 : count1_en <= count1_aux;
  count2 : count2_en <= count2_aux;
  
end rtl;
