select first_name, last_name, salary, department_id from employees where (department_id=30 or department_id=100) and (salary not between 10000 and 15000);