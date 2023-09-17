----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.11.2022 17:33:04
-- Design Name: 
-- Module Name: uc - Behavioral
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

entity uc is
 Port ( 
    clk    : in  std_logic;                      -- clock
    rst_n  : in  std_logic;                      -- reset
    ini    : in  std_logic;                      -- External control signal
    fin    : in std_logic;                       -- External control signal
    state  : out std_logic_vector(1 downto 0);   --Out signal for leds
    ctrl   : out std_logic_vector(2 downto 0);   -- Control vector
    status : in  std_logic_vector(1 downto 0)    -- Status vector
 );
end uc;

architecture Behavioral of uc is
    
    type t_st is (s0, s1, s2, s3);
    signal current_state, next_state : t_st;
    signal cmp, premio : std_logic;
    
begin

    p_status_signals : (cmp, premio) <= status;
    
    --registro de estados
    
    p_status_reg : process (clk, rst_n) is
    begin
    
        if rst_n = '1' then
            current_state <= s0;
        elsif rising_edge(clk) then
            current_state <= next_state;
        end if;
    end process p_status_reg;
    
    -----------------------------------------------------------------------------
  -- Proceso estado siguiente.
  -----------------------------------------------------------------------------
  p_next_state : process (current_state, ini, fin, cmp, premio) is
  begin  -- process p_next_state
    case current_state is
      when s0 =>
        if ini = '1' then
          next_state <= s1;
        else
          next_state <= s0;
        end if;
      when s1 =>
        if fin = '1' then
            if premio = '1' then
                next_state <= s2;
            else
                next_state <= s3;
            end if;
        else
            next_state <= s1;    
        end if;
      when s2 =>
        if cmp = '1' then
          next_state <= s0;
        else
          next_state <= s2;
        end if;         
      when s3 =>
        if cmp = '1' then
          next_state <= s0;
        else
          next_state <= s3;
        end if;
      when others => null;
    end case;
  end process p_next_state;
  
  p_outputs : process (current_state) is
  
    constant c_cont1_ld    : std_logic_vector(2 downto 0) := "001";
    constant c_cont2_ld    : std_logic_vector(2 downto 0) := "010";
    constant c_cont_stop   : std_logic_vector(2 downto 0) := "100";
  
  begin
  
    ctrl <= (others => '0');
    
    case current_state is
        when s0 =>
            ctrl <= (others => '0');
            state <= "00";
        when s1 =>
            ctrl <= c_cont1_ld or c_cont2_ld;
            state <= "01";
        when s2 =>
            ctrl <= c_cont_stop;
            state <= "10";
        when s3 =>
            ctrl <= c_cont_stop;
            state <= "11";
        end case;  
  end process p_outputs;



end Behavioral;