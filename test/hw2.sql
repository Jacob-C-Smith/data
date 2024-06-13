-- TODO: Continue with this assignment only after completing HW2_Part1_Reading on Canvas.

-- =========
-- HW2_Part1
-- ---------
-- Execute each SQL statement below, in sequential order, and
-- answer the corresponding question in HW2_Part1 on Canvas.

-- NOTE:
--   If you ever want to "reset" the database and start from scratch,
--   execute all SQL statements, in sequential order, from the top of this file.
-- =========

DROP TABLE IF EXISTS registered_students;
DROP TABLE IF EXISTS classes;
DROP TABLE IF EXISTS students;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CREATE TABLE classes
(
    id           INTEGER PRIMARY KEY AUTOINCREMENT,
    code         VARCHAR(10) UNIQUE,
    title        VARCHAR(50) NOT NULL,
    description  VARCHAR(200),
    max_students INTEGER DEFAULT 10
);

CREATE TABLE students
(
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    first_name VARCHAR(30) NOT NULL,
    last_name  VARCHAR(50) NOT NULL,
    birth_date DATE
);

INSERT INTO classes (code, title'CS 410', 'Databases');

SELECT *
FROM classes;
-- 💡 HINT:
-- Pin the results tab for the classes table, so you can always refer back to the table contents as you make changes
-- 📖 DataGrip/IntelliJ IDEA Pin tab documentation: https://www.jetbrains.com/help/datagrip/viewing-query-results.html#pin_result_tab

-- Canvas: Answer question Q1

-- Canvas: Answer question Q2

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- ❗ Expect an error when you run this INSERT statement.
INSERT INTO classes (code, title'CS 410', 'CS 410 SQL');

-- Canvas: Answer question Q3
-- After answering Q3 on Canvas about the error, comment out the above INSERT statement.


-- Canvas: Answer question Q4

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

INSERT INTO classes (title'CS 408 Web Development');

INSERT INTO classes (title'CS 402 Mobile Development');

-- 💡 HINT:
-- Refresh the content of the classes table to see the newly inserted rows.
-- Throughout this file, please remember to refresh the table contents after each SQL statement to see the changes.

-- Canvas: Answer question Q5

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- ❗ Expect an error when you run this INSERT statement.
INSERT INTO classes (code'CS 208');

-- Canvas: Answer question Q6
-- After answering Q6 on Canvas about the error, comment out the above INSERT statement.

-- Canvas: Answer question Q7

-- Canvas: Answer question Q8

-- Canvas: Answer question Q9

-- Canvas: Answer question Q10

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

first_name, last_name, birth_date'Alice', 'Agnesi', '1991-01-01');

first_name, last_name, birth_date'Bob', 'Babbage', '1992-02-02');

first_name, last_name, birth_date'Carol', 'Carson', '1993-03-03');

first_name, last_name, birth_date'Daniel', 'Dijkstra', '1994-04-04');

first_name, last_name, birth_date'Emmett', 'Einstein', '1995-05-05');

first_name, last_name, birth_date'Fiona', 'Faraday', '1996-06-06');

first_name, last_name, birth_date'George', 'Galois', '1997-07-07');

first_name, last_name, birth_date'Hannah', 'Hamilton', '1998-08-08');

first_name, last_name, birth_date'Isaac', 'Ishizaka', '1999-09-09');

first_name, last_name, birth_date'Jessica', 'Jackson', '2000-10-10');

first_name, last_name, birth_date'Wilbur', 'Wright', '1867-04-16');

first_name, last_name, birth_date'Walter', 'Wu', '1912-05-31');

SELECT *
FROM students;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SELECT *
FROM students
WHERE first_name = 'Alice';

SELECT *
FROM students
WHERE first_name = 'ALICE';

-- Canvas: Answer question Q11

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- 📖 SUBSTR function documentation: https://www.sqlitetutorial.net/sqlite-functions/sqlite-substr/
SELECT SUBSTR(code, 1, 3) AS mystery_column, code, id, title
FROM classes;

-- Canvas: Answer question Q12

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- Let's fix the rows with invalid data in classes
-- 📖 LIKE function documentation: https://www.sqlitetutorial.net/sqlite-like/
UPDATE classes
SET code = 'CS 408'
WHERE title LIKE '%CS 408%';

UPDATE classes
SET title = 'Full Stack Web Development'
WHERE code = 'CS 408';


/*
Uncomment and complete the following 2 UPDATE statements to change the row with title 'CS 402 Mobile Development' as follows:
  - set the new code: 'CS 402' (from null)
  - set the new title: 'Mobile Application Development' (from 'CS 402 Mobile Development')
*/
-- UPDATE classes
-- TBD_complete_this_statement

-- UPDATE classes
-- TBD_complete_this_statement

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- Let's update the course descriptions
UPDATE classes
SET description = 'Foundations of database management systems...'
WHERE code = 'CS 410';

