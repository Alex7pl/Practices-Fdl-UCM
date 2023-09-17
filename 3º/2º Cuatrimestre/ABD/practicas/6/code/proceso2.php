<?php

require_once 'c&d.php';

$db = conectar('localhost', 'Alex7pl', 'panciller', 'practica6');

$u = $_POST['nom']; 
$c = $_POST['contr'];
$r = $_POST['repetir'];

if($r == $c){

    $consultado = "INSERT INTO users (Usuario, Contraseña) VALUES ('$u', '$c')";
    if ($db->query($consultado)){
        echo "Usuario creado correctamente <br/>";
    }
    else{
        echo "Error: ". $db->error;
    }
}
else{
    echo "Las contraseñas no coinciden <br/>";
}

desconectar($db);

?>