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

entity contador is
    port (
     rst    : in std_logic;
     stop   : in std_logic; 
     clk    : in std_logic; 
     cont: out std_logic_vector(3 downto  0)
    );
end contador;

architecture rtl of contador is
   signal count : unsigned(3 downto  0);
   
   component divisor is 
        port (
         clk_100mhz : in  std_logic;         -- 100 MHz input clock
         clk_1hz    : out std_logic          -- 1 Hz output clock
        );
    end component;
    
    signal clk_1hz : std_logic;
begin
    
    dut : divisor port map (
        clk_100mhz => clk,
        clk_1hz => clk_1hz
     );

    p_contador: process (clk_1hz) is 
    begin
        if rising_edge(clk_1hz) then
            if rst = '1' then
                count <= (others => '0');
            else
                if stop = '0' then
                    if count = (3 downto 0 => '1') then
                        count <= (others => '0');
                    else
                        count <= count + 1;
                    end if;
                end if;
            end if;
         end if;
     end process p_contador;
     
    cont <= std_logic_vector(count);
end architecture rtl;
                
                