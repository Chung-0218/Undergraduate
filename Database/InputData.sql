USE reservation;

insert into company values ('Konkuk', '02-450-3114', 'konkuk@konkuk.ac.kr', '서울 광진구 능동로 120');

insert into client values ('C1', '이지금', '970101', '010-1234-5678', '일산서구 주엽동', 'gold01@naver.com', '1111');
insert into client values ('C2', '이지은', '970102', '010-1234-5679', '일산서구 대화동', 'silver02@naver.com', '2222');
insert into client values ('C3', '이지동', '970103', '010-1234-5670', '일산서구 백석동', 'bronze03@naver.com', '3333');

insert into owner values ('O1', '김주인', 'Konkuk', '010-1111-2222', '4444', 'kin@naver.com', '5555');
insert into owner values ('O2', '이주인', 'Konkuk', '010-3333-4444', '6666', 'kin@naver.com', '7777');

insert into establish_name values ('O1', '부산호텔', '부산');
insert into establish_name values ('O2', '제주호텔', '제주도');

insert into establish_info values ('C1-O1', '부산', '스위트룸', '4', '50000');
insert into establish_info values ('C2-O2', '제주도', '스위트룸', '6', '80000');

insert into reservation values ('R1', 'C1-O1', 'C1', '2021-06-14', '2021-06-17', 3, 150000);
insert into reservation values ('R2', 'C1-O1', 'C2', '2021-06-16', '2021-06-19', 4, 200000);
insert into reservation values ('R3', 'C2-O2', 'C3', '2021-06-21', '2021-06-23', 6, 480000);
