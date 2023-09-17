----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 13.11.2022 16:02:21
-- Design Name: 
-- Module Name: redIter - Behavioral
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

entity redIter is
 generic (
    num_bits: natural := 4;
    num_entradas: natural := 4
 );
 port ( 
    X: in std_logic_vector(num_entradas*num_bits-1 downto 0);
    S: out std_logic_vector(num_bits-1 downto 0)  
 );
end redIter;

architecture Behavioral of redIter is
    
    type c_array is array (num_entradas - 2 downto 0) of std_logic_vector(num_bits-1 downto 0);
    type x_array is array (num_entradas - 1 downto 0) of std_logic_vector(num_bits-1 downto 0);
    
    --instanciamos la celda como componente
    component celda is
        generic (
            num_bits: natural := 4
        );
        port ( 
            x : in std_logic_vector(num_bits-1 downto 0);
            c_in : in std_logic_vector(num_bits-1 downto 0);
            c_out : out std_logic_vector(num_bits-1 downto 0)
        );
    end component;
    
    signal C: c_array;
    signal Xa: x_array;
    
begin
    
    rellenar: process(X)
    begin
        for j in 0 to num_entradas - 1 loop
        Xa(j) <= X(j*4 + 3 downto j*4); 
        end loop;
    end process rellenar;
    
    dut1: celda
    generic map (
        num_bits => num_bits
    )
    port map(
        x => Xa(0),
        c_in => Xa(1),
        c_out => C(0)
    );
    
    genera_celdas: for i in 1 to num_entradas-2 generate
        i_celda: celda port map (
            Xa(i + 1), 
            C(i - 1), 
            C(i)
        );
    end generate genera_celdas;
    
    S <= C(num_entradas-2);

end Behavioral;
