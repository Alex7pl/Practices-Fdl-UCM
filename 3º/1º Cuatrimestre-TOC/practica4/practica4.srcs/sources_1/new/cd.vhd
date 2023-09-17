----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.11.2022 17:33:04
-- Design Name: 
-- Module Name: cd - Behavioral
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

entity cd is
 Port ( 
    clk : in std_logic;
    rst_n : in std_logic;
    a : in std_logic_vector (3 downto 0);
    b : in std_logic_vector (3 downto 0);
    ctrl   : in std_logic_vector(7 downto 0);   -- Control vector
    status : out  std_logic_vector(1 downto 0);  -- Status vector
    res : out std_logic_vector (7 downto 0)
 );
end cd;

architecture Behavioral of cd is

    signal n : unsigned (3 downto 0);
    signal add : std_logic_vector (7 downto 0);
    signal acc_r : std_logic_vector (7 downto 0);
    signal a_r : std_logic_vector (7 downto 0);
    signal b_r : std_logic_vector (7 downto 0);
    signal mux_output : std_logic_vector(7 downto 0);

    --control signal
    signal c_mux    : std_logic;
    signal c_acc_ld : std_logic;
    signal c_a_ld   : std_logic;
    signal c_a_sh   : std_logic;
    signal c_b_ld   : std_logic;
    signal c_b_sh   : std_logic;
    signal c_n_ld   : std_logic;
    signal c_n_cu   : std_logic;
    
    --status signals
    
    signal zero : std_logic;
    signal b_zero : std_logic;

begin

    (c_n_cu,
    c_n_ld,
    c_b_sh,
    c_b_ld,
    c_a_sh,
    c_a_ld,
    c_acc_ld,
    c_mux) <= ctrl;
    
    status <= (zero & b_zero);
    
  -----------------------------------------------------------------------------
  -- Comparador con cero
  -----------------------------------------------------------------------------
  p_cmp : process (n) is
  begin
    if n = "000" then
      zero <= '1';
    else
      zero <= '0';
    end if;
  end process p_cmp;
  
  -----------------------------------------------------------------------------
  -- Contador. Observad que la senal cntr esta definida como unsigned luego no
  -- es necesario hacer casting pues el operador "-" entiende la resta de un
  -- unsigned menos 1.
  -----------------------------------------------------------------------------
  p_n : process (clk, rst_n) is
  begin
    if rst_n = '1' then 
        n <= (others => '0');
    elsif rising_edge(clk) then
        if c_n_ld = '1' then
            n <= "0100";
        elsif c_n_cu = '1' then
            n <= n - 1;
        end if;
    end if;
  end process p_n;
  
  -----------------------------------------------------------------------------
  -- Sumador
  -----------------------------------------------------------------------------
  p_add : process (acc_r, a_r) is
  begin  -- process p_add

    add <= std_logic_vector(unsigned(acc_r) + unsigned(a_r));

  end process p_add;
  
  -----------------------------------------------------------------------------
  -- Multiplexor
  -----------------------------------------------------------------------------
  p_mux : process (c_mux, add) is
  begin  -- process p_mux
    if c_mux = '1' then
      mux_output <= (others => '0');
    elsif c_mux = '0' then
      mux_output <= add;
    end if;
  end process p_mux;
  
  -----------------------------------------------------------------------------
  -- Registro con carga paralelo
  -----------------------------------------------------------------------------
  p_acc_r : process (clk, rst_n) is
  begin
    if rst_n = '1' then
      acc_r <= (others => '0');
    elsif rising_edge(clk) then
      if c_acc_ld = '1' then
        acc_r <= mux_output;
      end if;
    end if;
  end process p_acc_r;
  
  -----------------------------------------------------------------------------
  -- Registro carga paralelo / desplazamiento izquierda
  -----------------------------------------------------------------------------
  
    p_a_r : process (clk, rst_n) is
    begin
        if rst_n = '1' then
            a_r <= (others => '0');
        elsif rising_edge(clk) then
            if c_a_ld = '1' then
                a_r <= "0000" & a(3 downto 0);
            elsif c_a_sh = '1' then
                a_r <= a_r(6 downto 0) & '0';
            end if;
        end if;
    end process p_a_r;
    
  -----------------------------------------------------------------------------
  -- Registro carga paralelo / desplazamiento derecha
  -----------------------------------------------------------------------------

    p_b_r : process (clk, rst_n) is
    begin
        if rst_n = '1' then
            b_r <= (others => '0');
        elsif rising_edge(clk) then
            if c_b_ld = '1' then
                b_r <= "0000" & b(3 downto 0);
            elsif c_b_sh = '1' then
                b_r <= '0' & b_r (7 downto 1);
            end if;
        end if;
    end process p_b_r;
    
    p_bzero : b_zero <= b_r(0);
    
    p_res : res <= acc_r(7 downto 0);

end Behavioral;
