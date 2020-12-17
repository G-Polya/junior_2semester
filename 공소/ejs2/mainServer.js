const express = require("express");
var http = require("http");
var fs = require("fs");
var Inko = require("inko");
var inko = new Inko();
const qs = require("querystring");
const mysql2 = require("sync-mysql");
const app = express();
const db_config = require(__dirname + "/config/database.js");
const conn = db_config.init();
const bodyParser = require("body-parser");
var session = require("express-session");
var mySqlStore = require("express-mysql-session")(session);
let router = express.Router();

var myRouter = require("./myrouter.js");
var template = require("./template.js");
var j = 0;

var url = require("url");
const { Console, group } = require("console");
const {
  RSA_NO_PADDING,
  SSL_OP_SSLEAY_080_CLIENT_DH_BUG,
} = require("constants");
const { read } = require("fs");
const e = require("express");

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

var options = {
  host: "localhost",
  port: 3306,
  user: "root",
  password: "",
  database: "moodle",
};

const conn2 = new mysql2({
  host: "localhost",
  user: "root",
  password: "",
  database: "moodle",
});

var sessionStore = new mySqlStore(options);

app.use(
  session({
    secret: "kim",
    resave: false,
    saveUninitialized: true,
    store: sessionStore,
  })
);

app.set("port", process.env.PORT || 3300);

db_config.connect(conn);

app.set("views", __dirname + "/views");
app.set("view engine", "ejs");
app.use(express.static("public"));
app.use("/grouprepository", express.static("grouprepository"));

app.use("/myrouter", myRouter);

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

app.get("/rate", (req, res) => {
  let dbGroupid;
  let userids = [];
  let dbCourseId = req.session.course[req.session.courseId].id;
  const userid = req.session.userid;
  console.log("userid: " + userid);
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fiels) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });
      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      dbGroupid = group_course[courseIndex].groupid;
      console.log("평가groupid: " + dbGroupid);

      var result5 = conn2.query(
        `SELECT hasrated FROM mdl_groups_members WHERE groupid = ${dbGroupid} AND userid =${req.session.userid}`
      );

      if (result5[0].hasrated === 1) {
        res.send(
          '<script>alert("이미 평가하셨습니다.");location.href="/home";</script>'
        );
      } else {
        //let groupid = session.groupid;
        let index = 0;
        let names = [];
        //let userids = []; 그룹의 유저아이디들을 저장하는 배열을 전역변수선언해놨음.
        userids.length = 0;

        result = conn2.query(
          `SELECT userid FROM mdl_groups_members WHERE groupid = ${dbGroupid}`
        );

        for (var i = 0; i < result.length; i++) {
          userids.push(result[i].userid);
          console.log(result[i].userid);
          var result13 = conn2.query(
            `SELECT firstname, lastname FROM mdl_user WHERE id=${result[i].userid}`
          );
          names.push(result13[0].firstname + " " + result13[0].lastname);
        }
        index = userids.length;
        res.render("rateTemplate", { name: names, length: index,course:req.session.course, username:req.session.username, coursename:req.session.coursename });
      }
    }
  });
});

