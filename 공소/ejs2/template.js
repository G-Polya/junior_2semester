var style = require("./style.js");

module.exports = {
  HTML: function (course, getfiles, db, group, username) {
    // return `
    // <!doctype html>
    // <head>
    // <meta charset="UTF-8">
    // <title></title>
    // ${style.css()}
    // </head>
    // <body>
    // ${getfiles}
    // <div class=origin>
    //     <form action="myrouter/addpart" method="post">
    //     <input type="text" name="part">
    //     <input type="submit" value="파트추가">
    //     </form>
    // </div>
    // <div class=origin>
    //     ${db}
    // </div>
    // </body>
    // </html>
    // `;
    return `

<!DOCTYPE html>
<html>
  <title>W3.CSS Template</title>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=device-width, initial-scale=1" />
  <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css" />

  <link
    rel="stylesheet"
    href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css"
  />
  <script src="https://use.fontawesome.com/releases/v5.2.0/js/all.js"></script>
${style.css()}
  <style>
    body {
      color: white;
      font-family: "Roboto", sans-serif;
      background-color: black;
    }
    html,
    body,
    h1,
    h2,
    h3,
    h4,
    h5 {
      color: white;
      font-family: "Roboto", sans-serif;
    }
    #mySidebar {
      background-color: rgba(38, 38, 39, 1);
    }
    #logo {
      width: 135px;
      height: 125px;
      top: 50px;
      left: 60px;
    }
    #logotext {
      font-weight: bold;
      font-size: 32px;
    }
    table {
      width:40%;
      border: 2px solid;
      border-color: white;
    }

    .silex-id-1605169710227-28 {width: 200px; min-height: 70px; position: absolute; top: 194px; left: 15px; background-color: transparent;}
    .silex-id-1605169710227-29 {width: 500px; height: 500px; position: absolute; top: 00px; left: 94%;}
  </style>
  <body>
    <div data-silex-type="image-element" class="editable-style image-element silex-id-1605169710227-29 page-main paged-element style-all-style1" data-silex-id="silex-id-1605169710227-29" style="" data-silex-href="#!page-main">
          <label>${username}</label>
    </div>
    <!-- Sidebar/menu -->
    <nav
      class="w3-sidebar w3-collapse"
      style="z-index: 3; width: 270px"
      id="mySidebar"
    >
      <br />
      <div class="w3-container w3-row">
        <img src="logo.637cfd18.jpg" id="logo" />
        <div id="logotext">
          <a href="/home">
            PLASS DGU
          </a>  
        </div>
        <div data-silex-type="text-element" class="editable-style text-element silex-id-1605169710227-28 page-main paged-element style-all-style1" data-silex-id="silex-id-1605169710227-28" style="">
            <select name="course" onchange="location=this.value;">
                <option value="select-course" > 강좌를 선택하세요 </option>
                ${course}
            </select>
        </div>

        <br />
        
        <a href="#" class="w3-bar-item w3-button"><i class="fa fa-envelope"></i></a>
        <a href="#" class="w3-bar-item w3-button"><i class="fa fa-user"></i></a>
        <a href="#" class="w3-bar-item w3-button"><i class="fa fa-cog"></i></a>
      </div>

  

      <hr />

      <div class="w3-bar-block">
        <a href="/teamPage" class="w3-bar-item w3-button w3-padding"
          ><i class="fa fa-users fa-fw"></i><b>공동문서작업</b>
        </a>
        <a href="/teamPage" class="w3-bar-item w3-button w3-padding">-Group정보</a>
        <a href="/workList" class="w3-bar-item w3-button w3-padding">-작업리스트</a>
        <a href="/fileUpload" class="w3-bar-item w3-button w3-padding w3-blue">-파일업로드</a>
        <br />

        <a href="/rate" class="w3-bar-item w3-button w3-padding"
          ><i class="far fa-star fa-fw"></i><b>평가하기</b> </a
        >
        <a href="/scoreboard" class="w3-bar-item w3-button w3-padding"
          ><i class="far fa-clipboard fa-fw"></i><b>평가점수표</b> </a
        >
      </div>
    </nav>

    <!-- Overlay effect when opening sidebar on small screens -->
    <div
      class="w3-overlay w3-hide-large w3-animate-opacity"
      onclick="w3_close()"
      style="cursor: pointer"
      title="close side menu"
      id="myOverlay"
    ></div>

    <!-- !PAGE CONTENT! -->
    <div class="w3-main w3-black" style="margin-left: 270px">
      <!-- Header -->
      <header class="w3-container" style="padding-top: 22px">
        <h5>
          <b> <i class="far fa-folder-open"></i> 파일업로드</b>
        </h5>
      </header>


      <div class="w3-row-padding w3-margin-top">
      <div style="color:white; font-size:40px; margin-left:40%; margin-top:5%"><b>공동 문서 작업</b></div>
                  <div style="position:relative; top:50px;">
                      ${getfiles}
                      <div class=origin>
                       <br>
                      </div>
                      <div class=origin>
                          <form action="myrouter/addpart/${group}" method="post">
                              <input type="text" name="part" size=8 maxlength=8>
                              <input type="submit" value="파트추가">
                          </form>
                      </div>
                  </div>
              </div>
        </div>
      </div>

      ${db}
  </body>
</html>

  `;
  },
};
