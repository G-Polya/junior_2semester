//const jsdom = require('mocha-jsdom');
//global.document = jsdom({url:"http://localhost"});
const mariadb = require('mariadb/callback');
const pool = mariadb.createPool({ 
    host: 'localhost', 
    user: 'root',
    password: '',
    database:'moodle',
    connectionLimit: 1 
});

// function buildTable(data) {
//     let table = document.getElementById('table1');

//     for(let i = 0; i < data.length; i++)
//     {
//         let row = `<tr>
//                     <td>${data[i].id}</td>
//                     <td>${data[i].firstname}</td>
//                     <td>${data[i].lastname}</td>
//                    <tr>}`
//         table.innerHTML += row;
//     }
// }

pool.getConnection((err, conn) => {
  if (err) throw err;

    console.log("connected ! connection id is " + conn.threadId);
    var temp2;
    let sql = "SELECT mdl_user.id, mdl_user.firstname, mdl_user.lastname FROM mdl_groups_members INNER JOIN mdl_user ON mdl_groups_members.userid = mdl_user.id;"
    let name;
    let temp = conn.query(sql,(err, result, fields)=>{
        if(err) throw err;
        
        //buildTable(result);
        console.log(result);
        
    });
		
	 
    
    conn.end(); //release to pool
});