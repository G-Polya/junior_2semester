
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
    var temp2;
    let temp = conn.query("select * from fileLocation",(err, result, fields)=>{
        if(err) throw err;
     
        temp2=result
    });
		
		console.log(temp2) 

    conn.end(); //release to pool
});
