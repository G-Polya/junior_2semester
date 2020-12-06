const express = require('express')
const app = express()
const db_config = require(__dirname+'/config/database.js')
const conn = db_config.init()
const bodyParser = require('body-parser')
var session=require('express-session')
var mySqlStore= require('express-mysql-session')(session)
let router = express.Router();

var template3 = require("./template3.js")
var template4 = require("./template4.js")

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



app.get('/course?:id/teamPage', function(req,res){
    res.render('teamPage.ejs', {memberName:req.session.names, groupName:req.session.groupName,course:req.session.course})
})

app.get('/main', function(req, res){
    console.log(req.session.course)
    res.render('main.ejs', {course:req.session.course})
})

app.get('/home', function(req, res){
    console.log(req.session.course)
    res.render('home.ejs', {course:req.session.course})
})

// app.get('/home', function(req, res){
    
//     course = req.session.course
    // function getFiles(course) {
    //     let files_ = []
    //     for(var i = 0; i < course.length;i++) {
    //         files_.push(`<option value=course${i}> ${course[i].shortname} </option>`)
    //     }
        
    //     files_ = files_.join("")
    //     return files_
    // }

    // let tt = getFiles(course)
    // let html = template3.HTML(tt)
    // res.writeHead(200)
    // res.end(html)


// })



app.get('/profilePage', function(req, res){
    res.render('profilePage.ejs',{course:req.session.course})
})

let comment = "hello"
app.get('/workList', function(req, res){
    res.render('workList.ejs', {memberName:req.session.names, groupName:req.session.groupName,comment:comment,course:req.session.course})      
})

app.get('/main/', function(req,res){
    console.log("test")
})

app.get(`/`)

app.get('/course?:id', function(req, res){
    //console.log(req.session.isLogined)
    //console.log(req.session.course)


    let _url = req.url;
    let queryData = url.parse(_url,true).query;
    //console.log(queryData)
    if(Object.keys(queryData).length > 0){
        console.log(queryData.id)
        let myCourse = req.session.course[queryData.id]
        res.render('course.ejs',{course:req.session.course, myCourse:myCourse})
    }


    
})


// app.get(`/course${i}`, function(req, res){
//     let _url = req.url
//     let course = req.session.course
    
//     function getTitle(course) {
//         let files_ = []
//         files_.push(`<h1> ${course[i].shortname} <h1>`)
        
        
//         files_ = files_.join("")
//         return files_
//     }

//     let tt = getTitle(course)
    
    
//     function getSelect(course) {
//         let files_ = []
//         for(var j = 0; j < course.length;j++) {
//             files_.push(`<option value=course${j}> ${course[j].shortname} </option>`)
//         }
        
//         files_ = files_.join("")
//         return files_
//     }
//     let ts = getSelect(course)
//     let html = template4.HTML(tt,ts)
//     res.writeHead(200)
//     res.end(html)
// })




// for(var i = 0; i< 5; i++){
//     app.get(`/course${i}`, function(req, res){
//         let _url = req.url
        
    
    
//         console.log(req.session.isLogined)
//         console.log(req.session.course)
//         res.render('course.ejs',{course:req.session.course})
//     })
// }

app.listen(3300, ()=>console.log('Sever is running on port 3300...'))