----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 14.11.2022 18:25:28
-- Design Name: 
-- Module Name: redArbol - Behavioral
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

entity redArbol is
    generic ( 
        num_bits     : natural := 4;
        num_entradas : natural := 4
    );
    port(
        rst  : in  std_logic;
        clk  : in  std_logic;
        X : in  std_logic_vector (num_entradas*num_bits-1 downto 0);
        S : out std_logic_vector (num_bits-1 downto 0)
    );
end redArbol;

architecture Behavioral of redArbol is

    --funcion
    function Log2( input:integer ) return integer is
        variable temp, log: integer;
    begin
        temp := input;
        log := 0;
        while (temp > 1) loop
            temp := temp/2;
            log := log+1;
        end loop;
        return log;
    end function log2;

    type c_array is array (Log2(num_entradas) - 1 downto 0, num_entradas - 2 downto 0) of std_logic_vector(num_bits-1 downto 0);
    type x_array is array (num_entradas-1 downto 0) of std_logic_vector(num_bits-1 downto 0);

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

    sync: process(clk, rst)
	begin
	   if rising_edge(clk) then 
	       if rst = '1' then 
	           for h in 0 to num_entradas - 1 loop
                    Xa(h) <= (others => '0');
               end loop;
	       else
	           for k in 0 to num_entradas - 1 loop
                    Xa(k) <= X(k*4 + 3 downto k*4); 
               end loop;
	       end if;
	   end if;
	end process sync;
	
	genera_celda: for l in 0 to (num_entradas/2**(1))-1 generate
	       dut1: celda
	           generic map (
	               num_bits => num_bits
	           )
	           port map (
	               x => Xa(l*2),
	               c_in => Xa(l*2+1),
	               c_out => C(0,l)
	           );
	   end generate genera_celda;
	
	gen_niveles: for i in 1 to Log2(num_entradas)-1 generate
	   gen_comparadores: for j in 0 to (num_entradas/2**(i+1))-1 generate
	       comparador_i: celda
	           generic map (
	               num_bits => num_bits
	           )
	           port map (
	               x => C(i-1,j*2),
	               c_in => C(i-1,j*2+1),
	               c_out => C(i, j)
	           );
	   end generate gen_comparadores;
	end generate gen_niveles;
	           
	S <= C(Log2(num_entradas) - 1, 0);
	
end Behavioral;
