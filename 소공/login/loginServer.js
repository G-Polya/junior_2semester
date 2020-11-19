const mysql      = require('mysql');
const dbconfig   = require('./config/database.js');
const connection = mysql.createConnection(dbconfig);
const express = require('express')
const app = express()
const http = require('http')

app.set('port', 3100);
const server = http.createServer(app).listen(app.get('port'))


let sequenceNumberByClient = new Map();

server.on("connection", (socket)=>{
    console.info(`Client connected [id=${socket.id}]`);
    sequenceNumberByClient.set(socket,1);

    socket.on("disconnect", ()=>{
        sequenceNumberByClient.delete(socket);
        console.info(`Client gone [id=${socekt.id}]`)
    })
})

setInterval(() =>{
    for(const [client, sequenceNumber] of sequenceNumberByClient.entries()){
        client.emit("seq-num", sequenceNumber);
        sequenceNumberByClient.set(client, sequenceNumber+1);
    }
},1000);



// const mariadb = require('mariadb/callback');
// const pool = mariadb.createPool({
//     host:'localhost',
//     user:'root',
//     password:'',
//     database : 'nodejs_test',
//     connectionLimit:1
// });

// pool.getConnection((err, conn) => {
//     if (err) throw err;
  
//       console.log("connected ! connection id is " + conn.threadId);
      
//       let idQuery = conn.query("select * from account", (err, result)=>{
//           if(err) throw err;
          
//       });
  
//       conn.end(); //release to pool
//   });