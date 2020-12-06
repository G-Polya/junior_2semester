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
const { Console } = require('console')
const { RSA_NO_PADDING } = require('constants')

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

// app.get('/teamPage', function(req,res){
//     console.log(req.session.course[req.session.courseId])
//     let dbCourseId = req.session.course[req.session.courseId].id
//     let sql = `select mdl_groups.name,groupid, firstname, lastname
//                from mdl_groups_members, mdl_user,mdl_groups
//                where mdl_groups_members.userid = mdl_user.id and
//                      mdl_groups_members.groupid=1 and
//                      mdl_groups_members.groupid = mdl_groups.id and
//                      mdl_groups.courseid=${dbCourseId};`

//     const names = []    
//     //const lastNames = []
//     conn.query(sql, function(err, rows, fields){
//         if(err) console.log('query is not excuted. select fail...\n'+err)
//         else {
//             rows.forEach((element)=>{
//                 names.push(element.firstname+element.lastname)
//             })
//             console.log(rows[0].name)
  
//             req.session.isLogined = true
//             req.session.save(function(){
//                 res.render('teamPage.ejs', {memberName:names,groupName:rows[0].name,course:req.session.course})
//             })
            
//         }
//     })
// })

app.get('/teamPage', function(req, res){
    let dbCourseId = req.session.course[req.session.courseId].id
    
    
    console.log(dbCourseId)
    let sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list
               from mdl_groups_members, mdl_user,mdl_groups
               where mdl_groups_members.userid = mdl_user.id and
                        mdl_groups_members.groupid=1 and           
                        mdl_groups_members.groupid = mdl_groups.id and
                        mdl_groups.courseid = ${dbCourseId};`


    // course 2
    // let sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list
    //            from mdl_groups_members, mdl_user,mdl_groups
    //            where mdl_groups_members.userid = mdl_user.id and
    //                     mdl_groups_members.groupid=3 and           
    //                     mdl_groups_members.groupid = mdl_groups.id and
    //                     mdl_groups.courseid = ${dbCourseId};`
    const names = []
    let group_user=[]
    let to_do_list = []
    conn.query(sql, function(err, rows, fields){
        if (err) console.log("query is not excuted. select fail...\n" + err);
        else{
            rows.forEach((element) => {
                names.push(element.firstname + element.lastname);
                to_do_list.push(element.to_do_list);
                group_user.push(element.groupid + '_' + element.id);
            });

            console.log(rows)
            console.log(to_do_list)
            req.session.names = names;
            req.session.groupName = rows[req.session.courseId].name;
            req.session.to_do_list = to_do_list;
            req.session.group_user = group_user;
            req.session.save(function(){
                res.render('teamPage.ejs', {memberName:names,groupName:rows[req.session.courseId].name,course:req.session.course})
            })

        }
    })
})

app.post("/store/:id", function (req, res) {
    var group = req.params.id.split("_")[0];
    var user = req.params.id.split("_")[1];
    conn.query(
      `Update mdl_groups_members set to_do_list = "${req.body.memo}"
      where groupid=${group} and userid=${user}`,
    );
    res.writeHead(302, { Location: '/workList' });
    res.end();
  });
  

app.get('/main', function(req, res){
    res.redirect('/')
})



app.get('/home', function(req, res){
    res.redirect('/')
})



app.get('/profilePage', function(req, res){
    res.render('profilePage.ejs',{course:req.session.course})
})

let comment = "hello"

app.get('/workList', function(req, res){
    let dbCourseId = req.session.course[req.session.courseId].id
    console.log("req.session.courseId: "+req.session.courseId)
    console.log(dbCourseId)
    let sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list
               from mdl_groups_members, mdl_user,mdl_groups
               where mdl_groups_members.userid = mdl_user.id and
                        mdl_groups_members.groupid=1 and
                        mdl_groups_members.groupid = mdl_groups.id and
                        mdl_groups.courseid = ${dbCourseId};`

     // course 2
    // let sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list
    //            from mdl_groups_members, mdl_user,mdl_groups
    //            where mdl_groups_members.userid = mdl_user.id and
    //                     mdl_groups_members.groupid=3 and           
    //                     mdl_groups_members.groupid = mdl_groups.id and
    //                     mdl_groups.courseid = ${dbCourseId};`
    const names = []
    let group_user=[]
    let to_do_list = []
    conn.query(sql, function(err,rows, fields){
        rows.forEach((element) => {
            names.push(element.firstname + element.lastname);
            to_do_list.push(element.to_do_list);
            group_user.push(element.groupid + '_' + element.id);
        });
        req.session.names = names;
        req.session.groupName = rows[req.session.courseId].name;
        req.session.to_do_list = to_do_list;
        req.session.group_user = group_user;

        req.session.save(function(){
            res.render("workList.ejs", {
                memberName: req.session.names,
                groupName: req.session.groupName,
                comment: req.session.to_do_list,
                group_user: req.session.group_user,course:req.session.course
            })
        })


    })
})



app.get('/course?:id', function(req, res){
    //console.log(req.session.isLogined)
    //console.log(req.session.course)
    

    let _url = req.url;
    let queryData = url.parse(_url,true).query;
    console.log(req.session.course)
    if(Object.keys(queryData).length > 0){
        console.log(queryData.id)
        console.log(req.session.course[queryData.id].id)
        req.session.courseId = queryData.id
        req.session.save(function(){
            res.render('course.ejs',{course:req.session.course, courseId:queryData.id})
        })
    }


    
})





app.listen(3300, ()=>console.log('Sever is running on port 3300...'))