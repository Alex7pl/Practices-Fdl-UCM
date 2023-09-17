<?php

require_once 'c&d.php';

$db = conectar('localhost', 'Alex7pl', 'panciller', 'practica6');

$u = $_POST['nom']; 
$c = $_POST['contr'];

$consultado = "SELECT Usuario, Contraseña FROM users WHERE Usuario LIKE '". $u. "'";
$consulta = $db->query($consultado);

$encontrado = false;

$row = $consulta->fetch_assoc();

if($row != null){

    if($row['Contraseña'] == $c){
        echo "Acceso correcto, bienvenido ". $u;
    }
    else{
        echo "Contraseña incorrecta para el usuario ". $u;
    }
}
else{

    header('Location: alta.html');
    desconectar($db);
    exit;
}

?>