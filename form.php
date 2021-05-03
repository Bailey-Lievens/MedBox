<?php
 if (!empty($_POST)) {
    $fp = fopen("json_schedule.json", "w");
    fprintf($fp, json_encode($_POST));
    fclose($fp);

    $fp = fopen("txt_schedule.txt", "w");
    fprintf($fp, json_encode($_POST));
    fclose($fp);
 }
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Medbox edit</title>

    <link rel="stylesheet" href="index.css">
    <link rel="stylesheet" href="form.css">
</head>
<body>
    <img src="images/logo.png" id="logo_image">

    <form action="" method="post" id="changeMedboxForm">
        <div class="tab">
            <h1>Monday</h1>
            <label for="monday_morning">Morning</label>
            <p><input placeholder="morning" type="text" name="monday_morning"></p>
            <label for="monday_midday">Midday</label>
            <p><input placeholder="midday" type="text" name="monday_midday"></p>
            <label for="monday_evenening">Evening</label>
            <p><input placeholder="evening" type="text" name="monday_evening"></p>
        </div>

        <div class="tab">
            <h1>Tuesday</h1>
            <label for="tuesday_morning">Morning</label>
            <p><input placeholder="morning" type="text" name="tuesday_morning"></p>
            <label for="tuesday_midday">Midday</label>
            <p><input placeholder="midday" type="text" name="tuesday_midday"></p>
            <label for="tuesday_evenening">Evening</label>
            <p><input placeholder="evening" type="text" name="tuesday_evening"></p>
        </div>

        <div class="tab">
            <h1>Wednesday</h1>
            <label for="wednesday_morning">Morning</label>
            <p><input placeholder="morning" type="text"  name="wednesday_morning"></p>
            <label for="wednesday_midday">Midday</label>
            <p><input placeholder="midday" type="text" name="wednesday_midday"></p>
            <label for="wednesday_evenening">Evening</label>
            <p><input placeholder="evening" type="text" name="wednesday_evening"></p>
        </div>

        <div class="tab">
            <h1>Thursday</h1>
            <label for="thursday_morning">Morning</label>
            <p><input placeholder="morning" type="text" name="thursday_morning"></p>
            <label for="thursday_midday">Midday</label>
            <p><input placeholder="midday" type="text" name="thursday_midday"></p>
            <label for="thursday_evenening">Evening</label>
            <p><input placeholder="evening" type="text" name="thursday_evening"></p>
        </div>

        <div class="tab">
            <h1>Friday</h1>
            <label for="friday_morning">Morning</label>
            <p><input placeholder="morning" type="text" name="friday_morning"></p>
            <label for="friday_midday">Midday</label>
            <p><input placeholder="midday" type="text" name="friday_midday"></p>
            <label for="friday_evenening">Evening</label>
            <p><input placeholder="evening" type="text" name="friday_evening"></p>
        </div>

        <div class="tab">
            <h1>Saturday</h1>
            <label for="saturday_morning">Morning</label>
            <p><input placeholder="morning" type="text" name="saturday_morning"></p>
            <label for="saturday_midday">Midday</label>
            <p><input placeholder="midday" type="text" name="saturday_midday"></p>
            <label for="saturday_evening">Evening</label>
            <p><input placeholder="evening" type="text" name="saturday_evening"></p>
        </div>

        <div class="tab">
            <h1>Sunday</h1>
            <label for="sunday_morning">Morning</label>
            <p><input placeholder="morning" type="text" name="sunday_morning"></p>
            <label for="sunday_midday">Midday</label>
            <p><input placeholder="midday" type="text" name="sunday_midday"></p>
            <label for="sunday_evening">Evening</label>
            <p><input placeholder="evening" type="text" name="sunday_evening"></p>
        </div>

        <div style="overflow: auto;">
            <div style="float: right;">
                <button type="button" id="prevBtn" onclick="nextPrev(-1)">Previous</button>
                <button type="button" id="nextBtn" onclick="nextPrev(1)">Next</button>
                <input id="submitBtn" style="display: none;" type="submit" value="Submit">
            </div>
        </div>

        <div style="text-align: center;margin-top: 40px;">
            <span class="step"></span>
            <span class="step"></span>
            <span class="step"></span>
            <span class="step"></span>
            <span class="step"></span>
            <span class="step"></span>
            <span class="step"></span>
        </div>
    </form>
    
    <script src="form.js"></script>
</body>
</html>