var socket = io.connect('http://192.168.1.111:3000');
socket.on('news', function (data) {
	console.log(data);
	socket.emit('reply', { my: 'hello server' });
});

$(document).ready(function(){
	var lastTime = 0;

	$('#picker').spectrum({
		color: '#f00',
		flat: true,
		move: function(color){
			var date = new Date();
			var time = date.getTime();
			if(time - lastTime > 100){
				var rgb = color.toRgb()
				var numb = Number(zeroFill(rgb.r) + zeroFill(rgb.g) + zeroFill(rgb.b));
				console.log(numb);
				socket.emit('color', numb);
				lastTime = time;
			}
		}
	});
});

function zeroFill(num) {
	if(num < 10){
		return "00" + num;
	} else if (num < 100) {
		return "0" + num;
	} else {
		return num + "";
	}
}