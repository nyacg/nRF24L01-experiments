var express = require('express');
var router = express.Router();
var exec = require('child_process');
var url = require('url');
var path = require('path');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'RGB Controller' });
});

router.get('/api/setcol', function(req, res){
	var parsedUrl = url.parse(req.url, true);
	var rgbVal = parseInt(parsedUrl.query.v);

	setCol(rgbVal);

	res.end("colour set to: " + rgbVal);
});

function setCol(colVal) {
	var dirPath = path.join(path.dirname(path.dirname(__dirname)), 'examples/');
	var filePath = path.join(path.dirname(path.dirname(__dirname)), 'examples/multiColouredLedInterface');
	console.log(filePath + " -v " + colVal);

	exec.execFile('multiColouredLedInterface', ['-v', colVal], {cwd: dirPath}, function (error, stdout, stderr) {
		console.log('stdout: ' + stdout);
		console.log('stderr: ' + stderr);
		
		if (error !== null) {
		  console.log('exec error: ' + error + "\n");
		}
	});
}

module.exports = router;