var http = require('http');
var url = require('url');
var	exec = require('child_process');

var port = parseInt(process.argv[2]);

var server = http.createServer(function(req, res){
	var parsedUrl = url.parse(req.url, true);
	var rgbVal = parseInt(parsedUrl.query.v);
	var result;

	if (/^\/api\/setcol/.test(req.url)) {
		result = {
			color: rgbVal
		};

		exec.execFile('./multiColouredLedInterface', ['-v', rgbVal], function (error, stdout, stderr) {
			console.log('stdout: ' + stdout);
			console.log('stderr: ' + stderr);
			
			if (error !== null) {
				console.log('exec error: ' + error);
			}
		});

	} else if (/^\/api\/unixtime/.test(req.url)) {
		result = { wot: "m8" };
	}

	if (result) {
		res.writeHead(200, { 'Content-Type': 'application/json' });
		res.end(JSON.stringify(result));
	} else {
		res.writeHead(404);
		res.end();
	}

	
});

server.listen(port);