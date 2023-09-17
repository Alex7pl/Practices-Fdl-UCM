<title>Conexion y desconexion</title>
<?php
//Definicion de una pequenafuncionqueabreunaconexion.
function conectar($host, $usuario, $contrasenia='', $b) {
    $db = new mysqli($host, $usuario, $contrasenia, $b);
    if($db) {
        echo'Conexion realizada correctamente.<br/>';
        echo'Informacion sobre el servidor:', mysqli_get_host_info($db), '<br/>';
        echo'Version del servidor:', mysqli_get_server_info($db), '<br/>';
    }
    else {
        printf('Error%d:%s.<br />', mysqli_connect_errno(), mysqli_connect_error());
    }
    return $db;
}
//Definicion de una pequenafuncionquecierraunaconexion.
function desconectar($conexion) {
    if($conexion) {
        $ok = @mysqli_close($conexion);
        if($ok) {
            echo'Desconexion realizada correctamente.<br/>';
        }
        else {
            echo'Fallo en la desconexion.<br/>';
        }
    }
    else {
        echo'Conexion no abierta.<br/>';
    }
}