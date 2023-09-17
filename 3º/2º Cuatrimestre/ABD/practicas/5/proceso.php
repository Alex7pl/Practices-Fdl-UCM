<!DOCTYPE html>
<html>
<head>
<title>Resultados</title>
<style>
table, th, td {
border : 1px solid black ;
}
</style>
</head>
<body>
    <div>
    <?php 
    $baseD = array("Alex7pl" => "poolofrito", "Sergio" => "amo", "coco123" => "susma");

    if(array_key_exists($_POST['nom'], $baseD)){

        echo "Error, el usuario ya existe";
    }
    else{

        $baseD[$_POST['nom']] = $_POST['contr'];

        echo "<table>";
        foreach($baseD as $key => $value){
            echo "<tr>";
            echo "<td> $key </td>";
            echo "<td> $value </td>";
            echo "</tr>";
        }
        echo "</table>";
    }
    ?>
    </div>
</body>
</html>