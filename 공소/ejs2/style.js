module.exports={
    css:function(){
        return `
        <style>
                .listcontent{
                    width:100%; 
                    clear:both;
                    height: 25px; 
                    font-size:70%;
                } 
                .link{
                    float:left;
                    position: relative;
                    bottom:-15px;
                    width:2%;
                }
                .titlefont{
                    color:white;
                }
                .listfont{
                    display : block;
                    text-overflow: ellipsis;
                    white-space: nowrap;
                    color:white;
                    font-size:30%; 
                    overflow:hidden;  
                }
                .check{
                    left: 1px;
                }
                .origin{
                    clear:both;
                }
                .vertical2{
                    border-left:6px solid white;
                    position:relative;
                    height: 10px;
                    left: 50%;
                    margin-left:-3px;
                    top:0;
                }
                .left{
                    float:left;
                }
                .part{
                    float:left;
                    width:15%;
                }
                .parttitle{
                    clear:both;
                    border:3px solid white;
                    vertical-align:middle;
                    font-size:100%;
                }
                .partupload{
                    clear:both;
                    border:3px solid white;
                }
                .horizontal{
                    float:left;
                    background-color:white;
                    widht:100%;
                    height:100%;
                }
            </style>
        `;
    }
    
}

// .parttitle{
//     background-color:#50bcdf;
//     clear:both;
//     border:1px solid white;
// }

// .partupload{
//     background-color:#fbceb1;
//     clear:both;
//     border:1px solid white;
// }