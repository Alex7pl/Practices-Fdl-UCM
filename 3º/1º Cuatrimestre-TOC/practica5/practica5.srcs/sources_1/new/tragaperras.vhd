----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 27.11.2022 20:27:59
-- Design Name: 
-- Module Name: tragaperras - Behavioral
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

entity tragaperras is
 Port (
    clk : in std_logic;
    rst : in std_logic;
    ini : in std_logic;
    fin : in std_logic;
    leds : out std_logic_vector (15 downto 0);
    display : out std_logic_vector (6 downto 0);
    display_enable : out std_logic_vector (3 downto 0) 
 );
end tragaperras;

architecture Behavioral of tragaperras is

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
    
    --se?ales necesarias para debouncer
    
    signal boton_rising1 : std_logic;
    signal boton_falling1 : std_logic;
    signal boton_rising2 : std_logic;
    signal boton_falling2 : std_logic;
    signal ini_aux : std_logic;
    signal fin_aux : std_logic;
    
    --instanciamos cd
    
    component cd is
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
    end component;
    
    signal display1_aux : std_logic_vector(3 downto 0);
    signal display2_aux : std_logic_vector(3 downto 0);
    
    --instanciamos uc
    
    component uc is
     Port ( 
        clk    : in  std_logic;                      -- clock
        rst_n  : in  std_logic;                      -- reset
        ini    : in  std_logic;                      -- External control signal
        fin    : in std_logic;                       -- External control signal
        state  : out std_logic_vector(1 downto 0);   --Out signal for leds
        ctrl   : out std_logic_vector(2 downto 0);   -- Control vector
        status : in  std_logic_vector(1 downto 0)    -- Status vector
     );
    end component;
    
    signal state_aux : std_logic_vector(1 downto 0);
    
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
    
    --instanciamos divisor
    
    component divisorF is
     port (
        rst        : in  std_logic;         -- asynch reset
        clk_100mhz : in  std_logic;         -- 100 MHz input clock
        clk_1hz    : out std_logic;         -- 1 Hz output clock
        count1_en  : out std_logic;          
        count2_en  : out std_logic
     );
    end component;
    
    signal count1_en_aux  : std_logic;          
    signal count2_en_aux  : std_logic;
    signal clk_1hz : std_logic;
    
    --instanciamos generador
    
    component gen_Sec is
     Port (
        rst : in std_logic;
        clk : in std_logic;  
        state : in std_logic_vector(1 downto 0);
        leds : out std_logic_vector(15 downto 0)
     );
    end component;
    
    --instanciamos las se?ales de control
    
    signal ctrl   : std_logic_vector(2 downto 0);  -- Control vector
    signal status : std_logic_vector(1 downto 0);  --Status vector

begin

    i_debouncer_ini : debouncer port map (
    clk             => clk,
    rst             => '0',
    x               => ini,
    xDeb            => ini_aux,
    xDebFallingEdge => boton_falling1,
    xDebRisingEdge  => boton_rising1);
    
    i_debouncer_fin : debouncer port map (
    clk             => clk,
    rst             => '0',
    x               => fin,
    xDeb            => fin_aux,
    xDebFallingEdge => boton_falling2,
    xDebRisingEdge  => boton_rising2);
    
    i_uc : uc port map (
    clk => clk,
    rst_n => rst,
    ini => ini_aux,
    fin => fin_aux,
    state => state_aux,
    ctrl => ctrl,
    status => status
    );
    
    i_cd : cd port map (
    clk => clk_1hz,
    rst => rst,
    count1_en => count1_en_aux,
    count2_en => count2_en_aux,
    ctrl => ctrl,
    status => status,
    display1 => display1_aux,
    display2 => display2_aux
    );
    
    i_divisorF : divisorF port map (
    rst => rst,
    clk_100mhz => clk,
    clk_1hz => clk_1hz,
    count1_en => count1_en_aux,       
    count2_en => count2_en_aux
    );
    
    i_displays : displays port map (
    clk => clk_1hz,
    rst => rst,
    digito_0 => display1_aux,
    digito_1 => display2_aux,
    digito_2 => "0000",
    digito_3 => "0000",
    display => display,
    display_enable => display_enable
    );
    
    i_genSec : gen_Sec port map (
    rst => rst,
    clk => clk_1hz, 
    state => state_aux,
    leds => leds
    );

end Behavioral;
