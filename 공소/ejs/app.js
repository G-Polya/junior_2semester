const express = require('express')
const app = express()
const db_config = require(__dirname+'/config/database.js')
const conn = db_config.init()
const bodyParser = require('body-parser')
const e = require('express')

db_config.connect(conn);

app.set('views', __dirname+'/views')
app.set('view engine', 'ejs')

app.use(bodyParser.json())
app.use(bodyParser.urlencoded({extended:false}))

app.get('/', function(req,res){
    //const body = req.body
    res.send("root")
})


app.get('/team', function(req,res){
    let sql = `select mdl_groups.name,groupid, firstname, lastname
               from mdl_groups_members, mdl_user,mdl_groups
               where mdl_groups_members.userid = mdl_user.id and 
                     mdl_groups_members.groupid=1 and 
                     mdl_groups_members.groupid = mdl_groups.id;
    `
    const names = []
    //const lastNames = []
    conn.query(sql, function(err, rows, fields){
        if(err) console.log('query is not excuted. select fail...\n'+err)
        else {
            rows.forEach((element)=>{
                names.push(element.firstname+element.lastname)
            })
            console.log(rows[0].name)
            res.render('team.ejs', {memberName:names,groupName:rows[0].name})
        }
    })


})


app.post('/store', function(req, res){
    let temp = req.body;
    console.log(temp.memo);
    req.body.memo = temp.memo
    console.log(req.body.memo)

})

app.listen(3200, ()=>console.log('Sever is running on port 3200...'))