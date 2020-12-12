var formidable = require('formidable');
var fs = require('fs');
var express = require('express');
var Inko = require('inko');
var inko = new Inko();

var router = express.Router();
var maxfilesize = 50*1024*1024;
var fileTypes=['application/haansofthwp', 'application/pdf', 
'application/vnd.openxmlformats-officedocument.wordprocessingml.document',
'image/jpeg', 'image/png', 'image/gif',  
'application/vnd.openxmlformats-officedocument.presentationml.presentation',
'text/plain'
]

//파일 업로드
router.post('/fileupload/:id', function (req, res) {
    let path = req.params.id;
    let fpath = path.replace(/,/g, '/');
    var splitpath = fpath.split("/");
    var fname = splitpath[2];
    var form = new formidable.IncomingForm(); //객체 할당
    //field값(필드 매개변수) 받는 부분
    form.parse(req, function (err, fields, files) {

        if(files.filetoupload.name.split('.').length>2)
        {
            res.send(`<script type="text/javascript">
                alert("이름에 '.' 이 포함된 파일은 업로드 할 수 없습니다. ");
                history.back();
                </script>`);
            res.end();
            return;
        }

        if(fileTypes.indexOf(files.filetoupload.type)===-1){
            res.send(`<script type="text/javascript">
                alert("지원하지 않는 형식의 파일입니다.");
                history.back();
                </script>`);
            res.end();
            return;
        }

        if(files.filetoupload.size>maxfilesize)
        {
            res.send(`<script type="text/javascript">
                alert("파일의 최대크기를 넘습니다.");
                history.back();
                </script>`);
            res.end();
            return;
        }

        var filelist = fs.readdirSync(fpath);
        var p=1;
        var splitname = files.filetoupload.name.split(".");
        var sname = splitname[splitname.length - 2];
        var ext = splitname[splitname.length - 1];
        

        for(var i in filelist)
        {
            if(filelist[i]==files.filetoupload.name)
                p++;
            var tempname=sname+'_'+p+'.'+ext;
            if(filelist[i]==tempname)
                p++;
        }
            
        sname=sname+'_'+p+'.'+ext;
                
        var oldpath = files.filetoupload.path;
        var newpath;
        if(p>1)
            newpath = fpath + '/' + sname;
        else
            newpath = fpath + '/' + files.filetoupload.name;

        fs.rename(oldpath, newpath, function (err) {
            if (err){
                res.send(`<script type="text/javascript">
                alert("파일을 선택해 주세요");
                history.back();
                </script>`);
                res.end();
            }
            else{
                res.writeHead(302, { Location: '/'+fname +'?id='+req.query.id });
                res.end();
            }
            
        });
    });
})

//파트 추가
router.post('/addpart/:id',(req,res) => {
    var filename=req.params.id.replace(/,/g, '/');
    var part=req.body.part;
    let addpart='./'+filename+'/'+part;
    var splitpath = filename.split("/");
    var fname=splitpath[2];

    var partlist = fs.readdirSync(filename);
    if(partlist.length==6){
        res.send(`<script type="text/javascript">
            alert("최대 6개의 파트만 가능합니다");
            history.back();
            </script>`);
        res.end();
    }
    else{
        fs.mkdir(addpart,err=>{
            if(err && err.cod != 'EEXIST'){
                res.send(`<script type="text/javascript">
                alert("파트가 존재하거나 입력되지 않았습니다");
                history.back();
                </script>`);
                res.end();
            }
            else{
                res.writeHead(302, { Location: '/'+fname+'?id='+req.query.id });
                res.end();
            }
            
        })
    }  
});

//파트 제거 (빈 파트만 가능)
router.post('/deletepart/:id', function (req, res) {
    let path = req.params.id;
    let fpath = path.replace(/,/g, '/');
    var splitpath = fpath.split("/");
    var fname = splitpath[2];

    fs.rmdir(fpath,err=>{
        if(err && err.cod != 'EEXIST') {
            res.send(`<script type="text/javascript">
            alert("파일이 있어 파트삭제 불가능");
            history.back();
            </script>`);
            res.end();
        }
        else{
            res.writeHead(302, { Location: '/'+fname +'?id='+req.query.id });
            res.end();
        }
       
    })
});

//파일 다운로드
router.get('/download/:id', function (req, res) {
    let filename = req.params.id.toString();
    let rfilename = filename.replace(/,/g, '/');
    res.download(rfilename);
});

//파일 삭제
router.post('/delete/:id', function (req, res) {
    let path = req.params.id;
    let fpath = path.replace(/,/g, '/');
    var splitpath = fpath.split("/");
    var fname = splitpath[2];

    var splitname = fpath.split(".");
    var sname = splitname[splitname.length - 2];
    var ext = "." + splitname[splitname.length - 1];
    let fbpath = fpath.replace(ext ,'_content.txt');
    let ffpath = inko.ko2en(fbpath);

    fs.unlink(fpath, function (err) {
        if (err) throw err;
        fs.stat(ffpath, function(err) {
            if (!err) {
                fs.unlink(ffpath, function (err){
                    if(err) throw err;
                });
            }
            else if (err.code === 'ENOENT') {
                console.log('file or directory does not exist');
            }
        });
        res.writeHead(302, { Location: '/' + fname + '?id=' + req.query.id });
        res.end();

    });

});

//comment 추가
router.get('/edit/:id', function (req, res) {
    var text = req.query.content;
    let path = req.params.id;
    let fpath = path.replace(/,/g, '/');

    var splitpath = fpath.split("/");
    var fname = splitpath[2];

    var splitname = fpath.split(".");
    var sname = splitname[splitname.length - 2];
    var ext = "." + splitname[splitname.length - 1];
    let fbpath = fpath.replace(ext ,'_content.txt');
    let ffpath = inko.ko2en(fbpath);
    console.log(ffpath)
    fs.writeFile(ffpath, text, (err) =>{
        if(err){
            console.log(err);
            res.status(500).send('Internal Server Error');
        }
        console.log('comment uploaded');
        res.writeHead(302, { Location: '/'+fname +'?id='+req.query.id });
        res.end();
    });
});

module.exports = router;