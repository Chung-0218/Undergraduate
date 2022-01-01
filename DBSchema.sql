USE reservation;

create table company (
com_name varchar(40) primary key,
com_tele varchar(30),
com_mail varchar(50),
com_location varchar(70)
);

create table client (
cli_num varchar(30) primary key,
cli_name varchar(30),
cli_birth varchar(30),
cli_phone varchar(30),
cli_address varchar(70),
cli_mail varchar(50),
cli_password varchar(30)
);

create table owner (
owner_num varchar(30) primary key,
owner_name varchar(30),
owner_company_name varchar(40),
owner_phone varchar(30),
owner_business_num varchar(30),
owner_mail varchar(50),
owner_password varchar(30)
);

create table establish_name (
owner_num varchar(30),
est_name varchar(50),
est_location varchar(80),
primary key (est_location),
foreign key (owner_num) references owner(owner_num) on delete cascade
);

create table establish_info (
serial_num varchar(30) primary key,
est_location varchar(80),
room_type varchar(30),
room_num varchar(30),
pay varchar(30),
foreign key (est_location) references establish_name(est_location) on delete cascade
);

create table reservation (
reser_num varchar(30) primary key,
serial_num varchar(30),
cli_num varchar(30),
reser_start date,
reser_fin date,
customer_num varchar(10),
pay varchar(30),
foreign key (serial_num) references establish_info(serial_num) on delete cascade,
foreign key (cli_num) references client(cli_num) on delete cascade
);