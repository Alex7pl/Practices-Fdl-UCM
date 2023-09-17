----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10.10.2022 18:46:32
-- Design Name: 
-- Module Name: And - Behavioral
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


library ieee;
use ieee.std_logic_1164.all;

entity ex3 is
    port (
     op1 : in std_logic_vector(3 downto 0);
     op2 : in std_logic_vector(3 downto 0);
     sal : out std_logic_vector(3 downto 0)
    );
end ex3;

architecture rtl of ex3 is
    
begin

    sal <= op1 and op2;
    
end architecture rtl;