app.post("/insertRate", (req, res) => {
  let dbGroupid;
  let dbCourseId = req.session.course[req.session.courseId].id;
  const userid = req.session.userid;
  console.log("userid: " + userid);
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fiels) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });
      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      dbGroupid = group_course[courseIndex].groupid;
      console.log("평가삽입groupid: " + dbGroupid);
      let userids = [];
      var result22 = conn2.query(
        `SELECT userid FROM mdl_groups_members WHERE groupid = ${dbGroupid}`
      );

      for (var i = 0; i < result22.length; i++) {
        userids.push(result22[i].userid);
      }

      var leadership_s = req.body.leadership;
      var assertiveness_s = req.body.assertiveness;
      var teamwork_s = req.body.teamwork;
      var creativeness_s = req.body.creativeness;
      var orator_s = req.body.orator;
      var courseid = req.session.course[req.session.courseId].id;

      var leadership = [];
      var assertiveness = [];
      var teamwork = [];
      var creativeness = [];
      var orator = [];

      for (var i = 0; i < userids.length; i++) {
        leadership[i] = parseFloat(leadership_s[i]);
        assertiveness[i] = parseFloat(assertiveness_s[i]);
        teamwork[i] = parseFloat(teamwork_s[i]);
        creativeness[i] = parseFloat(creativeness_s[i]);
        orator[i] = parseFloat(orator_s[i]);
      }

      //이미 있나 확인
      var result = conn2.query(
        `SELECT * FROM a_rate WHERE userid = ${userids[0]} AND groupid=${dbGroupid}`
      );
      console.log("포문시작전");
      console.log(userids.length);
      console.log(userids[0]);
      console.log(userids[1]);
      console.log(result[0]);

      if (result[0] === undefined) {
        for (var i = 0; i < userids.length; i++) {
          console.log("첫번째 for문");
          console.log(userids[i]);
          console.log(userids.length);
          result1 = conn2.query(
            `INSERT INTO a_rate (userid, courseid, leadership, teamwork, creativeness, assertiveness, orator, groupid) VALUES (?,?,?,?,?,?,?,?)`,
            [
              userids[i],
              courseid,
              leadership[i],
              teamwork[i],
              creativeness[i],
              assertiveness[i],
              orator[i],
              dbGroupid,
            ]
          );
        }
      } else {
        for (var k = 0; k < userids.length; k++) {
          console.log("두번째 for문");
          console.log(userids[k]);
          console.log(userids.length);
          var result2 = conn2.query(
            `select * from a_rate where userid = ${userids[k]} AND groupid = ${dbGroupid}`
          );
          console.log("result2[0].leadership" + result2[0].leadership);
          leadership[k] += result2[0].leadership;
          assertiveness[k] += result2[0].assertiveness;
          teamwork[k] += result2[0].teamwork;
          creativeness[k] += result2[0].creativeness;
          orator[k] += result2[0].orator;
        }

        for (var i = 0; i < userids.length; i++) {
          console.log("세번째 for문");
          console.log(userids[i]);
          console.log(userids.length);
          console.log(courseid);
          conn2.query(
            `UPDATE a_rate SET leadership = ${leadership[i]}, teamwork = ${teamwork[i]}, creativeness = ${creativeness[i]}, assertiveness = ${assertiveness[i]}, orator = ${orator[i]} WHERE userid = ${userids[i]} and courseid = ${courseid}`
          );
        }
      }

      conn2.query(
        `UPDATE mdl_groups_members SET hasrated = 1 WHERE groupid = ${dbGroupid} AND userid = ${req.session.userid}`
      );
      res.redirect("/dividescore");
    }
  });
});

app.get("/dividescore", (req, res) => {
  let dbGroupid;
  let dbCourseId = req.session.course[req.session.courseId].id;
  const userid = req.session.userid;
  console.log("userid: " + userid);
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fiels) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });
      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      dbGroupid = group_course[courseIndex].groupid;
      console.log("평가삽입groupid: " + dbGroupid);
      let userids = [];
      var result22 = conn2.query(
        `SELECT userid FROM mdl_groups_members WHERE groupid = ${dbGroupid}`
      );

      for (var i = 0; i < result22.length; i++) {
        userids.push(result22[i].userid);
      }

      sql2 = `SELECT * FROM a_rate WHERE groupid = ${dbGroupid}`;
      conn.query(sql2, function (error, rows, result) {
        if (error) throw error;
        else {
          rows.forEach((element) => {
            var result8 = conn2.query(
              `SELECT groupid FROM mdl_groups_members WHERE userid = ${element.userid}`
            );

            var result9 = conn2.query(
              `SELECT COUNT(*) AS mc FROM mdl_groups_members WHERE groupid = ${result8[0].groupid}`
            );

            var result10 = conn2.query(
              `SELECT COUNT(*) AS didall FROM mdl_groups_members WHERE groupid = ${result8[0].groupid} AND HASRATED = 1`
            );
            console.log(result10[0].didall);
            if (result10[0].didall === result9[0].mc) {
              var leadership = element.leadership / result9[0].mc;
              var assertiveness = element.assertiveness / result9[0].mc;
              var teamwork = element.teamwork / result9[0].mc;
              var creativeness = element.creativeness / result9[0].mc;
              var orator = element.orator / result9[0].mc;
            } else {
              var leadership = element.leadership;
              var assertiveness = element.assertiveness;
              var teamwork = element.teamwork;
              var creativeness = element.creativeness;
              var orator = element.orator;
            }
            conn2.query(
              `UPDATE a_rate SET leadership = ${leadership}, teamwork = ${teamwork}, creativeness = ${creativeness}, assertiveness = ${assertiveness}, orator = ${orator} WHERE userid = ${element.userid}`
            );
          });
        }
      });
      res.redirect("/notfinished");
    }
  });
});

