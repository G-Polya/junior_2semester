const express = require('express')
var http = require("http");
var fs = require("fs");
var Inko = require('inko');
var inko = new Inko();
const qs = require("querystring");

const app = express()
const db_config = require(__dirname+'/config/database.js')
const conn = db_config.init()
const bodyParser = require('body-parser')
var session=require('express-session')
var mySqlStore= require('express-mysql-session')(session)
let router = express.Router();

var myRouter = require("./myrouter.js");
var template = require("./template.js");
var j = 0;

var url = require("url")
const { Console, group } = require('console')
const { RSA_NO_PADDING } = require('constants')
const { read } = require('fs');
const e = require('express');

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
app.use(express.static("public"));
app.use("/grouprepository", express.static("grouprepository"));

app.use("/myrouter", myRouter);

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended:false}))

app.get('/', function(req,res){
    let _url = req.url;
    let queryData = url.parse(_url,true).query;
    let loginId = queryData.id

    IdRepository = [];

    for (var j in db) {
      if (db[j].guid == loginId) {
        if (db[j].g_path) {
          IdRepository.push(db[j].g_path);
        } else {
          var newrpos = "./grouprepository/" + db[j].c_name + "_" + db[j].gid;
          fs.mkdir(newrpos, (err) => {
            conn.query(
              `Update mdl_groups set group_path = "${
                db[j].c_name + "_" + db[j].gid
              }"
                          where id=${db[j].gid};`
            );
            dbqueryinput();
          });
        }
      }
    }
  
    function getFiles(dir, files_) {
      files_ = files_ || [];
      var files = fs.readdirSync(dir);
      files_.push("<ul>");
      for (var i in files) {
        if (IdRepository.indexOf(files[i]) === -1) continue;
        else
          files_.push(
            `<a href="/${files[i]}?id=${loginId}" class="w3-bar-item w3-button w3-padding">-파일업로드</a>`
            // `<li><a href="/${files[i]}?id=${loginId}">${files[i]}</a></li>`
          );
      }
      files_.push("</ul>");
      files_ = files_.join("");
      return files_;
    }
    

    let sql = `select id, shortname
               from mdl_course as C
               where C.id in (select B.courseid
                              from mdl_groups as B
                              where B.id in (select A.groupid
                                             from mdl_groups_members as A
                                             where userid=${queryData.id}));`
    conn.query(sql, function(err, rows, fields){
        if(err) console.log('query is not excuted. select fail...\n'+err)
        else {
            req.session.userid = loginId
            req.session.course = rows
            req.session.isLogined=true
            var tt = getFiles("./grouprepository", 0);
            console.log(tt)
            req.session.tt = tt
            
            req.session.save(function(){
                res.render('home.ejs', {course:rows})
            })
        }
    })
})




app.get('/fileUpload', function(req, res){
    const userid = req.session.userid
    let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`
    const group_course = []
    conn.query(sql, function(err, rows, fields){
        if (err) console.log("query is not excuted. select fail...\n" + err);
        else{
            rows.forEach((element)=>{
                group_course.push({courseid : element.courseid, groupid : element.id})
            })

            let dbCourseId = req.session.course[req.session.courseId].id
            
            const courseIndex = group_course.findIndex(function(element){
                if(element.courseid === dbCourseId){
                    return true
                }
            })

            if(courseIndex === -1){
                res.redirect('/home')
            }else {
                let dbGroupid = group_course[courseIndex].groupid
                sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list,courseid
                       from mdl_groups_members, mdl_user,mdl_groups
                       where mdl_groups_members.userid = mdl_user.id and
                             mdl_groups_members.groupid=${dbGroupid} and           
                             mdl_groups_members.groupid = mdl_groups.id and
                             mdl_groups.courseid = ${dbCourseId};`
                


                conn.query(sql, function(err, rows, fields){
                    if (err) console.log("query is not excuted. select fail...\n" + err);
                    else{


                        let groupIndex = rows.findIndex((element)=> {
                            return element.groupid === dbGroupid
                        })

                        res.redirect(`/${rows[groupIndex].name}?id=${req.session.userid}`)
                    }
                })
            }
        }
    })

    
})


