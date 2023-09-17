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
        num_entradas : natural := 16
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
    type r1_array is array (3 downto 0) of std_logic_vector(num_bits-1 downto 0);

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
    signal r1: r1_array;
    
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
               
               for a in 0 to 3 loop
                r1(a) <= C(1, a);
               end loop;
	       end if;
	   end if;
	end process sync;
	
	generar_prim_celda: for l in 0 to (num_entradas/2**(1))-1 generate
	       dut1: celda
	           generic map (
	               num_bits => num_bits
	           )
	           port map (
	               x => Xa(l*2),
	               c_in => Xa(l*2+1),
	               c_out => C(0,l)
	           );
	end generate generar_prim_celda;
	

	gen_seg_celda: for j in 0 to (num_entradas/2**(2))-1 generate
	       comparador_j: celda
	           generic map (
	               num_bits => num_bits
	           )
	           port map (
	               x => C(0,j*2),
	               c_in => C(0,j*2+1),
	               c_out => C(1, j)
	           );
	   end generate gen_seg_celda;

	

	   gen_comparadores: for j in 0 to (num_entradas/2**(3))-1 generate
	       comparador_i: celda
	           generic map (
	               num_bits => num_bits
	           )
	           port map (
	               x => r1(j*2),
	               c_in => r1(j*2+1),
	               c_out => C(2, j)
	           );
	   end generate gen_comparadores;

	
	gen_niveles: for i in 3 to Log2(num_entradas)-1 generate
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