app.get("/notfinished", (req, res) => {
  let dbGroupid;
  let dbCourseId = req.session.course[req.session.courseId].id;
  const userid = req.session.userid;
  console.log("userid: " + userid);
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fiels) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });
      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      dbGroupid = group_course[courseIndex].groupid;
      console.log("평가삽입groupid: " + dbGroupid);

      var result23 = conn2.query(
        `SELECT id FROM mdl_groups WHERE courseid = ${dbCourseId}`
      );

      let gnum = 0;
      console.log(result23.length);

      for (var k = 0; k < result23.length; k++) {
        var result9 = conn2.query(
          `SELECT COUNT(*) AS mc FROM mdl_groups_members WHERE groupid = ${result23[k].id} and HASRATED IS NULL  `
        );
        console.log(result23[k].id);
        console.log(result9[0].mc);
        gnum += result9[0].mc;
      }

      if (gnum === 1) {
        res.redirect("/scoreboard");
      } else {
        res.send(
          '<script>alert("아직 평가가 진행중입니다.");location.href="/home";</script>'
        );
      }
    }
  });
});

app.get("/scoreboard", (req, res) => {
  //mdl_roleassingment에 roleid가 role을 결정
  let dbGroupid;
  let dbCourseId = req.session.course[req.session.courseId].id;
  const userid = req.session.userid;
  console.log("userid: " + userid);
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fiels) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });
      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      dbGroupid = group_course[courseIndex].groupid;
      console.log("평가삽입groupid: " + dbGroupid);

      let userids = [];
      var result22 = conn2.query(
        `SELECT userid FROM mdl_groups_members WHERE groupid = ${dbGroupid}`
      );

      for (var i = 0; i < result22.length; i++) {
        userids.push(result22[i].userid);
      }

      var sql2 = "SELECT * FROM a_rate where courseid = ?";

      conn.query(
        sql2,
        [req.session.course[req.session.courseId].id],
        function (error, rows, result) {
          let length = rows.length;
          if (error) throw error;
          else {
            let leadership_sb = [];
            let teamwork_sb = [];
            let creativeness_sb = [];
            let assertiveness_sb = [];
            let orator_sb = [];
            let userids_sb = [];
            let names_sb = [];
            let keys = [];

            for (var i = 0; i < length; i++) {
              userids_sb[i] = rows[i].userid;
              leadership_sb[i] = rows[i].leadership;
              teamwork_sb[i] = rows[i].teamwork;
              creativeness_sb[i] = rows[i].creativeness;
              assertiveness_sb[i] = rows[i].assertiveness;
              orator_sb[i] = rows[i].orator;
              keys[i] =
                leadership_sb[i] +
                teamwork_sb[i] +
                creativeness_sb[i] +
                assertiveness_sb[i] +
                orator_sb[i];
            }
            var result;
            for (var j = 0; j < length; j++) {
              result = conn2.query(
                "select firstname, lastname from mdl_user where id = ?",
                [userids_sb[j]]
              );
              names_sb[j] = result[0].firstname + " " + result[0].lastname;
            }

            for (var i = 0; i < length - 1; i++) {
              for (var j = 0; j < length - 1 - i; j++) {
                if (keys[j] < keys[j + 1]) {
                  var names_t,
                    leadership_t,
                    teamwork_t,
                    creativeness_t,
                    assertiveness_t,
                    orator_t;

                  names_t = names_sb[j + 1];
                  leadership_t = leadership_sb[j + 1];
                  teamwork_t = teamwork_sb[j + 1];
                  creativeness_t = creativeness_sb[j + 1];
                  assertiveness_t = assertiveness_sb[j + 1];
                  orator_t = orator_sb[j + 1];

                  names_sb[j + 1] = names_sb[j];
                  leadership_sb[j + 1] = leadership_sb[j];
                  teamwork_sb[j + 1] = teamwork_sb[j];
                  creativeness_sb[j + 1] = creativeness_sb[j];
                  assertiveness_sb[j + 1] = assertiveness_sb[j];
                  orator_sb[j + 1] = orator_sb[j];

                  names_sb[j] = names_t;
                  leadership_sb[j] = leadership_t;
                  teamwork_sb[j] = teamwork_t;
                  creativeness_sb[j] = creativeness_t;
                  assertiveness_sb[j] = assertiveness_t;
                  orator_sb[j] = orator_t;
                }
              }
            }

            var result12 = conn2.query(
              `SELECT fullname FROM mdl_course WHERE id = ${
                req.session.course[req.session.courseId].id
              }`
            );
            var coursename = result12[0].fullname;

            var result13 = conn2.query(
              `SELECT idnumber FROM mdl_groups WHERE id = ${dbGroupid}`
            );

            console.log(result13[0].idnumber);

            res.render("scoreboardTemplate", {
              coursename: coursename,
              username: names_sb,
              leadership: leadership_sb,
              teamPlayer: teamwork_sb,
              creativeness: creativeness_sb,
              assertiveness: assertiveness_sb,
              orator: orator_sb,
              length: length,
              course:req.session.course,
              name:req.session.username
            });
          }
        }
      );
    }
  });
});

