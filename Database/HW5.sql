USE HW5;

# 1.

create table employee (employee_name varchar(30) not NULL,
street varchar(30) not NULL, city varchar(30) not NULL,
constraint PK_employee_name primary key (employee_name));

create table company (company_name varchar(30) not NULL,
city varchar(30) not NULL,
constraint PK_company_name primary key (company_name));

create table manages (employee_name varchar(30) not NULL,
manager_name varchar(30) not NULL,
constraint PK_employee_manager primary key (employee_name, manager_name),
foreign key (employee_name) references employee (employee_name),
foreign key (manager_name) references employee (employee_name));

create table works (employee_name varchar(30) not NULL,
company_name varchar(50) not NULL, salary numeric(10, 2) not NULL,
constraint PK_emp_company primary key (employee_name, company_name));

alter table works add constraint FK_works_company foreign key (company_name)
references company (company_name);

alter table works add constraint FK_works_employee foreign key (employee_name)
references employee (employee_name);

show tables;

# 2. 

insert into employee values('Mike', 'Street1', 'London');
insert into employee values('John', 'Street2', 'Paris');
insert into employee values('Olivia', 'Street3', 'NewYork');
insert into employee values('Emma', 'Street1', 'London');
insert into employee values('Jessica', 'Street2', 'Paris');
insert into employee values('Daniel', 'Street3', 'NewYork');
insert into employee values('Kim', 'Street4', 'Seoul');
insert into employee values('Luna', 'Street1', 'London');
insert into employee values('Jones', 'Street5', 'Paris');

insert into company values('First Bank Corporation', 'London');
insert into company values('Second Bank Corporation', 'Paris');
insert into company values('Third Bank Corporation', 'NewYork');
insert into company values('Small Bank Corporation', 'Seoul');

insert into manages values('Mike', 'Emma');
insert into manages values('Olivia', 'Emma');
insert into manages values('Daniel', 'John');
insert into manages values('Jessica', 'Kim');

insert into works values('Mike', 'First Bank Corporation', 13500.50);
insert into works values('John', 'Second Bank Corporation', 21000.25);
insert into works values('Olivia', 'Third Bank Corporation', 15000.00);
insert into works values('Emma', 'First Bank Corporation', 18500.50);
insert into works values('Jessica', 'Second Bank Corporation', 8500.00);
insert into works values('Daniel', 'Third Bank Corporation', 9900.50);
insert into works values('Kim', 'Small Bank Corporation', 14000.25);
insert into works values('Luna', 'First Bank Corporation', 12000.50);

# 3.

# 3.9

# a)
select employee_name from works where company_name = 'First Bank Corporation';

# b)
select * from employee where employee_name in
(select employee_name from works where company_name = 'First Bank Corporation'
and salary > 10000);

# c)
select employee_name from works where not company_name = 'First Bank Corporation';

# d) 
select employee_name from works where salary > all
(select salary from works where company_name = 'Small Bank Corporation');

# e) (company 테이블에서 company_name가 PK라서 회사들이 여러 도시에 있을 수가 없음...?)
select company_name,city from company where city in
(select city  from company 
where company_name='Small Bank Corporation');

# f)
select company_name from works group by company_name
having count(distinct employee_name) >= all
(select count(distinct employee_name) from works group by company_name);

# g)
select company_name from works group by company_name
having avg(salary) > (select avg(salary) from works
where company_name = 'First Bank Corporation');

# 3.10

# a)
update employee set city = 'Newton' where employee_name = 'Jones';
select employee_name, city from employee where employee_name = 'Jones';

# b) (기준을 $20000로 바꿈)
update works F set F.salary = F.salary * 1.03 where F.employee_name in
(select manager_name from manages) and F.salary * 1.1 > 20000
and F.company_name = 'First Bank Corporation';

update works F set F.salary = F.salary * 1.1 where F.employee_name in
(select manager_name from manages) and F.salary * 1.1 <= 20000
and F.company_name = 'First Bank Corporation';

select employee_name, salary from works;

# 3.16

# a)
select employee_name from works where company_name = 'First Bank Corporation';

# b)
select e.employee_name from employee as e, works as w, company as c
where e.employee_name = w.employee_name and e.city = c.city
and w.company_name = c.company_name;

# c)
select e1.employee_name from employee e1, employee e2, manages
where e1.employee_name = manages.employee_name
and e2.employee_name = manages.manager_name
and e1.street = e2.street and e1.city = e2.city;

# d)
select employee_name from works group by company_name, employee_name
having avg(salary) > (select avg(salary) from works
where company_name is not NULL);

# e)
select company_name from works group by company_name
order by sum(salary) limit 1;

# 3.17

# a)
update works set salary = salary * 1.1
where company_name = 'First Bank Corporation';
select employee_name, salary as New_salary from works;

# b)
update works set salary = salary * 1.1
where employee_name in (select manager_name from manages
where company_name = 'First Bank Corporation');
select employee_name, salary as New_salary from works;

# c)
delete from works
where company_name = 'Small Bank Corporation';
select employee_name, company_name from works;