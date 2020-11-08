const mariadb = require('mariadb/callback');
const pool = mariadb.createPool({ 
    host: 'localhost', 
    user: 'root',
    password: '',
    database:'nodejs_test',
    connectionLimit: 1 });

pool.getConnection((err, conn) => {
  if (err) throw err;

    console.log("connected ! connection id is " + conn.threadId);
    
    let temp = conn.query("select * from users",(err, result, fields)=>{
        if(err) throw err;
        console.log(result); // 이 부분을 return result로 한 후
    });
		
		console.log(temp) // 이러면 undefined 뜸..
	

    conn.end(); //release to pool
});