app.get("/prof", (req, res) => {
  let dbGroupid;
  let dbCourseId = req.session.course[req.session.courseId].id;
  const userid = req.session.userid;
  console.log("userid: " + userid);
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fiels) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });
      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      dbGroupid = group_course[courseIndex].groupid;
      console.log("평가삽입groupid: " + dbGroupid);
      let userids = [];
      var result22 = conn2.query(
        `SELECT userid FROM mdl_groups_members WHERE groupid = ${dbGroupid}`
      );

      for (var i = 0; i < result22.length; i++) {
        userids.push(result22[i].userid);
      }

      //mdl_roleassingment에 roleid가 role을 결정
      var sql2 = "SELECT * FROM a_rate where courseid = ?";

      conn.query(
        sql2,
        [req.session.course[req.session.courseId].id],
        function (error, rows, result) {
          let length = rows.length;
          if (error) throw error;
          else {
            let leadership_sb = [];
            let teamwork_sb = [];
            let creativeness_sb = [];
            let assertiveness_sb = [];
            let orator_sb = [];
            let userids_sb = [];
            let names_sb = [];
            let keys = [];

            for (var i = 0; i < length; i++) {
              userids_sb[i] = rows[i].userid;
              leadership_sb[i] = rows[i].leadership;
              teamwork_sb[i] = rows[i].teamwork;
              creativeness_sb[i] = rows[i].creativeness;
              assertiveness_sb[i] = rows[i].assertiveness;
              orator_sb[i] = rows[i].orator;
              keys[i] =
                leadership_sb[i] +
                teamwork_sb[i] +
                creativeness_sb[i] +
                assertiveness_sb[i] +
                orator_sb[i];
            }
            var result;
            for (var j = 0; j < length; j++) {
              result = conn2.query(
                "select firstname, lastname from mdl_user where id = ?",
                [userids_sb[j]]
              );
              names_sb[j] = result[0].firstname + " " + result[0].lastname;
            }

            for (var i = 0; i < length - 1; i++) {
              for (var j = 0; j < length - 1 - i; j++) {
                if (keys[j] < keys[j + 1]) {
                  var names_t,
                    leadership_t,
                    teamwork_t,
                    creativeness_t,
                    assertiveness_t,
                    orator_t;

                  names_t = names_sb[j + 1];
                  leadership_t = leadership_sb[j + 1];
                  teamwork_t = teamwork_sb[j + 1];
                  creativeness_t = creativeness_sb[j + 1];
                  assertiveness_t = assertiveness_sb[j + 1];
                  orator_t = orator_sb[j + 1];

                  names_sb[j + 1] = names_sb[j];
                  leadership_sb[j + 1] = leadership_sb[j];
                  teamwork_sb[j + 1] = teamwork_sb[j];
                  creativeness_sb[j + 1] = creativeness_sb[j];
                  assertiveness_sb[j + 1] = assertiveness_sb[j];
                  orator_sb[j + 1] = orator_sb[j];

                  names_sb[j] = names_t;
                  leadership_sb[j] = leadership_t;
                  teamwork_sb[j] = teamwork_t;
                  creativeness_sb[j] = creativeness_t;
                  assertiveness_sb[j] = assertiveness_t;
                  orator_sb[j] = orator_t;
                }
              }
            }

            var result12 = conn2.query(
              `SELECT fullname FROM mdl_course WHERE id = ${
                req.session.course[req.session.courseId].id
              }`
            );
            var coursename = result12[0].fullname;

            var result13 = conn2.query(
              `SELECT idnumber FROM mdl_groups WHERE id = ${dbGroupid}`
            );

            console.log(result13[0].idnumber);

            res.render("profscoreboardTemplate", {
              coursename: coursename,
              username: names_sb,
              leadership: leadership_sb,
              teamPlayer: teamwork_sb,
              creativeness: creativeness_sb,
              assertiveness: assertiveness_sb,
              orator: orator_sb,
              length: length,
              course:req.session.course,
              name:req.session.username,
    
            });
          }
        }
      );
    }
  });
});

