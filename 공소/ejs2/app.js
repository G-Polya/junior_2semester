const express = require('express')
const app = express()
const db_config = require(__dirname+'/config/database.js')
const conn = db_config.init()
const bodyParser = require('body-parser')
var session=require('express-session')
var mySqlStore= require('express-mysql-session')(session)
let router = express.Router();

var options = {
    host : 'localhost',
    port:3306,
    user:'root',
    password:'',
    database:'moodle'
}

var sessionStore = new mySqlStore(options)

app.use(session({
    secret : "kim",
    resave:false,
    saveUninitialized : true,
    store : sessionStore
}))



db_config.connect(conn);

app.set('views', __dirname+'/views')
app.set('view engine', 'ejs')

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended:false}))

app.get('/', function(req,res){
    let sql = `select id, shortname 
               from mdl_course
               where sortorder != 1;`
    conn.query(sql, function(err, rows, fields){
        if(err) console.log('query is not excuted. select fail...\n'+err)
        else {
            req.session.course = rows
            req.session.save(function(){
                res.render('home.ejs', {course:rows})
            })
        }
    })
})



app.get('/teamPage', function(req,res){
    res.render('teamPage.ejs', {memberName:req.session.names, groupName:req.session.groupName,course:req.session.course})
})

app.get('/selectedCourse', function(req, res){
    console.log(req.session.isLogined)
    res.render('selectedCourse.ejs',{course:req.session.course})
})


app.get('/home', function(req, res){
    
    res.render('home.ejs', {course:req.session.course})
})



app.get('/profilePage', function(req, res){
    res.render('profilePage.ejs')
})

let comment = "hello"
app.get('/workList', function(req, res){
    res.render('workList.ejs', {memberName:req.session.names, groupName:req.session.groupName,comment:comment,course:req.session.course})      
})

app.listen(3300, ()=>console.log('Sever is running on port 3300...'))