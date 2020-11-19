var http = require('http');
var formidable = require('formidable');
var fs = require('fs');
var url = require('url');
var express = require('express');
var app = express();
const bodyParser = require('body-parser')
const mysql      = require('mysql');
const dbconfig   = require('./config/database.js');
const connection = mysql.createConnection(dbconfig);

app.use(bodyParser.urlencoded({extended:false}))

app.set('port', process.env.PORT || 8888);

app.use(express.static('public'));


var groupName=[];
var firstnames=[];
var lastnames=[];

// var server = http.createServer(app).listen(app.get('port'), function () {
//     connection.query('SELECT name from mdl_groups', (error, rows) => {
//         if (error) throw error;
//         for (var i in rows){
//             groupName.push(rows[i].name);
//         }
//       });
    
//     connection.query(`select mdl_user.firstname, mdl_user.lastname 
//                     from mdl_user
//                     inner join mdl_groups_members on mdl_user.id=mdl_groups_members.userid;`, (error, rows) =>{
//                         if(error) throw error;
//                         for(var i in rows){
//                             firstnames.push(rows[i].firstname)
//                             lastnames.push(rows[i].lastname)
//                         }
//                     })
      
//     }
// );




app.get('/', function (req, res) {
    //res.send(db);


    var title = 'Welcome';
    var template = `
    <!DOCTYPE html>
    <html class="" lang="">
      <head>
        <script type="text/javascript" class="silex-json-styles" data-silex-static="">
        window.silex = window.silex || {}
        window.silex.data = {"site":{"width":1123.18408203125},"pages":[{"id":"page-main","displayName":"main","link":{"linkType":"LinkTypePage","href":"#!page-main"},"canDelete":true,"canRename":true,"canMove":true,"canProperties":true,"opened":false},{"id":"page-team","displayName":"team","link":{"linkType":"LinkTypePage","href":"#!page-team"},"canDelete":true,"canRename":true,"canMove":true,"canProperties":true,"opened":false},{"id":"page-profile","displayName":"profile","link":{"linkType":"LinkTypePage","href":"#!page-profile"},"canDelete":true,"canProperties":true,"canMove":true,"canRename":true,"opened":false}]}</script>
        <meta charset="UTF-8">
        <!-- generator meta tag -->
        <!-- leave this for stats and Silex version check -->
        <meta name="generator" content="Silex v2.2.11">
        <!-- End of generator meta tag -->
        <script type="text/javascript" src="https://editor.silex.me/static/2.11/jquery.js" data-silex-static=""></script>
        <script type="text/javascript" src="https://editor.silex.me/static/2.11/jquery-ui.js" data-silex-static="" data-silex-remove-publish=""></script>
        <script type="text/javascript" src="https://editor.silex.me/static/2.11/pageable.js" data-silex-static="" data-silex-remove-publish=""></script>
        <script type="text/javascript" src="https://editor.silex.me/static/2.11/front-end.js" data-silex-static=""></script>
        <link rel="stylesheet" href="https://editor.silex.me/static/2.11/normalize.css" data-silex-static="">
        <link rel="stylesheet" href="https://editor.silex.me/static/2.11/front-end.css" data-silex-static="">
    
        <style type="text/css" class="silex-style"></style>
        <script type="text/javascript" class="silex-script"></script>
        <style class="silex-inline-styles" type="text/css">
          .body-initial {background-color: rgba(13,13,13,1); position: static;}
          .silex-id-1478366444112-1 {background-color: rgba(13,13,13,1); position: static; margin-top: -1px; border-color: rgba(173,173,173,1);}
          .silex-id-1478366444112-0 {background-color: rgba(13,13,13,1); min-height: 665px; position: relative; margin-left: auto; margin-right: auto; border-color: rgba(158,158,158,1); display: block;}
          .silex-id-1474394621033-3 {position: static; margin-top: -1px; background-color: rgba(13,13,13,1); border-color: rgba(164,162,162,1); border-width: 0 0 2px 0; border-style: solid;}
          .silex-id-1474394621032-2 {background-color: rgba(13,13,13,1); min-height: 298px; position: relative; margin-left: auto; margin-right: auto; border-width: 0 0 2px 0; border-style: solid; border-color: rgba(71,71,71,1);}
          .silex-id-1604381522345-1 {width: 135px; height: 125px; position: absolute; top: 50px; left: 60px;}
          .silex-id-1604381556411-2 {width: 170px; min-height: 80.3515625px; position: absolute; top: 180px; left: 45px; background-color: transparent;}
          .silex-id-1604643193909-2 {width: 270.65972900390625px; min-height: 1900px; background-color: rgba(38,38,39,1); position: absolute; top: 1px; left: 0px; display: block;}
          .silex-id-1604643380215-3 {width: 265px; min-height: 55px; background-color: transparent; position: absolute; top: 300.52734375px; left: 00px; border-width: 2px 0 2px 0; border-style: solid; border-color: rgba(255,255,255,1);}
          .silex-id-1604643414316-4 {width: 265px; min-height: 55px; background-color: transparent; position: absolute; top: 362.9201354980469px; left: -0.190972238779068px; border-width: 0 0 2px 0; border-style: solid; border-color: rgba(255,255,255,1);}.silex-id-1604644963736-10 {width: 116px; min-height: 53.2421875px; position: absolute; top: 0px; left: 80px;}
          .silex-id-1604645216399-12 {width: 64px; min-height: 54px; position: absolute; top: 0px; left: 80px;}
          .silex-id-1604710473649-0 {width: 26px; height: 31px; position: absolute; top: 10px; left: 35px;}
          .silex-id-1604710519311-1 {width: 25px; height: 25px; position: absolute; top: 15px; left: 35px;}
          .silex-id-1605152678603-4 {width: 265px; min-height: 55px; background-color: transparent; position: absolute; top: 300px; left: 0px; border-width: 2px 0 2px 0; border-style: solid; border-color: rgba(255,255,255,1);}
          .silex-id-1605152678603-7 {width: 265px; min-height: 55px; background-color: transparent; position: absolute; top: 362px; left: 0px; border-width: 0 0 2px 0; border-style: solid; border-color: rgba(255,255,255,1);}
          .silex-id-1605152678603-9 {width: 25px; height: 25px; position: absolute; top: 15px; left: 35px;}
          .silex-id-1605153310902-18 {width: 110px; min-height: 53px; background-color: rgba(210,208,208,1); position: absolute; top: 103px; left: 13px;}
          .silex-id-1605153603327-20 {width: 110px; min-height: 53px; background-color: rgba(66,66,66,1); position: absolute; top: 20px; left: 13px;}
          .silex-id-1605153782286-21 {width: 110px; min-height: 53px; background-color: rgba(210,208,208,1); position: absolute; top: 163px; left: 13px;}
          .silex-id-1605153789022-23 {width: 110px; min-height: 53px; background-color: rgba(210,208,208,1); position: absolute; top: 223px; left: 13px;}
          .silex-id-1605153856283-25 {width: 110px; min-height: 53px; background-color: rgba(210,208,208,1); position: absolute; top: 343px; left: 13px;}
          .silex-id-1605153856681-26 {width: 110px; min-height: 53px; background-color: rgba(210,208,208,1); position: absolute; top: 283px; left: 13px;}
          .silex-id-1605153983873-28 {width: 110px; min-height: 53px; background-color: rgba(210,208,208,1); position: absolute; top: 405px; left: 13px;}
          .silex-id-1605154601439-30 {width: 820px; min-height: 53px; background-color: rgba(66,66,66,1); position: absolute; top: 20px; left: 137px;}
          .silex-id-1605156214985-32 {width: 195px; min-height: 45px; background-color: rgba(99,99,99,1); position: absolute; top: 102.73661804199219px; left: 137.3267822265625px;}
          .silex-id-1605157224136-36 {width: 64px; min-height: 53px; position: absolute; left: 80px;}
          .silex-id-1605157281739-38 {width: 116px; min-height: 53px; position: absolute; left: 80px;}
          .silex-id-1605158436114-42 {width: 135px; height: 125px; position: absolute; top: 50px; left: 60px;}
          .silex-id-1605158436114-43 {width: 170px; min-height: 70px; position: absolute; top: 180px; left: 45px; background-color: transparent;}
          .silex-id-1605158642745-48 {width: 26px; height: 31px; position: absolute; top: 10px; left: 35px;}
          .silex-id-1605169253679-1 {width: 783px; min-height: 53px; background-color: rgba(66,66,66,1); position: absolute; top: 20.104461669921875px; left: 109.90625px;}
          .silex-id-1605169308724-2 {width: 193px; min-height: 221px; background-color: rgba(173,173,173,1); position: absolute; top: 89.17755126953125px; left: 110.12509155273438px;}
          .silex-id-1605169337585-3 {width: 132px; height: 133px; position: absolute; top: 114.78521728515625px; left: 139.11465454101562px;}
          .silex-id-1605169362105-5 {width: 100px; min-height: 53px; background-color: rgba(173,173,173,1); position: absolute; top: 88.79180908203125px; left: 394.00347900390625px;}
          .silex-id-1605169414376-6 {width: 100px; min-height: 53px; background-color: rgba(173,173,173,1); position: absolute; top: 88.92049407958984px; left: 506.0069580078125px;}
          .silex-id-1605169429086-8 {width: 100px; min-height: 53px; background-color: rgba(173,173,173,1); position: absolute; top: 88.68417358398438px; left: 618.0103759765625px;}
          .silex-id-1605169447034-10 {width: 70.86804962158203px; min-height: 53px; background-color: rgba(173,173,173,1); position: absolute; top: 88px; left: 821.131950378418px;}
          .silex-id-1605169479817-12 {width: 70px; min-height: 53px; background-color: rgba(173,173,173,1); position: absolute; top: 418.9965515136719px; left: 820.8231201171875px;}
          .silex-id-1605169671992-14 {width: 265px; min-height: 55px; background-color: transparent; position: absolute; top: 300px; left: 0.388949915766716px; border-width: 2px 0 2px 0; border-style: solid; border-color: rgba(255,255,255,1);}
          .silex-id-1605169671992-15 {width: 116px; min-height: 53px; position: absolute; left: 80px;}
          .silex-id-1605169671992-16 {width: 26px; height: 31px; position: absolute; top: 10px; left: 35px;}
          .silex-id-1605169710227-20 {width: 265px; min-height: 55px; background-color: transparent; position: absolute; top: 362px; left: 00px; border-width: 0 0 2px 0; border-style: solid; border-color: rgba(255,255,255,1);}
          .silex-id-1605169710227-21 {width: 25px; height: 25px; position: absolute; top: 15px; left: 35px;}
          .silex-id-1605169710227-22 {width: 64px; min-height: 53px; position: absolute; left: 80px;}
          .silex-id-1605169710227-23 {width: 135px; height: 125px; position: absolute; top: 50px; left: 60px;}
          .silex-id-1605169710227-24 {width: 170px; min-height: 70px; position: absolute; top: 180px; left: 45px; background-color: transparent;}
          .silex-id-1605169710227-25 {width: 265px; min-height: 55px; background-color: transparent; position: absolute; top: 300px; left: 00px; border-width: 2px 0 2px 0; border-style: solid; border-color: rgba(255,255,255,1);}
          .silex-id-1605169710227-26 {width: 116px; min-height: 53px; position: absolute; left: 80px;}
          .silex-id-1605169710227-27 {width: 26px; height: 31px; position: absolute; top: 10px; left: 35px;}@media only screen and (max-width: 480px) {}
         </style>
        <title></title>
        
    
        
         <link href="https://fonts.googleapis.com/css?family=Roboto" rel="stylesheet" class="silex-custom-font">
         <meta name="viewport" content="width=device-width, initial-scale=1">
         <style type="text/css" class="silex-style-settings">
         .website-width {width: 1123.18408203125px;}@media (min-width: 481px) {.silex-editor {min-width: 1323.18408203125px;}}
        </style>
        <style class="silex-prodotype-style" type="text/css" data-style-id="all-style">
        .text-element > .silex-element-content {font-family: 'Roboto', sans-serif; font-style: normal; color: #ffffff; text-align: left; border-color: #ffffff; -webkit-transition: all 1s ease; -moz-transition: all 1s ease; -o-transition: all 1s ease; transition: all 1s ease;}a {color: #ffffff; text-decoration: none;}[data-silex-href] {color: #ffffff; text-decoration: none;}
        </style>
    
        <style class="silex-prodotype-style" type="text/css" data-style-id="style-all-style1">
        .style-all-style1.text-element > .silex-element-content {font-family: 'Roboto', sans-serif; color: #ffffff; -webkit-transition: all 1s ease; -moz-transition: all 1s ease; -o-transition: all 1s ease; transition: all 1s ease;}
        </style>
      </head>
    
    <body data-silex-id="body-initial" class="body-initial all-style enable-mobile prevent-resizable prevent-selectable editable-style silex-runtime" data-silex-type="container-element" style="" data-new-gr-c-s-loaded="14.983.0">
        
    <div data-silex-type="container-element" class="container-element editable-style silex-id-1474394621033-3 section-element prevent-resizable hide-on-mobile" data-silex-id="silex-id-1474394621033-3" style="">
            
        <div data-silex-type="container-element" class="editable-style silex-element-content silex-id-1474394621032-2 container-element website-width selected" data-silex-id="silex-id-1474394621032-2" style=""></div>
        <div data-silex-type="container-element" class="editable-style container-element silex-id-1605152678603-4 page-team paged-element" data-silex-id="silex-id-1605152678603-4" style="">
          <div data-silex-type="text-element" class="editable-style text-element silex-id-1605157281739-38 page-team paged-element" data-silex-id="silex-id-1605157281739-38" style="">
            <div class="silex-element-content normal"><p><b><a href="#!page-team" title="공동문서 작업" linktype="LinkTypePage" class="">공동 문서 작업</a></b></p>
            </div>
          </div>
          <div data-silex-type="image-element" class="editable-style image-element silex-id-1605158642745-48 page-team paged-element" data-silex-id="silex-id-1605158642745-48" style="">
            <img src="group%20icon.png">
          </div>
        </div>
        <div data-silex-type="container-element" class="editable-style container-element silex-id-1604643193909-2 hide-on-mobile" data-silex-id="silex-id-1604643193909-2" style="">
          <div data-silex-type="container-element" class="editable-style container-element silex-id-1604643380215-3 page-profile paged-element" data-silex-id="silex-id-1604643380215-3" style="">
            <div data-silex-type="text-element" class="editable-style text-element silex-id-1604644963736-10 page-profile paged-element" data-silex-id="silex-id-1604644963736-10" style="">
              <div class="silex-element-content normal"><p><b><a href="#!page-team" title="공동문서 작업" class="">공동 문서 작업</a></b></p>
              </div>
            </div>
            <div data-silex-type="image-element" class="editable-style image-element silex-id-1604710473649-0 page-profile paged-element" data-silex-id="silex-id-1604710473649-0" style=""><img src="group%20icon.png"></div></div><div data-silex-type="image-element" class="editable-style image-element silex-id-1604381522345-1 style-all-style1 page-profile paged-element" data-silex-id="silex-id-1604381522345-1" style=""><img src="logo.637cfd18.jpg"></div><div data-silex-type="container-element" class="editable-style container-element silex-id-1604643414316-4 page-profile paged-element" data-silex-id="silex-id-1604643414316-4" style=""><div data-silex-type="text-element" class="editable-style text-element silex-id-1604645216399-12 page-profile paged-element" data-silex-id="silex-id-1604645216399-12" style=""><div class="silex-element-content normal"><p><b><a href="#!page-profile" linktype="LinkTypePage" class="page-link-active">프로필</a></b></p></div></div><div data-silex-type="image-element" class="editable-style image-element silex-id-1604710519311-1 page-profile paged-element" data-silex-id="silex-id-1604710519311-1" style=""><img src="icon-profile-user.png"></div></div><div data-silex-type="text-element" class="editable-style text-element silex-id-1604381556411-2 style-all-style1 page-profile paged-element" data-silex-id="silex-id-1604381556411-2" style=""><div class="silex-element-content normal"><h1><b><a href="#!page-main" linktype="LinkTypePage">PLASS DGU</a></b><br></h1></div></div><div data-silex-type="text-element" class="editable-style text-element silex-id-1605158436114-43 style-all-style1 page-team paged-element" data-silex-id="silex-id-1605158436114-43" style=""><div class="silex-element-content normal"><h1><b><a href="#!page-main" linktype="LinkTypePage" class="">PLASS DGU</a></b><br></h1></div></div><div data-silex-type="image-element" class="editable-style image-element silex-id-1605158436114-42 style-all-style1 page-team paged-element" data-silex-id="silex-id-1605158436114-42" style=""><img src="logo.637cfd18.jpg"></div><div data-silex-type="container-element" class="editable-style container-element silex-id-1605169671992-14 page-team paged-element" data-silex-id="silex-id-1605169671992-14" style=""><div data-silex-type="text-element" class="editable-style text-element silex-id-1605169671992-15 page-team paged-element" data-silex-id="silex-id-1605169671992-15" style=""><div class="silex-element-content normal"><p><b><a href="#!page-team" title="공동문서 작업" linktype="LinkTypePage" class="">공동 문서 작업</a></b></p></div></div><div data-silex-type="image-element" class="editable-style image-element silex-id-1605169671992-16 page-team paged-element" data-silex-id="silex-id-1605169671992-16" style=""><img src="group%20icon.png"></div></div><div data-silex-type="image-element" class="editable-style image-element silex-id-1605169710227-23 page-main paged-element style-all-style1" data-silex-id="silex-id-1605169710227-23" style=""><img src="logo.637cfd18.jpg"></div><div data-silex-type="container-element" class="editable-style container-element silex-id-1605169710227-25 page-main paged-element" data-silex-id="silex-id-1605169710227-25" style=""><div data-silex-type="text-element" class="editable-style text-element silex-id-1605169710227-26 page-main paged-element" data-silex-id="silex-id-1605169710227-26" style=""><div class="silex-element-content normal"><p><b><a href="#!page-team" title="공동문서 작업" linktype="LinkTypePage" class="">공동 문서 작업</a></b></p></div></div><div data-silex-type="image-element" class="editable-style image-element silex-id-1605169710227-27 page-main paged-element" data-silex-id="silex-id-1605169710227-27" style=""><img src="group%20icon.png"></div></div><div data-silex-type="container-element" class="editable-style container-element silex-id-1605169710227-20 page-main paged-element" data-silex-id="silex-id-1605169710227-20" style=""><div data-silex-type="image-element" class="editable-style image-element silex-id-1605169710227-21 page-main paged-element" data-silex-id="silex-id-1605169710227-21" style=""><img src="icon-profile-user.png"></div><div data-silex-type="text-element" class="editable-style text-element silex-id-1605169710227-22 page-main paged-element" data-silex-id="silex-id-1605169710227-22" style=""><div class="silex-element-content normal"><p><b><a href="#!page-profile" class="page-link-active">프로필</a></b></p></div></div></div><div data-silex-type="text-element" class="editable-style text-element silex-id-1605169710227-24 page-main paged-element style-all-style1" data-silex-id="silex-id-1605169710227-24" style=""><div class="silex-element-content normal"><h1><b><a href="#!page-main" linktype="LinkTypePage" class="">PLASS DGU</a></b><br></h1><span class="_wysihtml-temp-caret-fix" style="position: absolute; display: block; min-width: 1px; z-index: 99999;">﻿</span></div></div></div></div><div data-silex-type="container-element" class="container-element editable-style silex-id-1478366444112-1 section-element prevent-resizable" data-silex-id="silex-id-1478366444112-1" style="">
            
        <div data-silex-type="container-element" class="editable-style silex-element-content silex-id-1478366444112-0 container-element website-width" data-silex-id="silex-id-1478366444112-0" style="">
          <div data-silex-type="html-element" class="editable-style html-element silex-id-1605154601439-30 page-team paged-element" data-silex-id="silex-id-1605154601439-30" style="">
            <div class="silex-element-content">
              <ul style="list-style-type:none">
               <span style="font-weight: bold; color: white;" "="">
                 <li>그룹명: ${groupName[0]}</li>
               </span>
              </ul>
            </div>
          </div>
          <div data-silex-type="html-element" class="editable-style html-element silex-id-1605153983873-28 page-team paged-element" data-silex-id="silex-id-1605153983873-28" style="">
            <div class="silex-element-content">
              <p><strong></strong></p>
              <center>
                <strong>
                  <font color="black">팀원5</font>
                </strong>
                <center>
                  <strong></strong><p></p>
                </center>
              </center>
            </div>
          </div>
          <div data-silex-type="html-element" class="editable-style html-element silex-id-1605153856681-26 page-team paged-element" data-silex-id="silex-id-1605153856681-26" style="">
            <div class="silex-element-content">
              <p><strong></strong></p>
              <center>
                <strong>
                  <font color="black">팀원3</font>
                </strong><center>
                  <strong></strong><p></p>
                </center>
              </center>
            </div>
          </div>
          <div data-silex-type="html-element" class="editable-style html-element silex-id-1605153856283-25 page-team paged-element" data-silex-id="silex-id-1605153856283-25" style="">
            <div class="silex-element-content">
              <p><strong></strong></p>
              <center>
                <strong><font color="black">팀원4</font></strong>
                <center><strong></strong><p></p></center>
              </center>
            </div>
          </div>
          <div data-silex-type="html-element" class="editable-style html-element silex-id-1605153789022-23 page-team paged-element" data-silex-id="silex-id-1605153789022-23" style="">
            <div class="silex-element-content">
              <p><strong></strong></p>
              <center>
                <strong>
                  <font color="black">팀원2</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605153782286-21 page-team paged-element" data-silex-id="silex-id-1605153782286-21" style="">
              <div class="silex-element-content">
                <p><strong></strong></p>
                <center>
                  <strong><font color="black">팀원1</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605153310902-18 page-team paged-element" data-silex-id="silex-id-1605153310902-18" style="">
              <div class="silex-element-content">
                <p><strong></strong></p>
                <center>
                  <strong><font color="black">팀장</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605153603327-20 page-team paged-element" data-silex-id="silex-id-1605153603327-20" style="">
              <div class="silex-element-content">
                <ul style="list-style-type:none">
                 <span style="font-weight: bold; color: white;" "="">
                  <li>그룹 </li>
                 </span>
                </ul>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605169362105-5 page-profile paged-element" data-silex-id="silex-id-1605169362105-5" style="">
              <div class="silex-element-content">
                <p><strong></strong></p>
                <center><strong><font size="">강좌</font></strong>
                  <center><strong></strong><p></p>
                  </center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605169414376-6 page-profile paged-element" data-silex-id="silex-id-1605169414376-6" style="">
              <div class="silex-element-content">
                <p><strong></strong></p>
                <center>
                  <strong><font size="">Details</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605169429086-8 page-profile paged-element" data-silex-id="silex-id-1605169429086-8" style="">
              <div class="silex-element-content">
                <p><strong></strong></p>
                <center><strong><font size="">특기</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605169308724-2 page-profile paged-element" data-silex-id="silex-id-1605169308724-2" style="">
              <div class="silex-element-content"><br><br><br><br><br><br><br><br><br>
                <p><strong></strong></p>
                <center><strong>"User name"</strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605169253679-1 page-profile paged-element" data-silex-id="silex-id-1605169253679-1" style="">
              <div class="silex-element-content"><p><strong></strong></p>
                <center><strong><font color="white">User Profile</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="image-element" class="editable-style image-element silex-id-1605169337585-3 page-profile paged-element" data-silex-id="silex-id-1605169337585-3" style="">
              <img src="icon-profile-user.png">
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605169447034-10 page-profile paged-element" data-silex-id="silex-id-1605169447034-10" style="">
              <div class="silex-element-content"><p><strong></strong></p>
                <center><strong><font size="">수정</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="html-element" class="editable-style html-element silex-id-1605169479817-12 page-profile paged-element" data-silex-id="silex-id-1605169479817-12" style="">
              <div class="silex-element-content"><p><strong></strong></p>
                <center><strong><font size="">저장</font></strong>
                  <center><strong></strong><p></p></center>
                </center>
              </div>
            </div>
            <div data-silex-type="container-element" class="editable-style container-element silex-id-1605156214985-32 page-team paged-element" data-silex-id="silex-id-1605156214985-32" style="">
                <label> ${firstnames[0] + lastnames[0]}</label>
            </div>
          </div>
          <div data-silex-type="container-element" class="editable-style container-element silex-id-1605152678603-7 page-team paged-element" data-silex-id="silex-id-1605152678603-7" style="">
            <div data-silex-type="image-element" class="editable-style image-element silex-id-1605152678603-9 page-team paged-element" data-silex-id="silex-id-1605152678603-9" style="">
              <img src="icon-profile-user.png">
            </div>
            <div data-silex-type="text-element" class="editable-style text-element silex-id-1605157224136-36 page-team paged-element" data-silex-id="silex-id-1605157224136-36" style="">
              <div class="silex-element-content normal">
                <p><b><a href="#!page-profile" class="page-link-active">프로필</a></b></p>
              </div>
            </div>
          </div>
        </div>
        <div data-silex-type="container-element" class="editable-style container-element silex-id-1605168439863-17" data-silex-id="silex-id-1605168439863-17">
          
        </div>
    </body>
    </html>
    `;
    res.writeHead(200);
    res.end(template);

});
