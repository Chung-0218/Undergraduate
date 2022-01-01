USE library;

create table 학생 (
학번 int(10) primary key,
학과 varchar(30),
이름 varchar(30),
이메일 varchar(50),
연체횟수 int(10)
);

create table 교수 (
사번 int(10) primary key,
학과 varchar(30),
이름 varchar(30),
이메일 varchar(50),
연체횟수 int(10)
);

create table 도서 (
도서번호 int(20) primary key,
제목 varchar(30),
저자 varchar(30),
권수 int(10),
대출가능여부 varchar(10)
);

create table 대출도서 (
도서번호 int(20) primary key,
대출일자 varchar(30),
반납일자 varchar(30),
foreign key (도서번호) references 도서(도서번호) on delete cascade
);

create table 대출예약 (
도서번호 int(20) primary key,
예약신청일자 varchar(30),
반납일자 varchar(30),
foreign key (도서번호) references 도서(도서번호) on delete cascade
);

create table 대출연장 (
도서번호 int(20) primary key,
대출일자 varchar(30),
반납일자 varchar(30),
연장여부 varchar(10),
연장횟수 int(10),
foreign key (도서번호) references 도서(도서번호) on delete cascade
);