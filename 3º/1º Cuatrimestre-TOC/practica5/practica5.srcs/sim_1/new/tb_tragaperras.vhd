----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 28.11.2022 13:34:49
-- Design Name: 
-- Module Name: tb_tragaperras - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity tb_tragaperras is
--  Port ( );
end tb_tragaperras;

architecture Behavioral of tb_tragaperras is

    component tragaperras is
 Port (
    clk : in std_logic;
    rst : in std_logic;
    ini : in std_logic;
    fin : in std_logic;
    leds : out std_logic_vector (15 downto 0);
    display : out std_logic_vector (6 downto 0);
    display_enable : out std_logic_vector (3 downto 0) 
 );
end component;

signal clk, rst_n, ini, fin: std_logic;

signal led: std_logic_vector(15 downto 0);
signal display: STD_LOGIC_VECTOR (6 downto 0);
signal display_enable: STD_LOGIC_VECTOR (3 downto 0);
constant clk_period: time := 10 ns;

begin

i_tragaperras : tragaperras port map(clk, rst_n, ini, fin, led, display, display_enable);

stimulus: process
  begin
  
    -- Put initialisation code here
    rst_n <='1';
    ini <= '0';
    fin <= '0';
    wait for 10 ns;
    rst_n <='0';
    wait for 200 ns;

    ini <='1';
    wait for 10 ns;
    ini <= '0';
    
    wait for 200 ns;
    
    fin <='1';
    wait for 10 ns;
    fin <= '0';
 
    wait;
  end process;
  
clk_process: process 
begin
 clk <= '0';
 wait for clk_period/2;
 clk <= '1';
  wait for clk_period/2;
  end process;

end Behavioral;