app.get('/teamPage', function(req, res){
    const user = "tollea1235"       // 임시로 tollea1235, 무들에서 로그인정보(로그인ID)를 받아올것
    const userid = req.session.userid
    console.log("userid : " + userid)
    let sql = `select courseid,id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid});`

    
    const group_course = []
    conn.query(sql, function(err, rows, fields) {
        if (err) console.log("query is not excuted. select fail...\n" + err);
        else{
            rows.forEach((element)=>{
                group_course.push({courseid : element.courseid, groupid : element.id})
            })
           
            let dbCourseId = req.session.course[req.session.courseId].id
            
            const courseIndex = group_course.findIndex(function(element){
                if(element.courseid === dbCourseId){
                    return true
                }
            })
            
            console.log(group_course)
            

            if(courseIndex == -1){
                res.redirect('/home')
            } else {
                let dbGroupid = group_course[courseIndex].groupid
                console.log("dbGroupid : "+dbGroupid)

                sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list,courseid
                    from mdl_groups_members, mdl_user,mdl_groups
                    where mdl_groups_members.userid = mdl_user.id and
                            mdl_groups_members.groupid=${dbGroupid} and           
                            mdl_groups_members.groupid = mdl_groups.id and
                            mdl_groups.courseid = ${dbCourseId};`

                const names = []
                let group_user=[]
                let to_do_list = []
                conn.query(sql, function(err, rows, fields){
                    if (err) console.log("query is not excuted. select fail...\n" + err);
                    else{
                        rows.forEach((element) => {
                            if(element.courseid === dbCourseId){
                                names.push(element.firstname + element.lastname);
                                to_do_list.push(element.to_do_list);
                                group_user.push(element.groupid + '_' + element.id);
                                
                            }
                        });
    
                        
                        req.session.names = names;
                        let groupIndex = rows.findIndex((element)=> {
                            return element.groupid === dbGroupid
                        })
                        
                        req.session.to_do_list = to_do_list;
                        req.session.group_user = group_user;
                        req.session.save(function(){
                            res.render('teamPage2.ejs', {memberName:names,groupName:rows[groupIndex].name,course:req.session.course})
                        })
    
                    }
                })

            }
            
        
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
    console.log(req.session.userid)
    res.redirect(`/home`)
})



app.get('/home', function(req, res){
    res.redirect(`/?id=${req.session.userid}`)
})



app.get('/profilePage', function(req, res){
    res.render('profilePage.ejs',{course:req.session.course})
})

let comment = "hello"

app.get('/workList', function(req, res){
    let dbCourseId = req.session.course[req.session.courseId].id
    const userid = req.session.userid
    console.log("userid: " + userid)
    let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`
    const group_course = []
    conn.query(sql, function(err, rows, fiels){
        if (err) console.log("query is not excuted. select fail...\n" + err);
        else{
            rows.forEach((element)=>{
                group_course.push({courseid : element.courseid, groupid : element.id})
            })
            const courseIndex = group_course.findIndex(function(element){
                if(element.courseid === dbCourseId){
                    return true
                }
            })

            

            let dbGroupid = group_course[courseIndex].groupid
            console.log("dbGroupid : "+dbGroupid)
            sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list,courseid
                   from mdl_groups_members, mdl_user,mdl_groups
                   where mdl_groups_members.userid = mdl_user.id and
                         mdl_groups_members.groupid=${dbGroupid} and           
                         mdl_groups_members.groupid = mdl_groups.id and
                         mdl_groups.courseid = ${dbCourseId};`

            const names = []
            let group_user=[]
            let to_do_list = []
            conn.query(sql, function(err, rows, fields){
                rows.forEach((element)=>{
                    if(element.courseid === dbCourseId){
                        names.push(element.firstname + element.lastname);
                        to_do_list.push(element.to_do_list);
                        group_user.push(element.groupid + '_' + element.id);
                    }
                })

                req.session.names = names
                let groupIndex = rows.findIndex((element)=>{
                    return element.groupid === dbGroupid
                })
    
                
                req.session.groupName = rows[groupIndex].name
                req.session.to_do_list = to_do_list
                req.session.group_user = group_user;
                req.session.save(function(){
                    res.render('workList2.ejs', {
                        memberName:names,
                        groupName:req.session.groupName.name, 
                        comment: req.session.to_do_list,
                        group_user: req.session.group_user,
                        course:req.session.course
                    })
                })
            })

           

        }
    })
})



app.get('/course?:id', function(req, res){
    

    let _url = req.url;
    let queryData = url.parse(_url,true).query;
    console.log(req.session.course)
    if(Object.keys(queryData).length > 0){
        req.session.courseId = queryData.id
        req.session.save(function(){
            res.render('course2.ejs',{course:req.session.course, courseId:queryData.id, userid:req.session.userid})
        })
    }
})


app.get("/:id", function (req, res) {
    var loginId = req.query.id;
    var group = req.params.id;
    group = "./grouprepository/" + group;
    
    IdRepository = [];
  
    for (var j in db) {
      if (db[j].guid == loginId) {
        if (db[j].g_path) {
          IdRepository.push(db[j].g_path);
        } else {
          var newrpos = "./grouprepository/" + db[j].c_name + "_" + db[j].gid;
          fs.mkdir(newrpos, (err) => {
            conn.query(
              `Update mdl_groups set group_path = "${
                db[j].c_name + "_" + db[j].gid
              }"
                          where id=${db[j].gid};`
            );
            dbqueryinput();
          });
        }
      }
    }
  
    function getFiles2(dir, files_) {
      files_ = files_ || [];
      var files = fs.readdirSync(dir);
      files_.push("<ul>");
      for (var i in files) {
        if (IdRepository.indexOf(files[i]) === -1) continue;
        else
          files_.push(
            `<li><a href="/${files[i]}?id=${loginId}">${files[i]}</a></li>`
          );
      }
      files_.push("</ul>");
      files_ = files_.join("");
      return files_;
    }
  
    function getFiles(dir, isPart, files_) {
      files_ = files_ || [];
      var files = fs.readdirSync(dir).map((filename) => {
        return {
          filename: filename,
          mtime: fs.statSync(dir + "/" + filename).mtime,
        };
      });
  
      if (isPart == 1) files.sort((a, b) => a.mtime - b.mtime);
      var idx = 0;
      for (var i in files) {
        var name = dir + "/" + files[i].filename;
        var forbid = "_content";
        if (name.indexOf(forbid) != -1) {
          continue;
        }
        j = j + 1;
        if (fs.statSync(name).isDirectory()) {
          let uname = name.replace(/\//g, ",");
          files_.push("<ul>");
          files_.push(`<div class="part"> 
                  <div class="parttitle">
                  <form action="myrouter/deletepart/${uname}?id=${loginId}" method="post">
                  <h2 class="titlefont" style=color:white;>
                  <input type="image" src="white.png" style="width:20px; height:auto; margin-left:5%;"alt="x">
                      ${files[i].filename}
                  </h2>
                  </form>
                  </div>
                  `);
          files_.push(`
                  <div class="partupload">
                  <form action="myrouter/fileupload/${uname}?id=${loginId}" method="post"  enctype="multipart/form-data">
                  <input type="file" name="filetoupload"  style="width:100%; font-size:30%; color:white">
                  <input type="submit" style="font-size:30%;">
                  </form>
                  </div>
                  `);
  
          getFiles(name, 1, files_);
  
          files_.push("</div>");
          if (i < files.length - 1) {
            files_.push(`
                      <div class="link">
                      <hr style="color:white; height:8px; border:none; background-color:white"  align="center">
                      </div>
                      `);
          }
          files_.push("</ul>");
        } else {
          var spliturl = name.split("/");
          var fname = spliturl[spliturl.length - 1];
          let uname = name.replace(/\//g, ",");
  
          var path = uname;
          var fpath = path.replace(/,/g, "/");
          var splitname = fpath.split(".");
          var ext = "." + splitname[splitname.length - 1];
          var ffpath = fpath.replace(ext, "_content.txt");
          var fbpath = inko.ko2en(ffpath);
          var finalpath = fbpath.replace("./grouprepository", "/grouprepository");
          files_.push(`
                  <div class="vertical2">
                  </div>`);
  
          files_.push(`
                      <div id = "listcontent${j}" class="listcontent" style="border:2px solid white; overflow: auto; height: 100px; background-color:black; position:relative;">
                      `);
          files_.push(`
                  <form action="myrouter/delete/${uname}?id=${loginId}" method="post" onsubmit="return confirm('정말 삭제하시겠습니까?');">
                  <div class="left">
                  <input type="image" src="white.png" style="width:15px; height:auto; margin-left:5%;"alt="x">
                  </div>
                  </form>
                  <a class="listfont" href="myrouter/download/${uname}?id=${loginId}"><b>&nbsp;&nbsp;${fname}</b></a>
                  <br>
                  <form class = "detail" action="myrouter/edit/${uname}">
                  <input type = "button" class = "detailBT" value = "detail" id = "dis${j}"><br>
                  <textarea name = "content" cols="35" rows="9" id = 'comment_area${j}' style="display:none" ></textarea><br>
                  <input type="submit" value="Edit" id = 'comment_edit${j}' style="display:none" >
                  </form>
  
                  </div>
                  <script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>
                  <script type="text/javascript">
                      $(document).on("click","#dis${j}", function(){
                          if($("#comment_area${j}").css('display') == 'none'){
                              $("#comment_area${j}").show();
                              $("#comment_edit${j}").show();
                              $("#listcontent${j}").css('width','200px');
                              $("#listcontent${j}").css('height','200px');
                              $("#listcontent${j}").css('z-index', '1000');
                              $("#comment_area${j}").load("${finalpath}",function(txt, status,xhr){
                                  if (status == "success") {
                                  } else if (status == "error") {
                                      
                                  }
                              });
                              }else{
                                  $("#listcontent${j}").css('width','125px');
                                  $("#listcontent${j}").css('height','100px');
                                  $("#listcontent${j}").css('z-index', 'initial');
                                  $("#comment_area${j}").hide();
                                  $("#comment_edit${j}").hide();
                              }
                      });
  
                   </script>
                  `);
        }
        idx++;
      }
  
      files_ = files_.join("");
      return files_;
    }
    
    console.log(req.session.course)
    function getCourse(course){

        options = [];
        // files_.push(`<select name="course" onchange="location=this.value;">`)
        //options.push(`<option value="select-course" > 강좌를 선택하세요 </option>`)
        for (var i=0; i < course.length; i ++){
            options.push(`<option value="course?id=${i}"> ${course[i].shortname} </option>`)
        }
        // files_.push("</select>")
        options = options.join("");
        return options;
    }

    console.log(getCourse(req.session.course))

    let ugroup = group.replace(/\//g, ",");
    var html = template.HTML(
      getCourse(req.session.course),
      getFiles(group, 0),
      getFiles2("./grouprepository", 0),
      ugroup + "?id=" + loginId
    );
    res.writeHead(200);
    res.end(html);
});
  
  var db = [];
  
var server = http.createServer(app).listen(app.get("port"), function () {
    dbqueryinput();
});
  
function dbqueryinput() {
    conn.query(
      `SELECT gm.id, gm.groupid, gm.userid, g.group_path, c.fullname
          from mdl_groups_members gm
          left outer join mdl_groups g on gm.groupid=g.id
          left outer join mdl_course c on g.courseid=c.id`,
      (error, rows) => {
        db = [];
        if (error) throw error;
        for (var i in rows) {
          db.push({
            gm: rows[i].id,
            gid: rows[i].groupid,
            guid: rows[i].userid,
            g_path: rows[i].group_path,
            c_name: rows[i].fullname,
          });
        }
      }
    );
  }
  



app.listen(3300, ()=>console.log('Sever is running on port 3300...'))