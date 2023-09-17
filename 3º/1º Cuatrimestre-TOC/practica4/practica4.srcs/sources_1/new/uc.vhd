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
    fin    : out std_logic;                      -- External control signal
    ctrl   : out std_logic_vector(7 downto 0);   -- Control vector
    status : in  std_logic_vector(1 downto 0)  -- Status vector
 );
end uc;

architecture Behavioral of uc is
    
    type t_st is (s0, s1, s2, s3, s4);
    signal current_state, next_state : t_st;
    signal zero, b_zero : std_logic;
    
begin

    --señales de status a internas para trabajar con ellas en separado
    
    p_status_signals : (zero, b_zero) <= status;
    
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
  p_next_state : process (current_state, ini, zero, b_zero) is
  begin  -- process p_next_state
    case current_state is
      when s0 =>
        if ini = '1' then
          next_state <= s1;
        else
          next_state <= s0;
        end if;
      when s1 =>
        next_state <= s2;
      when s2 =>
        if zero = '1' then
            next_state <= s0;
        elsif b_zero = '1' then
            next_state <= s4;
        else 
            next_state <= s3;
        end if;        
      when s3 =>
        next_state <= s2;
      when s4 =>
        next_state <= s2;
      when others => null;
    end case;
  end process p_next_state;
  
  p_outputs : process (current_state) is
  
    constant c_mux    : std_logic_vector(7 downto 0) := "00000001";
    constant c_acc_ld : std_logic_vector(7 downto 0) := "00000010";
    constant c_a_ld   : std_logic_vector(7 downto 0) := "00000100";
    constant c_a_sh   : std_logic_vector(7 downto 0) := "00001000";
    constant c_b_ld   : std_logic_vector(7 downto 0) := "00010000";
    constant c_b_sh   : std_logic_vector(7 downto 0) := "00100000";
    constant c_n_ld   : std_logic_vector(7 downto 0) := "01000000";
    constant c_n_cu   : std_logic_vector(7 downto 0) := "10000000";
  
  begin
  
    ctrl <= (others => '0');
    
    case current_state is
        when s0 =>
            ctrl <= (others => '0');
            fin  <= '1';
        when s1 =>
            ctrl <= c_mux or c_acc_ld or c_a_ld or c_b_ld or c_n_ld;
            fin  <= '0';
        when s2 =>
            ctrl <= (others => '0');
            fin  <= '0';
        when s3 =>
            ctrl <= c_a_sh or c_b_sh or c_n_cu;
            fin  <= '0';
        when s4 =>
            ctrl <= c_acc_ld or c_a_sh or c_b_sh or c_n_cu;
            fin  <= '0';
        end case;  
  end process p_outputs;



end Behavioral;
