
var express = require('express');
var app = express();
var db_config = require(__dirname + '/config/database.js');
var conn = db_config.init();
var bodyParser = require('body-parser');
var url = require("url")

db_config.connect(conn);

app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended : false}));



app.get('/', function (req, res) {
    const body = req.body
    const inputId = body.id
    console.log(body)

    res.send("root")
    //res.render('login.ejs');
});

app.get('/list', function (req, res) {
    var sql = 'SELECT * FROM BOARD';    
    conn.query(sql, function (err, rows, fields) { 
        if(err) console.log('query is not excuted. select fail...\n' + err);
        else res.render('list.ejs', {list : rows});
    });
});
app.get('/registerPage', function (req, res) {
    let duplicateMsg=""
    res.render('register.ejs',{duplicateMsg:""})
});


app.post('/gotoRegister', function(req,res){
    res.redirect("/registerPage");
})

const idCheck = (id, people) => {
    for(var i = 0; i<people.length; i++){
        if(id == people[i].Id){
            return false;
        }
        else {
            return true;
        }
    }
}



app.get('/duplicateFunc', function(req, res){

    const userInfo = []

    const already = function(userInfo, inputId) {
        for(var i = 0 ;i < userInfo.length; i++){
            if(userInfo[i].userid === inputId){
                return true;
            }
            else{
                return false;
            }
        }
    }
    let duplicateMsg =""

    let sql = "SELECT userid, userPw from account";
    // const body = req.body
    // const inputId = body.id
    // console.log(inputId)
    let _url = req.url
    const queryData = url.parse(_url, true).query
    let inputId = queryData.id
    let inputPw = queryData.pw


    conn.query(sql, function(err, rows, fields){
        if(err) throw err
        for(var i = 0; i < rows.length; i++){   
             userInfo.push( {userid:rows[i].userid, userPw: rows[i].userPw})
        }
    
       // console.log(userInfo)

      
        const flag = already(userInfo, inputId)
        
        //res.render('register.ejs', {duplicateMsg:" "})

        if(inputId === "") {
            res.render('register.ejs', {duplicateMsg:""})
        } else {
            if(flag){
                res.render('register.ejs', {duplicateMsg:"중복되는 ID입니다."})
            } else {
                res.render('register.ejs', {duplicateMsg:"사용해도 좋은 ID입니다"})
            }  
        }
        
            
    })

})

// app.get('/login', function (req, res) {
//     console.log(req.body)
 
// });



app.get('/next', function(req,res){
    res.render("next.ejs")
})

app.get('/login', function(req,res) {
    let loginMsg="hello"
    res.render('login.ejs', {loginMsg:loginMsg});
})

app.get('/loginFunc', function (req, res) {
  let _url = req.url
  const queryData = url.parse(_url, true).query
  let inputId = queryData.id
  let inputPw = queryData.pw

  const userInfo = []

  const authenticate = function(userInfo, inputId, inputPw) {
    for(var i = 0 ;i < userInfo.length; i++){
        if(userInfo[i].userid === inputId && userInfo[i].userPw === inputPw){
            return true;
        }
        else{
            return false;
        }
    }
  }

  const sql = "SELECT userid, userPw from account";
  conn.query(sql, function(err, rows, fields){
    if(err) throw err
    else{
        for(var i = 0; i < rows.length; i++){   
            userInfo.push( {userid:rows[i].userid, userPw: rows[i].userPw})
        }

        const flag = authenticate(userInfo, inputId, inputPw)

        if(inputId === "") {
            res.render('login.ejs', {loginMsg:""})
        } else {
            if(flag){
                res.render('login.ejs', {loginMsg:"로그인성공"})
            } else {
                res.render('login.ejs', {loginMsg:"등록되지 않은 ID 또는 PW입니다"})
            }  
        }

    }
    
  })

});

app.listen(3100, () => console.log('Server is running on port 3100...'));