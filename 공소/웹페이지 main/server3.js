var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url=require('url');
var express=require('express');
var app=express();

app.set('port',process.env.PORT||8888);

app.post('/fileupload',function(req,res){
  var form = new formidable.IncomingForm(); //객체 할당
        //field값(필드 매개변수) 받는 부분
        form.parse(req, function(err, fields, files){
            var oldpath = files.filetoupload.path;
            var newpath = 'C:/xampp/htdocs/upload/' + files.filetoupload.name;
            fs.rename(oldpath, newpath, function(err){
                if(err) throw err;
                fs.readFile('./uploadedpage.html','UTF-8',
                    function(err,data){
                        res.writeHead(200, {'Content-Type':'text/html'});
                        res.write(data);
                        res.end();
                    }
                );
            });
        });
})

app.get('/fileupload',function(req,res){
  var form = new formidable.IncomingForm(); //객체 할당
  //field값(필드 매개변수) 받는 부분
  form.parse(req, function(err, fields, files){
      var oldpath = files.filetoupload.path;
      var newpath = 'C:/xampp/htdocs/upload/' + files.filetoupload.name;
      fs.rename(oldpath, newpath, function(err){
          if(err) throw err;
          fs.readFile('./uploadedpage.html','UTF-8',
              function(err,data){
                  res.writeHead(200, {'Content-Type':'text/html'});
                  res.write(data);
                  res.end();
              }
          );
      });
  });
});

app.get('/',function(req,res){
  var title = 'Welcome';  
  outputtemplate=function(lst){
    var template = `
    <!doctype html>
    <html>
    <head>
      <title>WEB1 - ${title}</title>
      <meta charset="utf-8">
    </head>
    <body>
      <h1><a href="/">WEB</a></h1>
      ${lst}
      <h2>${title}</h2>
      <form action="fileupload" method="post" enctype="multipart/form-data">
        <input type="file" name="filetoupload">
        <input type="submit">
        </form>
    </body>
    </html>
    `;
    res.writeHead(200);
    res.end(template);
  }

  fs.readdir('./upload', function(error, filelist){
    var list='<ul>';
    var i = 0;
    while(i < filelist.length){
      list = list + `<li><a href="download/${filelist[i]}">${filelist[i]}</li></a>`;
      i = i + 1;
    }
    list = list+'</ul>';
    outputtemplate(list);
  });
  
});

app.get('/download/:id',function(req,res){
  var filename=req.params.id;
    filepath="./upload/"+filename;
    res.download(filepath);
});

var server = http.createServer(app).listen(app.get('port'),function(){});
   

