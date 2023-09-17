----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 20.11.2022 17:33:04
-- Design Name: 
-- Module Name: multiplicador - Behavioral
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

entity multiplicador is
 Port (
    clk : in std_logic;
    rst_n : in std_logic;
    ini : in std_logic;
    a : in std_logic_vector (3 downto 0);
    b : in std_logic_vector (3 downto 0);
    leds : out std_logic_vector (15 downto 0);
    display : out std_logic_vector (6 downto 0);
    display_enable : out std_logic_vector (3 downto 0)
 );
end multiplicador;

architecture Behavioral of multiplicador is

    --instanciamos debouncer
    
    component debouncer is
     port (
        rst             : in  std_logic;
        clk             : in  std_logic;
        x               : in  std_logic;
        xDeb            : out std_logic;
        xDebFallingEdge : out std_logic;
        xDebRisingEdge  : out std_logic
     );
    end component;
    
    --señales necesarias para debouncer
    
    signal boton_rising : std_logic;
    signal boton : std_logic;
    signal boton_falling : std_logic;

    --instanciamos cd
    
    component cd is
     Port ( 
        clk : in std_logic;
        rst_n : in std_logic;
        a : in std_logic_vector (3 downto 0);
        b : in std_logic_vector (3 downto 0);
        ctrl : in std_logic_vector(7 downto 0);   -- Control vector
        status : out  std_logic_vector(1 downto 0);  -- Status vector
        res : out std_logic_vector (7 downto 0)
     );
    end component cd;
    
    --instanciamos uc
    
    component uc is
     Port ( 
        clk    : in  std_logic;                      -- clock
        rst_n  : in  std_logic;                      -- reset
        ini    : in  std_logic;                      -- External control signal
        fin    : out std_logic;                      -- External control signal
        ctrl   : out std_logic_vector(7 downto 0);   -- Control vector
        status : in  std_logic_vector(1 downto 0)  -- Status vector
     );
    end component uc;
    
    --instanciamos el display
    
    component displays
     Port ( 
        rst : in STD_LOGIC;
        clk : in STD_LOGIC;       
        digito_0 : in  STD_LOGIC_VECTOR (3 downto 0);
        digito_1 : in  STD_LOGIC_VECTOR (3 downto 0);
        digito_2 : in  STD_LOGIC_VECTOR (3 downto 0);
        digito_3 : in  STD_LOGIC_VECTOR (3 downto 0);
        display : out  STD_LOGIC_VECTOR (6 downto 0);
        display_enable : out  STD_LOGIC_VECTOR (3 downto 0)
     );
    end component displays;
    
    --instanciamos las señales de control
    
    signal ctrl   : std_logic_vector(7 downto 0);  -- Control vector
    signal status : std_logic_vector(1 downto 0);  --Status vector
    
    --señal con la multiplicacion
    
    signal mult_aux: std_logic_vector(7 downto 0);
    
    --señal para saber si ha acabado
    
    signal done : std_logic;

begin

    i_debouncer : debouncer port map (
    clk             => clk,
    rst             => rst_n,
    x               => ini,
    xDeb            => boton,
    xDebFallingEdge => boton_falling,
    xDebRisingEdge  => boton_rising);

    i_cd : cd port map (
    clk    => clk,
    rst_n  => rst_n,
    a      => a,
    b      => b,
    ctrl   => ctrl,
    status => status,
    res    => mult_aux);

    i_uc : uc port map (
    clk    => clk,
    rst_n  => rst_n,
    ini    => boton,
    fin    => done,
    ctrl   => ctrl,
    status => status);
    
    i_displays : displays port map (
    clk => clk,
    rst => rst_n,
    digito_0 => mult_aux(3 downto 0),
    digito_1 => mult_aux(7 downto 4),
    digito_2 => "0000",
    digito_3 => "0000",
    display => display,
    display_enable => display_enable
    );
    
    i_leds : process (done) is
    begin
    
        if done = '1' then
            leds <= (others => '1');
        else
            leds <= (others => '0');
        end if;
    end process i_leds;

end Behavioral;