UPDATE classes
SET description = 'Learn how to apply various technologies used for client-side and server-side web development...'
WHERE code = 'CS 408';

UPDATE classes
SET description = 'A project-intensive course on mobile development using either iOS or Android as a platform...'
WHERE code = 'CS 402';

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Write a DELETE statement to delete all students born before '1900-01-01' or those that have a 'w' in their last name

📖 SQLite AND and OR clauses documentation: https://www.tutorialspoint.com/sqlite/sqlite_and_or_clauses.htm

💡 HINT:
  - start by writing a "SELECT *" statement that satisfies the conditions
  - after you get the expected results for the SELECT statement, replace the "SELECT *" with "DELETE"
*/
--TODO: add your DELETE statement here


-- Canvas: Answer question Q13

-- ================
-- End of HW2_Part1
-- ================

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- TODO: Complete HW2_Part2_Reading on Canvas.

-- TODO: Continue with HW2_Part2 below.

-- =========
-- HW2_Part2
-- ---------
-- Execute each SQL statement below, in sequential order, and
-- answer the corresponding question in HW2_Part2 on Canvas.

-- NOTE:
--   If you ever want to "reset" the database and start from scratch,
--   execute all SQL statements, in sequential order, from the top of this file.
-- =========

CREATE TABLE registered_students
(
    id         INTEGER PRIMARY KEY AUTOINCREMENT,
    class_id   INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    FOREIGN KEY (class_id) REFERENCES classes (id),
    FOREIGN KEY (student_id) REFERENCES students (id)
);

-- 📖 SQLite CURRENT_TIMESTAMP documentation: https://www.sqlitetutorial.net/sqlite-date-functions/sqlite-datetime-function/
ALTER TABLE registered_students
    ADD COLUMN signup_timestamp DATETIME DEFAULT CURRENT_TIMESTAMP;

-- Canvas: Answer question Q14

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- Selecting primitives results in returning (or "echo-ing") those values
SELECT 123, 'abc';

-- Aliases demo for column names
SELECT 123 AS column1, 'abc' AS column2;


-- values 5 and 7 are "echo-ed" and inserted into the registered_students table
-- this is referred to as an "INSERT INTO SELECT" statement
INSERT INTO registered_students(class_id, student_id)
SELECT 5, 7;

SELECT *
FROM registered_students;

-- Canvas: Answer question Q15

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- In the query below, LIKE selects students who have letter 'i' (or 'I') in their name (the comparison is case insensitive)
-- NOTE: value 8 is "echo-ed" and "repeated" for each row
SELECT 8, id, first_name
FROM students
WHERE first_name LIKE '%i%';

INSERT INTO registered_students(class_id, student_id)
SELECT 8, id
FROM students
WHERE first_name LIKE '%i%';

-- Canvas: Answer question Q16

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
💡 HINT: there are 3 SQL statements below
  - a SELECT sub-query from the classes table
  - a SELECT query from the students table
  - an INSERT statement in the registered_students table

💡 HINT: Before running the INSERT statement, run the SELECT statement to see what data will be inserted.
 */
INSERT INTO registered_students(class_id, student_id)
SELECT (SELECT id
        FROM classes
        WHERE code = 'CS 410'), id
FROM students
WHERE first_name LIKE '%a%';

-- Canvas: Answer question Q17

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- 📖 LENGTH function documentation: https://www.sqlitetutorial.net/sqlite-functions/sqlite-length/
SELECT (SELECT id
        FROM classes
        WHERE code = 'MATH 175'), id, last_name, LENGTH(last_name) as number_of_characters_in_last_name
FROM students
WHERE LENGTH(last_name) >= 8;

INSERT INTO registered_students(class_id, student_id)
SELECT (SELECT id
        FROM classes
        WHERE code = 'MATH 175'), id
FROM students
WHERE LENGTH(last_name) >= 8;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- Java version of concatenating strings           : first_name + ' ' + last_name
-- SQLite version of concatenating strings         : first_name || ' ' || last_name
-- Other databases version of concatenating strings: CONCAT(first_name, ' ', last_name)

-- 📖 LOWER function documentation: https://www.sqlitetutorial.net/sqlite-functions/sqlite-lower/
SELECT first_name || ' ' || last_name AS student_full_name
FROM students
WHERE LOWER(first_name) LIKE '%c%';

/*
NOTE: even though the LOWER function coverts the first name to lowercase,
the LIKE operator ignores the case sensitivity, and returns all rows containing 'c' or 'C' in the first name.

In other words, the LOWER function is not needed in this case.

However, other databases support LIKE functions that are case sensitive and it's a good practice to use
the LOWER function in SQLite, to make it easier when migrating from SQLite to MySQL, PostgreSQL or other databases.
*/

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- The following 2 INSERT statements are equivalent.
-- This first example uses sub-queries
-- NOTE: You can either run the first one, the second one, or both.
INSERT INTO registered_students(class_id, student_id)
SELECT (SELECT id
        FROM classes
        WHERE code = 'WRITE 212'), id
