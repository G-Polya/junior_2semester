
|_course1(tst, courseid: 5)
      |_ ParkSungHo (userid:8)            >> teacher skyss1234
  |_ group1(groupid:1)
      |_ KimHeeSu2  (userid:3) >> 팀장  tollea1235
      |_ KimHeeSu3  (userid:4) >> 학생  tollea1236
      |_ ParkMinSu  (userid:6) 
      |_ ParkMinSu2 (userid:7)
      |_ ParkMinSu3 (userid:9)
  |_ group2(groupid:2)
      
      |_ KimHeeSu   (userid:2)            >> 팀장 tollea1234
      |_ ParkSungHo2(userid:10)           >> 학생 sunday1235
      |_ ParkSungHo3 (userid:11) 
      |_ ParkSungHo4 (userid:12)
      |_ ParkSungHo5 (userid:13) 
  |_ group3(groupid:3)    
      |_ KimSungSu  (userid:14)           >> 팀장 honoka1234
      |_ KimSungSu2 (userid:15)           >> 학생 honoka1235
      |_ KimSungSu3  (userid:16)
      |_ KimSungSu4  (userid:17)          
      |_ KimSungSu5  (userid:18)               
|_course2(tst2, courseid: 7)     
  |_ tst2Group2(groupid:4)
      |_ LeeSungHo  (userid:5) >> 팀장 skyss1234
      |_ KimHeeSu2  (userid:3) >> 학생 tollea1235
      |_ LeeSungHo2  
      |_ LeeSungHo3  
      |_ LeeSungHo4  
      

과목 2개 듣는 사람이 각 과목의 그룹에 접근 >> KimHeeSu2

db에 추가한것
mdl_groups_members테이블에 작업리스트의 작성을 위한 to_do_list 칼럼추가
mdl_groups에 파일이 저장될 경로가 되는 group_path 칼럼추가
mdl_groups_member에 hasrated(int, null) 추가
create table a_rate
(
    userid int(20), 
    leadership float, 
    teamwork float, 
    creativeness float, 
    assertiveness float, 
    orator float, 
    courseid int
);