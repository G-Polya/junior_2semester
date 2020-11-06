const mariadb = require('mariadb/callback');
const pool = mariadb.createPool({ 
    host: 'localhost', 
    user: 'root',
    password: '',
    database:'moodle',
    connectionLimit: 1 });

pool.getConnection((err, conn) => {
  if (err) throw err;

    console.log("connected ! connection id is " + conn.threadId);
    
    conn.query("select * from fileLocation",(err, result, fields)=>{
        if(err) throw err;
        console.log(result);
    });

    conn.end(); //release to pool
});