app.get("/", function (req, res) {
  let _url = req.url;
  let queryData = url.parse(_url, true).query;
  let loginId = queryData.id;
  IdRepository = [];

  makerepository();

  async function makerepository() {
    for (var j in db) {
      if (db[j].guid == loginId) {
        if (db[j].g_path) {
          IdRepository.push(db[j].g_path);
        } else {
          var newrpos = "./grouprepository/" + db[j].c_name + "_" + db[j].gid;
          var cname = db[j].c_name;
          var dbgid = db[j].gid;
          await makedir(newrpos, cname, dbgid);
        }
      }
    }
  }

  function makedir(a, b, c) {
    fs.mkdir(a, (err) => {
      conn.query(
        `Update mdl_groups set group_path = "${b + "_" + c}" where id=${c};`
      );
      dbqueryinput();
    });
  }

  let sql = `select id, shortname
               from mdl_course as C
               where C.id in (select B.courseid
                              from mdl_groups as B
                              where B.id in (select A.groupid
                                             from mdl_groups_members as A
                                             where userid=${queryData.id}));`;
  conn.query(sql, function (err, rows1, fields) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      sql = `select firstname, lastname from mdl_user where id=${loginId}`
      conn.query(sql, function(err, rows, fields){
        const name = rows[0].firstname+rows[0].lastname
        req.session.username = name;
        req.session.userid = loginId;
        //console.log(rows1)
        req.session.course = rows1;
        req.session.isLogined = true;
  
        req.session.save(function () {
          res.render("home.ejs", { course: rows1, username : name });
        });

      })
    
    }
  });
});

app.get("/fileUpload", function (req, res) {
  const userid = req.session.userid;
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fields) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });

      let dbCourseId = req.session.course[req.session.courseId].id;

      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      if (courseIndex === -1) {
        res.redirect("/home");
      } else {
        let dbGroupid = group_course[courseIndex].groupid;

        sql = `select distinct mdl_groups.group_path, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list,courseid
                       from mdl_groups_members, mdl_user,mdl_groups
                       where mdl_groups_members.userid = mdl_user.id and
                             mdl_groups_members.groupid=${dbGroupid} and           
                             mdl_groups_members.groupid = mdl_groups.id and
                             mdl_groups.courseid = ${dbCourseId};`;

        conn.query(sql, function (err, rows, fields) {
          if (err) console.log("query is not excuted. select fail...\n" + err);
          else {
            let groupIndex = rows.findIndex((element) => {
              return element.groupid === dbGroupid;
            });

            res.redirect(
              `/${rows[groupIndex].group_path}?id=${req.session.userid}`
            );
          }
        });
      }
    }
  });
});

