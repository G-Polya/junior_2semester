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

app.get('/work', function(req,res){
    res.render('work.ejs')
})


app.get('/team', function(req,res){
    const sql = `select mdl_user.firstname, mdl_user.lastname 
                 from mdl_user
                 inner join mdl_groups_members on mdl_user.id=mdl_groups_members.userid;`
    const names = []
    //const lastNames = []
    conn.query(sql, function(err, rows, fields){
        if(err) console.log('query is not excuted. select fail...\n'+err)
        else {
            rows.forEach((element)=>{
                names.push(element.firstname+element.lastname)
            })
            //console.log(names)
            res.render('team.ejs', {memberName:names})
        }
    })
})

app.listen(3200, ()=>console.log('Sever is running on port 3200...'))