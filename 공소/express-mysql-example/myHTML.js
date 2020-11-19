var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url = require('url');
var express = require('express');
var app = express();
const bodyParser = require('body-parser')
const mysql      = require('mysql');
const dbconfig   = require('./config/database.js');
const connection = mysql.createConnection(dbconfig);

app.use(bodyParser.urlencoded({extended:false}))

app.set('port', process.env.PORT || 3000);
app.use(express.static('public'));



app.post('/fileupload/:id', function (req, res) {
    let path = req.params.id;
    let fpath = path.replace(/,/g, '/');
    var form = new formidable.IncomingForm(); //객체 할당
    //field값(필드 매개변수) 받는 부분
    form.parse(req, function (err, fields, files) {
        var oldpath = files.filetoupload.path;
        var newpath = fpath + '/' + files.filetoupload.name;
        fs.rename(oldpath, newpath, function (err) {
            if (err){
                res.send(`<script type="text/javascript">
                alert("파일을 선택해 주세요");
                history.back();
                </script>`);
                res.end();
            }
            else{
                res.writeHead(302, { Location: '/' });
                res.end();
            }
            
        });
    });
})

app.post('/addpart/',(req,res) => {
    var part=req.body.part;
    let addpart='./upload/'+part;
    fs.mkdir(addpart,err=>{
        if(err && err.cod != 'EEXIST'){
            res.send(`<script type="text/javascript">
            alert("파트가 존재하거나 입력되지 않았습니다");
            history.back();
            </script>`);
            res.end();
        }
        else{
            res.writeHead(302, { Location: '/' });
            res.end();
        }
        
    })
    
});

app.post('/deletepart/:id', function (req, res) {
    let path = req.params.id;
    let fpath = path.replace(/,/g, '/');

    fs.rmdir(fpath,err=>{
        if(err && err.cod != 'EEXIST') {
            res.send(`<script type="text/javascript">
            alert("파일이 있어 파트삭제 불가능");
            history.back();
            </script>`);
            res.end();
        }
        else{
            res.writeHead(302, { Location: '/' });
            res.end();
        }
       
    })
});

app.post('/delete/:id', function (req, res) {
    let path = req.params.id;
    let fpath = path.replace(/,/g, '/');

    fs.unlink(fpath, function (err) {
        if (err) throw err;
        console.log('file deleted');
        res.writeHead(302, { Location: '/' });
        res.end();

    });

});

app.get('/download/:id', function (req, res) {
    let filename = req.params.id.toString();
    let rfilename = filename.replace(/,/g, '/');
    let filepath = './upload/' + rfilename;
    res.download(filepath);
});
var groupName=[];
var firstnames=[];
var lastnames=[];

var server = http.createServer(app).listen(app.get('port'), function () {
    connection.query('SELECT name from mdl_groups', (error, rows) => {
        if (error) throw error;
        for (var i in rows){
            groupName.push(rows[i].name);
        }
      });
    
    connection.query(`select mdl_user.firstname, mdl_user.lastname 
                    from mdl_user
                    inner join mdl_groups_members on mdl_user.id=mdl_groups_members.userid;`, (error, rows) =>{
                        if(error) throw error;
                        for(var i in rows){
                            firstnames.push(rows[i].firstname)
                            lastnames.push(rows[i].lastname)
                        }
                    })
      
    }
);

 function showMembers(firstnames) {
    const member_template = ``;
    for(var i in firstnames.length){
        
    }
 }



app.get('/', function (req, res) {
    //res.send(db);


    var title = 'Welcome';
    var template = `
    <!DOCTYPE html>
    <html>
    <head>
    <meta charset="UTF-8">
      <style>
        *{
            margin: 0px;
            padding: 0px;
        }
        .container{
            width: 1000px;
            margin: 0 auto;
        }
        .container div{
            text-align: center;
            display: table;
        }
        .container div span{
            display: table-cell;
            vertical-align: middle;
        }
        .top{
            
            margin-bottom: 10px;
            outline: 1px solid #9F9F9F;
            width: 1000px;
            height: 80px;
            display: table;
            background-color: black;
        }
        .middle{
            margin-top: 20px;
            width: 1000px;
            height: 500px;
            position: relative;
        }
        .middle-left{
            outline: 1px solid #9F9F9F;
            position: absolute;
            top: 0px;
            width: 200px;
            height: 500px;
            background-color: black;
        }
        .middle-right{
            position: absolute;
            top: 0px;
            left: 220px;
            width: 800px;
            height: 500px;
        }
        .middle-right-1{
            outline: 1px solid #9F9F9F;
            width: 780px;
            height: 500px;
            background-color:white;
        }
        
        .bottom{
            margin-top: 20px;
            margin-bottom: 20px;
            outline: 1px solid #9F9F9F;
            width: 1000px;
            height: 100px;
            background-color: black;
            color: #fff;
        }
        
        .groupButton{
            color:black;
            font-size: large;
            top:0;
            height:50px;
            width:150px;
            margin-left:20px ;
            margin-top: 10px;
        
        }
        
        .profileButton{
            color:black;
            font-size: large;
            top:0;
            height:50px;
            width:150px;
            margin-left:20px ;
            margin-top: 10px;
        
        }
      </style>
    </head>
    <body>
    
    <div class="container">
      <!-- TOP -->
      <div class="top">
        <span style="color: white;">TOP (1000 x 80) <br/> #FF5E00;</span>
      </div>
    
      <!-- MIDDLE -->
      <div class="middle">
    
        <div class="middle-left"> 
            <button class="groupButton" onclick="location.href='group.html'"><b>공동문서작업</b></button>
            <button class="profileButton" onclick="location.href='profile.html'"><b>프로필</b></button>
        </div>
    
        <div class="middle-right">
    
          <div class="middle-right-1">
            <label> ${groupName[0]}</label>
          </div>
    
        </div>
    
      </div>
    
      <div class="bottom"> <span style="color: white;">BOTTOM (1000 x 100) <br/> #5D5D5D;</span> </div>
    
    </div>
    
    </body>
    </html>

    `;
    res.writeHead(200);
    res.end(template);

});


