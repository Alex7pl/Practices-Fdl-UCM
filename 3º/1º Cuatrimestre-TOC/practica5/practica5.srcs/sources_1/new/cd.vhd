----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 27.11.2022 20:29:12
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

entity cd is
 Port (
    clk : in std_logic;
    rst : in std_logic; 
    count1_en : in std_logic;
    count2_en : in std_logic;
    ctrl : in std_logic_vector(2 downto 0);  
    status : out std_logic_vector(1 downto 0);
    display1 : out std_logic_vector(3 downto 0);
    display2 : out std_logic_vector(3 downto 0)
 );
end cd;

architecture Behavioral of cd is

    --intanciamos componentes necesarios
    
    COMPONENT p5_bram_1
     PORT (
        clka : IN STD_LOGIC;
        wea : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
        addra : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
        dina : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
        douta : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
     );
    END COMPONENT;
    
    COMPONENT p5_bram_2
     PORT (
        clka : IN STD_LOGIC;
        wea : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
        addra : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
        dina : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
        douta : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)
     );
    END COMPONENT;
    
    component contador is
     port (
        rst    : in std_logic;
        stop   : in std_logic; 
        clk    : in std_logic; 
        cont: out std_logic_vector(3 downto  0)
     );
    end component contador;
    
    --salidas de ambos componentes
    
    signal cont1_s : std_logic_vector(3 downto 0);
    signal cont2_s : std_logic_vector(3 downto 0);
    signal stop : std_logic_vector(3 downto 0);
    
    --salidas de las bram
    
    signal bram1_s : std_logic_vector(3 downto 0);
    signal bram2_s : std_logic_vector(3 downto 0);
    
    --salidas de los dos registros
    
    signal cont1_r : std_logic_vector(3 downto 0);
    signal cont2_r : std_logic_vector(3 downto 0);
    
    signal status_aux : std_logic;
    
    --señales de memorias que no se utilizan
    
    signal wea : STD_LOGIC_VECTOR(0 DOWNTO 0) := (others => '0');
    signal dina : STD_LOGIC_VECTOR(3 DOWNTO 0) := (others => '0');
    
    --control signal
    
    signal c_cont1_ld    : std_logic;
    signal c_cont2_ld    : std_logic;
    signal c_cont_stop   : std_logic;
    
    --status signals
    
    signal premio : std_logic;
    signal cmp : std_logic;

begin

   (c_cont_stop,
    c_cont2_ld,
    c_cont1_ld) <= ctrl;
    
    status <= (cmp & premio);

    i_contador_1 : contador port map (
        rst => rst,
        stop => count1_en,
        clk => clk,
        cont => cont1_s
    );
    
    i_contador_2 : contador port map (
        rst => rst,
        stop => count2_en,
        clk => clk,
        cont => cont2_s
    );
    
    i_contador_stop : contador port map (
        rst => rst,
        stop => c_cont_stop,
        clk => clk,
        cont => stop
    );
    
    i_bram_1 : p5_bram_1 PORT MAP (
        clka => clk,
        wea => wea,
        addra => cont1_s,
        dina => dina,
        douta => bram1_s
    );
    
    i_bram_2 : p5_bram_2 PORT MAP (
        clka => clk,
        wea => wea,
        addra => cont2_s,
        dina => dina,
        douta => bram2_s
    );
    
    p_cmp_tiempo : process(stop) is
    begin
        if stop = "1001" then
            cmp <= '1';
        else
            cmp <= '0';
        end if;
    end process;
    
    p_cmp_reg : process(cont1_r, cont2_r) is
    begin
        if cont1_r = cont2_r then
            premio <= '1';
        else
            premio <= '0';
        end if;
    end process;
    
    p_reg_1 : process(rst, clk) is
    begin
        if rst = '1' then
            cont1_r <= (others => '0');
        elsif rising_edge(clk) then
            if c_cont1_ld = '1' then
                cont1_r <= bram1_s;
            end if;
        end if;
    end process;
    
    p_reg_2 : process(rst, clk) is
    begin
        if rst = '1' then
            cont2_r <= (others => '0');
        elsif rising_edge(clk) then
            if c_cont2_ld = '1' then
                cont2_r <= bram2_s;
            end if;
        end if;
    end process;
    
    display1 <= cont1_r;
    display2 <= cont2_r;

end Behavioral;
