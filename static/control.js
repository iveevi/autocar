var steer = 0
var drive = 0

$('#dummy').click(function () {
        console.log('Sending...');
        console.log(steer);
        console.log(drive);
        
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