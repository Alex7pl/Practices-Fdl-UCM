<?php

$dias_semana = array("L" => "Lunes", "M" => "Martes", "X" => "Miércoles", "J" => "Jueves", "V" => "Viernes", "S" => "Sábado", "D" => "Domingo", );
$seleccionados = array("L", "X", "S", "D");

foreach($seleccionados as $val){
    echo $dias_semana[$val]. " ";
}

?>