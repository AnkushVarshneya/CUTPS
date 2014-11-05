--cuTPS data
--This file is for creating and populating data into tables

--Delete table if there are table with the same name in the current database
--Will display error if table with the same name does not exist, can be ignored

begin transaction;

drop table if exists Role;
drop table if exists User;
drop table if exists Student;
drop table if exists PaymentInformation;
drop table if exists Student_RegisteredIn_Course;
drop table if exists Course;
drop table if exists Term;
drop table if exists Course_Assigned_Textbook;
drop table if exists Textbook;
drop table if exists Chapter;
drop table if exists Section;
drop table if exists ShoppingCart;
drop table if exists ShoppinCart_Contains_PurchasableItem;
drop table if exists PurchasableItem;

--creating the Table called Role
create table Role(
	roleID integer NOT NULL primary key,
	roleType varchar(20)
	);
	
--insert default roles
insert into Role (roleID, roleType) values (1, "Student");
insert into Role (roleID, roleType) values (2, "Content Manager");
insert into Role (roleID, roleType) values (3, "Administrator");

--creating the Table called User
create table User(
	userName varchar(50) NOT NULL primary key,
	fullName varchar(50),
	password varchar(20),
	roleID integer NOT NULL,
	foreign key (roleID) references Role(roleID) on delete cascade
	);
	
--creating the Table called Student
create table Student(
	studentNumber varchar(10) NOT NULL primary key,
	cmail varchar(100) NOT NULL UNIQUE,
	userName varchar(50) NOT NULL,
	foreign key (userName) references User(userName) on delete cascade
	);
	
--creating the Table called PaymentInformation
create table PaymentInformation(
	creditCardNumber varchar(50) NOT NULL,
	cardType varchar(50),
	cvv varchar(50),
	expirationDate varchar(10),
	nameOnCard varchar(50),
	postalCode varchar(7),
	province varchar(50),
	city varchar(50),
	streetName varchar(50),
	houseNumber integer,
	studentNumber varchar(10) NOT NULL,
	foreign key (studentNumber) references Student(studentNumber) on delete cascade,
	primary key(studentNumber, creditCardNumber)
);

--creating the Table called Student_RegisteredIn_Course 
create table Student_RegisteredIn_Course(
	studentNumber varchar(10) NOT NULL references Student(studentNumber),
	courseCode varchar(8) NOT NULL references Course(courseCode),
	section varchar(1) NOT NULL references Course(section),
	termID integer NOT NULL references Course(termID),
	primary key(studentNumber, courseCode, section, termID)
);

--creating the Table called Course
create table Course(
	courseCode varchar(8) NOT NULL,
	section varchar(1) NOT NULL,
	instructor varchar(20),
	termID integer NOT NULL,
	foreign key (termID) references Term(termID) on delete cascade,
	primary key(courseCode, section, termID)
);

--creating the Table called Term
create table Term(
	termID integer NOT NULL primary key,
	startDate varchar(10),
	endDate varchar(10)
);

--creating the Table called Course_Assigned_Textbook 
create table Course_Assigned_Textbook(
	ISBN varchar(20) NOT NULL references Textbook(ISBN),
	courseCode varchar(8) NOT NULL references Course(courseCode),
	section varchar(1) NOT NULL references Course(section),
	termID integer NOT NULL references Course(termID),
	primary key(ISBN, courseCode, section, termID)
);

--creating the Table called Textbook
create table Textbook(
	ISBN varchar(20) NOT NULL primary key,
	coverImageLocation varchar(100),
	desc varchar(200),
	author varchar(50),
	textBookTitle varchar(50),
	publisher varchar(50),
	edition varchar(50),
	itemID integer NOT NULL,
	foreign key (itemID) references PurchasableItem(itemID) on delete cascade
);

--creating the Table called Chapter
create table Chapter(
	ISBN varchar(20) NOT NULL,
	chapterNumber integer NOT NULL,
	chapterTitle varchar(50),
	itemID integer NOT NULL,
	foreign key (ISBN) references Textbook(ISBN) on delete cascade,
	foreign key (itemID) references PurchasableItem(itemID) on delete cascade,
	primary key(ISBN, chapterNumber)
);

--creating the Table called Section
create table Section(
	ISBN varchar(20) NOT NULL,
	chapterNumber integer NOT NULL,
	sectionNumber integer NOT NULL,
	sectionTitle varchar(50),
	itemID integer NOT NULL,
	foreign key (ISBN) references Chapter(ISBN) on delete cascade,
	foreign key (chapterNumber) references Chapter(chapterNumber) on delete cascade,
	foreign key (itemID) references PurchasableItem(itemID) on delete cascade,
	primary key(ISBN, chapterNumber, sectionNumber)
);

--creating the Table called PurchasableItem
create table PurchasableItem(
	itemID integer NOT NULL primary key,
	price decimal(18,2),
	availability boolean
);

commit;