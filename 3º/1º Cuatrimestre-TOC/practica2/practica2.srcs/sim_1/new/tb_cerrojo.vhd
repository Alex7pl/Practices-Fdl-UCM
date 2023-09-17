----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03.10.2022 20:11:11
-- Design Name: 
-- Module Name: tb_cerrojo - Behavioral
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

entity tb_cerrojo is
end tb_cerrojo;

architecture Behavioral of tb_cerrojo is

component cerrojo is
    port (
     rst_n   : in std_logic;
     clk     : in std_logic; 
     bot     : in std_logic;
     clave   : in std_logic_vector(7 downto 0);
     leds    : out std_logic_vector(15 downto 0);
     display: out std_logic_vector(6 downto 0)
    );
end component;

signal rst_n, clk, bot : std_logic;
signal clave : std_logic_vector(7 downto 0);

signal leds : std_logic_vector(15 downto 0);
signal display : std_logic_vector(6 downto 0);

begin

    dut : cerrojo port map (
        rst_n => rst_n,
        clk => clk,
        bot => bot,
        clave => clave,
        leds => leds,
        display => display
    );
    
      -- Input clock
  p_clk : process
  begin
    clk <= '0', '1' after 10 ns;
    wait for 20 ns;
  end process p_clk;
  
   p_stim : process
   begin
    rst_n  <= '0';
    bot <= '0';
    wait for 50 ns;
    wait until rising_edge(clk);
    rst_n <= '1';
    wait until rising_edge(clk);
    clave <= "00000001";
    wait until rising_edge(clk);
    bot <= '1';
    wait until rising_edge(clk);
    bot <= '0';
    wait;
  end process;

end Behavioral;
