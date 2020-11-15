const express    = require('express');
const mariadb      = require('mariadb/callback');
const dbconfig   = require('./config/database.js');
const connection = mariadb.createConnection(dbconfig);

const app = express();

// configuration =========================
app.set('port', process.env.PORT || 3000);

app.get('/', (req, res) => {
  res.send('Root');
});


var db = []
app.get('/users', async (req, res) => {
      
  //const p = document.createElement('p');
  db = connection.query('SELECT username FROM mdl_user', (error, rows) => {
    if (error) throw error;


    res.send(db);
    console.log(rows)
    return rows;
  }).rows;

  // query 객체 출력
  console.log(db);
  
  
});

//async console.log("db 4: "+db);

app.listen(app.get('port'), () => {
  console.log('Express server listening on port ' + app.get('port'));
});


