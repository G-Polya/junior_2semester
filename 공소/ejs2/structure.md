
|_course1(tst, courseid: 5)
  |_ group1(groupid:1)
      |_ KimHeeSu   (userid:2)
      |_ KimHeeSu2  (userid:3)
      |_ KimHeeSu3  (userid:4)
      |_ ParkMinSu  (userid:6)
      |_ ParkMinSu2 (userid:7)
  |_ group2(groupid:2)
      |_ ParkSungHo (userid:8)
|_course2(tst2, courseid: 7)
  |_ tst2Group1(groupid:3)
      |_ KimHeeSu2  (userid:3)
  |_ tst2Group2(groupid:4)
      |_ LeeSungHo  (userid:5)


과목 2개 듣는 사람이 각 과목의 그룹에 접근 >> KimHeeSu2

db에 추가한것
mdl_groups_members테이블에 작업리스트의 작성을 위한 to_do_list 칼럼추가
mdl_groups에 파일이 저장될 경로가 되는 group_path 칼럼추가