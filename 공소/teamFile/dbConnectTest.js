
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
// ```
// CREATE TABLE fileLocation
// ( 
//     number int primary key, 
//     directory varchar(30), 
//     fileName varchar(30)
// );


// insert into fileLocation (number, directory, fileName) VALUE
// (
//     1,
//     "C:\Users\wlska\Documents\junior_2semester\공소\teamFile",
//     "testFile"
// );
// ```