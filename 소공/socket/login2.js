var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url = require('url');
var qs = require("querystring");
var express = require('express');
var app = express();
const bodyParser = require('body-parser')
const mysql      = require('mysql');


var template = require("./template.js");
const { response } = require('express');

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








var server = http.createServer(app).listen(app.get('port'))

app.get('/', function(req,res){

    var _url = req.url;
    var queryData = url.parse(_url, true).query;
    var pathname = url.parse(_url,true).pathname;
    if(pathname==="/")
    {
        var html = template.HTML()
        res.writeHead(200)
        res.end(html)
    } else if(pathname==="/socket") {
        var html = template.HTML();
        var body="";
        req.on("data", function(data){
            body = body+data;
        })
    }

    req.on("end", function(){
        var post = qs.parse(body);
        var userid = post.userid
        var userpw = post.userpw
    
        console.log(userid)
    })


    // function getInfo() {
    //     var username = 
    //     var password = $("#password").val();
    
    //     for(var i = 0; i < objPeople.length; i++) {
    //         // check is user input matches username and password of a current index of the objPeople array
    //         if(username == objPeople[i].username && password == objPeople[i].password) {
    //             console.log(username + " is logged in!!!")
    //             // stop the function if this is found to be true
    //             const success = document.createElement('label');
    //             success.textContent = username + " is logged in!!"
    //             document.getElementById("login").appendChild(success);
    //             return
    //         }
    //     }
    //     console.log("incorrect username or password")
    // }

    var title="Login";



})