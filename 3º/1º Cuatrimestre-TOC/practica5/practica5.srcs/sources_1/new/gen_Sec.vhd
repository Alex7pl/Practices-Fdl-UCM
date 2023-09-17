----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 27.11.2022 23:00:38
-- Design Name: 
-- Module Name: gen_Sec - Behavioral
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

entity gen_Sec is
 Port (
    rst : in std_logic;
    clk : in std_logic;  
    state : in std_logic_vector(1 downto 0);
    leds : out std_logic_vector(15 downto 0)
 );
end gen_Sec;

architecture Behavioral of gen_Sec is

signal leds_aux : std_logic_vector(15 downto 0);

begin

    p_gen_sec : process(rst, clk, leds_aux) is
    begin
    
        if rst = '1' then
            leds_aux <= (others => '0');
        elsif rising_edge(clk) then
            if state = "00" then
                if leds_aux = "1010101010101010" then
                    leds_aux <= (others => '0');
                elsif leds_aux = "0101010101010101" then
                    leds_aux <= (others => '0');
                else
                    leds_aux <= not leds_aux(0) & leds_aux(15 downto 1);
                end if;            
            elsif state = "01" then
                leds_aux <= (others => '0'); 
            elsif state = "10" then
                leds_aux <= not leds_aux;
            elsif state = "11" then
                if leds_aux = "0101010101010101" then
                    leds_aux <= "1010101010101010";
                else
                    leds_aux <= "0101010101010101";
                end if;
            end if;
        end if;
    end process p_gen_sec;
    
    leds <= leds_aux;

end Behavioral;
