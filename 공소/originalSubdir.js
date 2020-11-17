var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url = require('url');
var express = require('express');
var app = express();
const bodyParser = require('body-parser')
const mysql      = require('mysql');
const dbconfig   = require('./express-mysql-example/config/database.js');
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

app.get('/', function (req, res) {
    //res.send(db);

    function getFiles(dir, files_) {
        files_ = files_ || [];
        var files = fs.readdirSync(dir);
        
        //var p = 1;
        for (var i in files) {
            var name = dir + '/' + files[i];
            if (fs.statSync(name).isDirectory()) {
                let uname = name.replace(/\//g, ',');
                files_.push('<ul>')
                files_.push(`<div style="border:1px solid orange; width:13%;"> 
                <form action="deletepart/${uname}" method="post">
                <h2 class="titlefont">
                    <input type="submit" value="x">
                    ${files[i]}
                </h2>
                </form>
                `);
                files_.push(`
                <div class="origin" style="border:1px solid orange">
                <form action="fileupload/${uname}" method="post"  enctype="multipart/form-data">
                <input type="file" name="filetoupload" style="width:73%;">
                <input type="submit">
                </form>
                </div>
                `)
                getFiles(name, files_);

               
                files_.push('</div>');
                files_.push(`
                <div class="link">
                <hr color="orange" size="8" align="center">
                </div>
                `)
                  files_.push('</ul>')
            } else {
                var spliturl = name.split("/");
                var fname = spliturl[spliturl.length - 1];
                let downloadUrl = spliturl.slice(spliturl.indexOf("upload") + 1).join(",");
                let uname = name.replace(/\//g, ',');
                files_.push(`
                <div class="vertical">
                <p></p>
                </div>
                <div class="origin" style="border:1px solid orange; width:100%;">
                <form action="delete/${uname}" method="post">
                <input type="submit" value="x" >
                <a href="/download/${downloadUrl}" class=listfont>${fname}</a>
                </form>
                </div>
                `)
            }
        }

      
        files_ = files_.join('');
        return files_;
    }

    var title = 'Welcome';
    var template = `
    <!doctype html> 
    <head>
    
    <meta charset="UTF-8">
    <title></title>
    <style>
        div{float:left;}
        .link{
            float:left;
            position: relative;
            bottom:-15px;
            width:3%;
        }
        .titlefont{
            font-size:90%;
        }
        .listfont{
            font-size:70%;
        }
        .check{
            left: 1px;
        }
        .origin{
            clear:both;
        }
        .right{
            float:right;
        }
        .vertical{
           background-color:yellow; 
           width: 6%;
           position: relative;
           left: 47%;
        }
        .horizontal{
            float:left;c
            background-color:orange;
            widht:100%;
            height:100%;
        }
    </style>
    </head>
    <body>
    ${getFiles('./upload')}
    <div class=origin>
        <form action="addpart/" method="post">
        <input type="text" name="part">
        <input type="submit" value="파트추가">
        </form>
    </div>
    
    <div class=origin>
        ${db}
    </div>
    </body>
    </html>
    `;
    res.writeHead(200);
    res.end(template);

});

var db=[];

var server = http.createServer(app).listen(app.get('port'), function () {
    connection.query('SELECT firstname from mdl_user', (error, rows) => {
        if (error) throw error;
        for (var i in rows){
            db.push(rows[i].firstname);
        }
      });
 });


