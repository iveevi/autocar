var steer = 0
var drive = 0

document.addEventListener('keydown', function (event) {
        // Use switch
        if (event.keyCode == 37)
                steer = -1;
        if (event.keyCode == 38)
                drive = 1;
        else if (event.keyCode == 39)
                steer = 1;
        else if (event.keyCode == 40)
                drive = -1;
        else
                return;

        $.ajax({
                type: "POST",
                contentType: "application/json;charset=utf-8",
                url: "/input",
                traditional: "true",
                data: JSON.stringify({
                        steer, drive
                }),
                dataType: "json"
        });
});