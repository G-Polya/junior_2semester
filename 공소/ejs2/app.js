const express = require('express')
const app = express()
const db_config = require(__dirname+'/config/database.js')
const conn = db_config.init()
const bodyParser = require('body-parser')
var session=require('express-session')
var mySqlStore= require('express-mysql-session')(session)
let router = express.Router();

var template3 = require("./template3.js")

var url = require("url")

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
                req.session.isLogined=true
                req.session.save(function(){
                res.render('home.ejs', {course:rows})
            })
        }
    })
})



app.get('/:course/teamPage', function(req,res){
    let sql = `select mdl_groups.name,groupid, firstname, lastname
               from mdl_groups_members, mdl_user,mdl_groups
               where mdl_groups_members.userid = mdl_user.id and 
               mdl_groups_members.groupid=1 and 
               mdl_groups_members.groupid = mdl_groups.id`

    const names = []    
    //const lastNames = []
    conn.query(sql, function(err, rows, fields){
        if(err) console.log('query is not excuted. select fail...\n'+err)
        else {
            rows.forEach((element)=>{
                names.push(element.firstname+element.lastname)
            })
            console.log(rows[0].name)
  
            req.session.isLogined = true
            req.session.save(function(){
                res.render('teamPage.ejs', {memberName:names,groupName:rows[0].name,comment:comment})
            })
            
        }
    })
    //res.render('teamPage.ejs', {memberName:req.session.names, groupName:req.session.groupName,course:req.session.course})
})

app.get('/selected', function(req, res){
    let course = req.session.course
    function getFiles(course) {
        let files_ = []
        for(var i = 0; i < course.length;i++) {
            files_.push(`<option value=course${i}> ${course[i].shortname} </option>`)
        }
        
        files_ = files_.join("")
        return files_
    }

    let tt = getFiles(course)
    let html = template3.HTML(tt)
    res.writeHead(200)
    res.end(html)


    
})



app.get('/:course', function(req, res){
    //console.log(req.session.isLogined)
   // console.log(req.session.course)

    let _url = req.url;
    let queryData = url.parse(_url,true).query;
    if(Object.keys(queryData).length > 0){
        console.log(queryData.course)
    }


    res.render('course0.ejs',{course:req.session.course})
})


// app.get('/course1', function(req, res){
//     console.log(req.session.isLogined)
//     console.log(req.session.course)
//     res.render('course1.ejs',{course:req.session.course})
//     res.render('course1.ejs',{course:req.session.course})
// })

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