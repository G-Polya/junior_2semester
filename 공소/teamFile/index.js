const mariadb = require('mariadb/callback');
const conn = mariadb.createConnection({
      host: 'localhost', 
      user:'root',
      password: '',
      database: 'nodejs_test'
    });
conn.connect(err => {
  if (err) throw err;
  conn.query("select * from users", (err, result, fields)=>{
      if(err) throw err;
      console.log(result);
  });
});