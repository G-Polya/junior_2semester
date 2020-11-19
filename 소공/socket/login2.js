var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url = require('url');
var express = require('express');
var app = express();
const bodyParser = require('body-parser')
const mysql      = require('mysql');

app.use(bodyParser.urlencoded({extended:false}))

app.set('port', process.env.PORT || 8888);

app.use(express.static('public'));

var objPeople = [
	{ // Object @ 0 index
		username: "sam",
		password: "codify"
	},
	{ // Object @ 1 index
		username: "matt",
		password: "academy"
	},
	{ // Object @ 2 index
		username: "chris",
		password: "forever"
	}

]





function getInfo() {
	var username = document.getElementById('username').value
	var password = document.getElementById('password').value

	for(var i = 0; i < objPeople.length; i++) {
		// check is user input matches username and password of a current index of the objPeople array
		if(username == objPeople[i].username && password == objPeople[i].password) {
			console.log(username + " is logged in!!!")
            // stop the function if this is found to be true
            const success = document.createElement('label');
            success.textContent = username + " is logged in!!"
            document.getElementById("login").appendChild(success);
            return
		}
	}
	console.log("incorrect username or password")
}


var server = http.createServer(app).listen(app.get('port'))

app.get('/', function(req,res){
    var title="Login";
    var template = `
    <!DOCTYPE html>
<html>
    <head>	
        <meta charset="UTF-8">
		<title>JavaScript Simple Login System</title>
		<link rel="shortcut icon" href="favicon.ico">
	</head>
	<body>
    로그인 페이지입니다!
    <br><br><br>


        <div class="login__container">
            <div id="login">
                <form>
                    ID: <input type="text" id="username" placeholder="Choose Username">
                    
                    <br>
                    비밀번호: <input type="text" id="password" placeholer="Choose Password">
                    <button type="button" value="로그인" onclick="${getInfo()}">로그인</button>
                    <button type="button" value="회원가입" onclick="location.href='register.'">회원가입</button>
                </form>
            </div>
            
        </div>
		

		<script src="./loginClient.js"></script>
	</body>
</html>
    `;

    res.writeHead(200);
    res.end(template)
})