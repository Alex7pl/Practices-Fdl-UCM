----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06.11.2022 21:34:54
-- Design Name: 
-- Module Name: celda - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity celda is
generic (
    num_bits: natural := 4
);
port ( 
    x : in std_logic_vector(num_bits-1 downto 0);
    c_in : in std_logic_vector(num_bits-1 downto 0);
    c_out : out std_logic_vector(num_bits-1 downto 0)
);
end celda;

architecture rtl of celda is
    
    signal x_c2: signed(num_bits-1 downto 0);
    signal c_in_c2: signed(num_bits-1 downto 0);
    signal c_out_c2: signed(num_bits-1 downto 0) := (others => '0');
    
begin
    
    x_c2 <= signed(x);
    c_in_c2 <= signed(c_in);
    
    p_mayor: process(x_c2, c_in_c2)
    begin
       if x_c2 > c_in_c2 then
           c_out_c2 <= x_c2;
       else
           c_out_c2 <= c_in_c2;
       end if;   
    end process p_mayor;
    
    c_out <= std_logic_vector(c_out_c2);
    
end rtl;