app.get("/teamPage", function (req, res) {
  const user = "tollea1235"; // 임시로 tollea1235, 무들에서 로그인정보(로그인ID)를 받아올것
  const userid = req.session.userid;
  console.log("userid : " + userid);
  let sql = `select courseid,id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid});`;

  const group_course = [];
  conn.query(sql, function (err, rows, fields) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });

      let dbCourseId = req.session.course[req.session.courseId].id;

      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      console.log(group_course);

      if (courseIndex == -1) {
        res.redirect("/home");
      } else {
        let dbGroupid = group_course[courseIndex].groupid;
        console.log("팀페이지 dbGroupid : " + dbGroupid);

        sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list,courseid
                    from mdl_groups_members, mdl_user,mdl_groups
                    where mdl_groups_members.userid = mdl_user.id and
                            mdl_groups_members.groupid=${dbGroupid} and           
                            mdl_groups_members.groupid = mdl_groups.id and
                            mdl_groups.courseid = ${dbCourseId};`;

        const names = [];
        let group_user = [];
        let to_do_list = [];
        conn.query(sql, function (err, rows, fields) {
          if (err) console.log("query is not excuted. select fail...\n" + err);
          else {
            rows.forEach((element) => {
              if (element.courseid === dbCourseId) {
                names.push(element.firstname + element.lastname);
                to_do_list.push(element.to_do_list);
                group_user.push(element.groupid + "_" + element.id);
              }
            });

            req.session.names = names;
            let groupIndex = rows.findIndex((element) => {
              return element.groupid === dbGroupid;
            });

            req.session.to_do_list = to_do_list;
            req.session.group_user = group_user;

            req.session.save(function () {
              res.render("teamPage2.ejs", {
                memberName: names,
                groupName: rows[groupIndex].name,
                course: req.session.course,
                username:req.session.username,
                coursename:req.session.coursename
              });
            });
          }
        });
      }
    }
  });
});

app.post("/store/:id", function (req, res) {
  var group = req.params.id.split("_")[0];
  var user = req.params.id.split("_")[1];
  conn.query(
    `Update mdl_groups_members set to_do_list = "${req.body.memo}"
      where groupid=${group} and userid=${user}`
  );
  res.writeHead(302, { Location: "/workList" });
  res.end();
});

app.get("/main", function (req, res) {
  console.log(req.session.userid);
  res.redirect(`/home`);
});

app.get("/home", function (req, res) {
  res.redirect(`/?id=${req.session.userid}`);
});

app.get("/profilePage", function (req, res) {
  res.render("profilePage.ejs", { course: req.session.course });
});

let comment = "hello";

app.get("/workList", function (req, res) {
  let dbCourseId = req.session.course[req.session.courseId].id;
  const userid = req.session.userid;
  console.log("userid: " + userid);
  let sql = `select courseid, id
               from mdl_groups
               where id in (select groupid
                            from mdl_groups_members
                            where userid=${userid})`;
  const group_course = [];
  conn.query(sql, function (err, rows, fiels) {
    if (err) console.log("query is not excuted. select fail...\n" + err);
    else {
      
      rows.forEach((element) => {
        group_course.push({ courseid: element.courseid, groupid: element.id });
      });
      const courseIndex = group_course.findIndex(function (element) {
        if (element.courseid === dbCourseId) {
          return true;
        }
      });

      let dbGroupid = group_course[courseIndex].groupid;

      console.log("dbGroupid : " + dbGroupid);
      console.log("dbCourseid : " + dbCourseId);
      sql = `select distinct mdl_groups.name, groupid, firstname, lastname, mdl_user.id, mdl_groups_members.to_do_list,courseid
                   from mdl_groups_members, mdl_user,mdl_groups
                   where mdl_groups_members.userid = mdl_user.id and
                         mdl_groups_members.groupid=${dbGroupid} and           
                         mdl_groups_members.groupid = mdl_groups.id and
                         mdl_groups.courseid = ${dbCourseId};`;

      const names = [];
      let group_user = [];
      let to_do_list = [];
      conn.query(sql, function (err, rows1, fields) {
        
        
        console.log(rows1)
        rows1.forEach((element) => {
          if (element.courseid === dbCourseId) {
            names.push(element.firstname + element.lastname);
            to_do_list.push(element.to_do_list);
            group_user.push(element.groupid + "_" + element.id);
          }
        });

        req.session.names = names;
        let groupIndex = rows1.findIndex((element) => {
          return element.groupid === dbGroupid;
        });

        req.session.groupName = rows1[groupIndex].name;
        req.session.to_do_list = to_do_list;
        req.session.group_user = group_user;  
        
        req.session.save(function () {
          res.render("workList2.ejs", {
            memberName: names,
            groupName: req.session.groupName.name,
            comment: req.session.to_do_list,
            group_user: req.session.group_user,
            course: req.session.course,
            username:req.session.username,
            coursename:req.session.coursename
          
          });
        });
          


        

        
      });
    }
  });
});

app.get("/course?:id", function (req, res) {
  var result4 = conn2.query(
    `SELECT groupid FROM mdl_groups_members WHERE userid = ${req.session.userid}`
  );

  req.session.groupid = result4[0].groupid;
  console.log(req.session.groupid);

  var result13 = conn2.query(
    `SELECT idnumber FROM mdl_groups WHERE id = ${req.session.groupid}`
  );

  console.log(result13[0].idnumber);
  if (result13[0].idnumber === "777") {
    res.redirect("/prof");
  }

  //console.log(req.session.username)
  let _url = req.url;
  let queryData = url.parse(_url, true).query;
  if (Object.keys(queryData).length > 0) {
    req.session.courseId = queryData.id;
    let dbCourseId = req.session.course[req.session.courseId].id;
    console.log("dbCourseid : " + dbCourseId);
    let sql = `select fullname from mdl_course where id=${dbCourseId}`
    conn.query(sql, function(err, rows, fields){

      req.session.coursename = rows[0].fullname

      req.session.save(function () {
        res.render("course2.ejs", {
          course: req.session.course,
          courseId: queryData.id,
          userid: req.session.userid,
          username:req.session.username,
          coursename : req.session.coursename
        });
      });
      
    })

    
  }
});

const wrapper = (asyncFn) => {
  return async (req, res, next) => {
    try {
      return await asyncFn(req, res, next);
    } catch (error) {
      return next(error);
    }
  };
};

app.get(
  "/:id",
  wrapper(async (req, res) => {
    var loginId = req.query.id;
    var group = req.params.id;
    console.log();
    group = "./grouprepository/" + group;

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
          var finalpath = fbpath.replace(
            "./grouprepository",
            "/grouprepository"
          );
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
                  <textarea name = "content" cols="42" rows="9" id = 'comment_area${j}' style="display:none" ></textarea><br>
                  <input type="submit" value="Edit" id = 'comment_edit${j}' style="display:none" >
                  </form>
  
                  </div>
                  <script src="https://code.jquery.com/jquery-3.2.1.min.js"></script>
                  <script type="text/javascript">
                      $(document).on("click","#dis${j}", function(){
                          if($("#comment_area${j}").css('display') == 'none'){
                              $("#comment_area${j}").show();
                              $("#comment_edit${j}").show();
                              $("#listcontent${j}").css('width','100%');
                              $("#listcontent${j}").css('height','200%');
                              $("#listcontent${j}").css('z-index', '1000');
                              $("#comment_area${j}").load("${finalpath}",function(txt, status,xhr){
                                  if (status == "success") {
                                  } else if (status == "error") {
                                      
                                  }
                              });
                              }else{
                                  $("#listcontent${j}").css('width','100%');
                                  $("#listcontent${j}").css('height','100%');
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

    function getCourse(course) {
      options = [];
      // files_.push(`<select name="course" onchange="location=this.value;">`)
      //options.push(`<option value="select-course" > 강좌를 선택하세요 </option>`)
      for (var i = 0; i < course.length; i++) {
        options.push(
          `<option value="course?id=${i}"> ${course[i].shortname} </option>`
        );
      }
      // files_.push("</select>")
      options = options.join("");
      return options;
    }

    let ugroup = group.replace(/\//g, ",");
    var html = template.HTML(
      getCourse(req.session.course),
      getFiles(group, 0),
      getFiles2("./grouprepository", 0),
      ugroup + "?id=" + loginId,
      req.session.username,
      req.session.coursename
    );
    res.writeHead(200);
    res.end(html);
  })
);

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
