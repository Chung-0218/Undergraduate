USE university

# 문제 3.1

# b)
select distinct student.id
from (student join takes using(id))
	  join (instructor join teaches using(id))
	  using (course_id, sec_id, semester, year)
where instructor.name = 'Einstein';

# d)
select id, name from instructor
where salary = (select max(salary) from instructor);

# e)
select course_id, sec_id, count(id)
from section natural join takes
where semester = 'Autumn' and year = 2009
group by course_id, sec_id;

# f)
select max(enrollment) from (select count(id) as enrollment
from section natural join takes
where semester = 'Autumn' and year = 2009
group by course_id, sec_id)A;

# g)
with sec_enrollment as( select course_id, sec_id, count(id) as enrollment
from section natural join takes where semester = 'Autumn' and year = 2009
group by course_id, sec_id)
select course_id, sec_id from sec_enrollment
where enrollment = (select max(enrollment) from sec_enrollment);

# 문제 3.2

# a)
(select sum(credits * points)
from takes, course, grade_points where takes.grade = grade_points.grade
and takes.course_id = course.course_id and id = '12345')
union (select 0 from student where id = '12345'
and not exists (select * from takes where id = '12345'));

# b)
select sum(credits * points) / sum(credits) as GPA
from takes, course, grade_points
where takes.grade = grade_points.grade
and takes.course_id = course.course_id and id = '12345';

# c)
select id, sum(credits * points) / sum(credits) as GPA
from takes, course, grade_points
where takes.grade = grade_points.grade
and takes.course_id = course.course_id group by id
union (select id, null as GPA from student
where not exists (select * from takes where takes.id = student.id));


# 문제 3.11

# a)
select distinct name, id from student natural join takes
natural join course where dept_name = 'Comp. Sci.';

# b)
select id, name from student where not exists
(select id, name from student natural join takes where year < 2009);

# c)
select dept_name, max(salary) from instructor
group by dept_name;

# d)
select min(Minimum_Salary) from (select dept_name, max(salary)
Minimum_Salary from instructor group by dept_name)A;


USE scott

# 4.
select ename, sal from emp where sal >= 2850;

# 5.
select ename, deptno from emp where empno = 7566;

# 6.
select ename, sal from emp where sal > 2850 or sal < 1500;

# 7.
select ename, deptno from emp where deptno = 10 or deptno = 30
order by ename asc;

# 8.
select ename, sal from emp where (deptno = 10 or deptno = 30) and sal >= 1500;

# 9.
select ename, job from emp where mgr is NULL;

# 10.
select ename, sal, comm from emp order by comm asc, sal asc;

# 11.
select ename from emp where locate('A', ename) = 3 ;

# 12.
select ename from emp where mgr = 7782 or deptno = 30
and ename - replace(ename, 'L', '') = 2;

# 13.
select ename, job, sal from emp where job = 'Clerk' or job = 'Analyst'
and sal not in(1000, 3000, 5000);

# 14.
select empno, ename, sal, (sal * 1.15) as New_Sal,
round(sal / 100 * 15, 0) as Increase from emp;

# 15.
select ename, ifnull(comm , 'No Commission') as comm from emp;

# 16.
select job, loc from emp, dept where emp.deptno = 30;

# 17.
select ename, dname, loc from emp, dept where emp.comm > 0;

# 18.
select ename, job, emp.deptno, dname from emp, dept 
where dept.loc = 'Dallas';

# 19.
select ename, empno, mgr_ename, mgr_empno from emp left outer join
(select ename mgr_ename, empno mgr_empno from emp
where job = 'Manager') mgr on emp.empno = mgr_empno;

# 20.
select ename, hiredate from emp
where hiredate < (select hiredate from emp where ename = 'Blake');

# 21.
select e.ename 'Employee', e.hiredate 'EmpHiredate', m.ename 'Manager', m.hiredate 'MgrHiredate'
from emp e join emp m on e.mgr = m.empno
where e.hiredate < m.hiredate;

# 22.
select max(sal), min(sal), sum(sal), avg(sal)
from emp group by job;

# 23.
select job, count(empno) from emp group by job;

# 24.
select count(ename) from emp where mgr is not NULL;

# 25.
select ename, min(sal) from emp where ename is not NULL
group by ename having min(sal) >= 1000 order by min(sal) desc;

# 26.
select dname, loc, count(dname), round(avg(sal), 2) 'Average' 
from dept, emp group by dname, loc;

# 27.
select distinct ename, hiredate from dept, emp
where not(ename = 'Blake') and (select deptno from emp
where ename = 'Blake');

# 28.
select ename, sal from emp where sal > (select avg(sal) from emp)
order by sal desc;

# 29.
select empno, ename, job from emp, dept
where loc = 'Dallas';

# 30.
select b.ename, b.sal from emp a, emp b
where a.ename = 'King' and a.empno = b.mgr;
