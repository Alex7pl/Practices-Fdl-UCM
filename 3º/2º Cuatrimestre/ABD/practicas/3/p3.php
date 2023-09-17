<!DOCTYPE html>
<html>
<head>
<title>Tablas con PHP</title>
<style>
table, th, td {
border : 1px solid black ;
}
</style>
</head>
<body>
    <?php
    
    echo "<table>";

    echo "<tr>";

    for ($i = 0; $i <= 10; $i++){ echo "<th> $i </th>"; }

    echo "</tr>";

    for ($j = 1; $j <= 10; $j++){

        echo "<tr>";
        
        echo "<th> $j </th>";

        for ($h = 1; $h <= 10; $h++){

            $aux = $j * $h;

            echo "<td> $aux </td>";

        }

        echo "</tr>";
    }

    echo "</table>";
    ?>
</body>
</html>