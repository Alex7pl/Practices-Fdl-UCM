<!DOCTYPE html>
<html>
<head>
    <title>Resultados</title>
    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <title>Page Title</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <link rel='stylesheet' type='text/css' media='screen' href='main.css'>
    <script src='main.js'></script>
</head>
<body>
    <div>
    <?php
    echo "<b><i> Datos del formulario </i></b>", '<br>', '<br>';
    echo "<b>Nombre: </b>".$_POST['nom'] , '<br>';
    echo "<b>Teléfono: </b>".$_POST['tel'] , '<br>';
    echo "<b>E-mail: </b>".$_POST['mail'] , '<br>';
    echo "<b>Dirección: </b>".$_POST['dir'] , '<br>', '<br>';

    echo "<b>Primer plato: </b>".$_POST['primero'] , '<br>';
    echo "<b>Segundo plato: </b>".$_POST['segundo'] , '<br>';
    
    echo "<b>Bebida elegida: </b>";
    if($_POST['cafeote'] == "C"){echo "Café";} else {echo "Té";}
    echo '<br>';

    echo "<b>Observaciones: </b>";
    if(empty($_POST['obs'])){

        echo "Sin observaciones";
    }
    else{

        echo $_POST['obs'];
    }
    echo '<br>', '<br>';

    if($_POST['condi'] == "ok"){echo "acepta las condiciones";}
    ?>
    </div>
</body>
</html>