FROM students
WHERE LOWER(first_name) LIKE '%r%';

-- This second example uses JOINs
INSERT INTO registered_students(class_id, student_id)
SELECT classes.id, students.id
FROM students
    INNER JOIN classes ON (code = 'WRITE 212') AND (LOWER(first_name) LIKE '%r%');

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Uncomment and complete the SELECT statement below that returns:
   - all classes which have registered students and
   - the number of students taking the class.

💡 HINTS: In the inner SELECT statement
  - use the aggregate COUNT function (https://www.sqlitetutorial.net/sqlite-count-function/)
  - use a GROUP BY clause (https://www.sqlitetutorial.net/sqlite-group-by/)
*/

-- SELECT classes.id,
--        code,
--        number_of_enrolled_students,
--        max_students
-- FROM (
--       -- TODO: finalize this inner SELECT statement
--       SELECT TBD
--
--       ) AS temp_table_with_class_id_and_number_of_enrolled_students
--          INNER JOIN classes ON classes.id = temp_table_with_class_id_and_number_of_enrolled_students.class_id
-- ORDER BY classes.id;

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Uncomment and complete the SELECT statement below that returns all classes which have no students signed up.

💡 HINTS: There are multiple possible solutions, but one of the solutions requires the use of:
  - a LEFT JOIN (https://www.sqlitetutorial.net/sqlite-left-join/) and
  - a HAVING clause (https://www.sqlitetutorial.net/sqlite-having/)
*/

-- SELECT classes.id, code, COUNT(student_id) AS number_of_students, max_students
-- FROM TBD

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Uncomment and complete the SELECT statement below that returns:
  - all students ordered by their id,
  - the classes they signed up for and
  - the date they signed up for the class

💡 HINTS:
  - use two LEFT JOIN clauses or two INNER JOIN clauses.
  - Food for thought: what is the difference between using two LEFT JOINs or using two INNER JOINs?
*/

-- SELECT
--     students.id,
--     students.first_name || ' ' || students.last_name AS full_name,
--     classes.code,
--     DATE(registered_students.signup_timestamp) AS signup_date
-- FROM TBD

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Uncomment and complete the SELECT statement below that returns all classes that have too many students
(i.e. the number of students exceeded the maximum students for the class).

💡 HINTS:
  - use a sub-query that returns a table with class_id and the number of registered_students
  - join the classes table and the sub-query table
  - use a WHERE filter on the joined tables
*/

-- SELECT classes.id, code, title, max_students, number_of_enrolled_students
-- FROM TBD

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- Let's try to register a student with id 456 (which does not exist) to a class with id 123 (which does not exist)
INSERT INTO registered_students (class_id, student_id123, 456);

-- Canvas: Answer question Q18

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- TODO: enable the enforcement of FOREIGN KEY constraints by
--       following the instructions from section 9 in the HW2 description:
--       https://docs.google.com/document/d/1XvnFOI6ssJp8IqlnhYlgu6cy_30OphGaCadxktZrbM8/edit#heading=h.xergorgytnks

-- ❗ Expect an error when you run this INSERT statement (assuming that you enabled the FOREIGN KEY constraint).
INSERT INTO registered_students (class_id, student_id-10, 208);

-- Canvas: Answer question Q19
-- After answering Q19 on Canvas about the error, comment out the above INSERT statement.

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

-- Run the following two INSERT statements
-- that are attempting to register the same student for the same class
INSERT INTO registered_students (class_id, student_id2, 3);

INSERT INTO registered_students (class_id, student_id2, 3);

-- Canvas: Answer question Q20

-- Canvas: Answer question Q21

-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*
Let's delete and recreate the registered_students table,
since the ALTER TABLE command that we would require to
add the new UNIQUE constraint is not supported in SQLite.
(https://www.sqlite.org/omitted.html)
*/
DROP TABLE IF EXISTS registered_students;

CREATE TABLE registered_students
(
    -- id         INTEGER PRIMARY KEY AUTOINCREMENT,
    /* NOTE:
         the old primary key id is not needed for this type of "join" table that "links"
         different tables using foreign keys (this is true for all relational databases,
         not just SQLite)
     */

    class_id   INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    FOREIGN KEY (class_id) REFERENCES classes (id),
    FOREIGN KEY (student_id) REFERENCES students (id),
    UNIQUE (class_id, student_id)

    -- NOTE: alternatively, in this situation, instead of UNIQUE we could have used a composite PRIMARY KEY
    -- PRIMARY KEY (class_id, student_id)
);

-- Now let's try to register the same student for the same class twice
INSERT INTO registered_students (class_id, student_id2, 3);

-- ❗ Expect an error when you run this INSERT statement.
INSERT INTO registered_students (class_id, student_id2, 3);

-- Canvas: Answer question Q22

-- ============================================
-- End of HW2_Part2, congratulations!!! 🎉🎉🎉
-- ============================================
