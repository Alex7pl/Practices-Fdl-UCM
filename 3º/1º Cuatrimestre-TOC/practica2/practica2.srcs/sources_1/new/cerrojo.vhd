----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 01.10.2022 17:39:15
-- Design Name: 
-- Module Name: cerrojo - Behavioral
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

entity cerrojo is
    port (
     rst_n   : in std_logic;
     clk     : in std_logic; 
     bot     : in std_logic;
     clave   : in std_logic_vector(7 downto 0);
     leds    : out std_logic_vector(15 downto 0);
     display : out std_logic_vector(6 downto 0)
    );
end cerrojo;

architecture Behavioral of cerrojo is

    --estados de la maquina

    type estado_t is (inicial_st, cuatro_st, tres_st, dos_st, uno_st, final_st);
    signal estado_actual, estado_siguiente : estado_t;

    --inicializamos componentes necesarios del cerrojo(conversor y debouncer)

    component conv_7seg is
        port (
         x       : in  std_logic_vector (3 downto 0);
         display : out std_logic_vector (6 downto 0)
        );
    end component;

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

    --creamos señales necesarias para los componentes

    signal intentos : std_logic_vector (3 downto 0);
    signal rstC : std_logic;
    signal boton_rising : std_logic;
    signal boton, load_reg : std_logic;
    signal boton_falling : std_logic;

    --señal del comparador

    signal eq : std_logic;

    --señal donde se guarda la contraseña

    signal contrasena : std_logic_vector(7 downto 0);
    

begin
    
    dut1 : debouncer port map (
        rst => rstC,
        clk => clk,
        x => bot,
        xDeb => boton,
        xDebFallingEdge => boton_falling,
        xDebRisingEdge => boton_rising
    );
    
    dut2 : conv_7seg port map(
        x => intentos,
        display => display
    );

    p_reg : process (clk, rst_n)
    begin
        if rst_n = '0' then
            estado_actual <= inicial_st;
        elsif rising_edge(clk) then
            estado_actual <= estado_siguiente;
        end if;
    end process;

    p_next_state : process (estado_actual, boton_rising, eq)
    begin
    
        load_reg <= '0';
        
        case estado_actual is
            when inicial_st =>
                if boton_rising = '1' then
                    estado_siguiente <= cuatro_st;
                else 
                    estado_siguiente <= inicial_st;
                end if;
                load_reg <= '1';
            when cuatro_st =>
                if boton_rising = '1' then
                    if eq = '1' then
                        estado_siguiente <= inicial_st;
                    else 
                        estado_siguiente <= tres_st;
                    end if;
                else
                    estado_siguiente <= cuatro_st;
                end if;
            when tres_st =>
                if boton_rising = '1' then
                    if eq = '1' then
                        estado_siguiente <= inicial_st;
                    else 
                        estado_siguiente <= dos_st;
                    end if;
                else
                    estado_siguiente <= tres_st;
                end if;
            when dos_st =>
                if boton_rising = '1' then
                    if eq = '1' then
                        estado_siguiente <= inicial_st;
                    else 
                        estado_siguiente <= uno_st;
                    end if;
                else
                    estado_siguiente <= dos_st;
                end if;
            when uno_st =>
                if boton_rising = '1' then
                    if eq = '1' then
                        estado_siguiente <= inicial_st;
                    else 
                        estado_siguiente <= final_st;
                    end if;
                else
                    estado_siguiente <= uno_st;
                end if;
            when final_st =>
                estado_siguiente <= final_st;
        end case;
    end process;

    p_outputs : process(estado_actual)
    begin
        case estado_actual is
            when inicial_st =>
                intentos <= "0100";
                leds <= (others => '1');
            when cuatro_st =>
                intentos <= "0100";
                leds <= (others => '0');
            when tres_st =>
                intentos <= "0011";
                leds <= (others => '0');
            when dos_st =>
                intentos <= "0010";
                leds <= (others => '0');
            when uno_st =>
                intentos <= "0001";
                leds <= (others => '0');
            when final_st =>
                intentos <= "0000";
                leds <= (others => '0');
        end case;
    end process;

    reg_clave : process(clk, rst_n)
    begin
        if (rst_n = '0') then
            contrasena <= (others => '0');
        elsif (rising_edge(clk)) then
            if (load_reg='1') then
                contrasena <= clave;
            end if;
        end if;
    end process;

    p_comparator : process(clave, contrasena)
    begin
        if clave = contrasena then
            eq <= '1';
        else
            eq <= '0';
        end if;
    end process;
    
    p_reset : process(rst_n)
    begin 
        if rst_n = '0' then
            rstC <= '1';
        else
            rstC <= '0';
        end if;
    end process;

end Behavioral;
