--cuTPS data
--This file is for creating and populating data into tables

--Delete table if there are table with the same name in the current database
--Will display error if table with the same name does not exist, can be ignored

begin transaction;

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

--creating the Table called User
create table User(
	userName varchar(50) NOT NULL primary key,
	firstName varchar(20),
	lastName varchar(20),
	password varchar(20),
	role varchar(20)
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
	cvv varchar(50),
	expirationDate date,
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
	startDate date,
	endDate date
);

--creating the Table called Course_Assigned_Textbook 
create table Course_Assigned_Textbook(
	ISBN varchar(13) NOT NULL references Textbook(ISBN),
	courseCode varchar(8) NOT NULL references Course(courseCode),
	section varchar(1) NOT NULL references Course(section),
	termID integer NOT NULL references Course(termID),
	primary key(ISBN, courseCode, section, termID)
);

--creating the Table called Textbook
create table Textbook(
	ISBN varchar(13) NOT NULL primary key,
	coverImageLocation varchar(100),
	Desc varchar(200),
	Author varchar(50),
	TextBookTitle varchar(50),
	Publisher varchar(50),
	Edition varchar(50),
	itemID integer NOT NULL,
	foreign key (itemID) references PurchasableItem(itemID) on delete cascade
);

--creating the Table called Chapter
create table Chapter(
	ISBN varchar(13) NOT NULL,
	chapterNumber integer NOT NULL,
	chapterTitle varchar(50),
	itemID integer NOT NULL,
	foreign key (ISBN) references Textbook(ISBN) on delete cascade,
	foreign key (itemID) references PurchasableItem(itemID) on delete cascade,
	primary key(ISBN, chapterNumber)
);

--creating the Table called Section
create table Section(
	ISBN varchar(13) NOT NULL,
	chapterNumber integer NOT NULL,
	sectionNumber integer NOT NULL,
	sectionTitle varchar(50),
	itemID integer NOT NULL,
	foreign key (ISBN) references Chapter(ISBN) on delete cascade,
	foreign key (chapterNumber) references Chapter(chapterNumber) on delete cascade,
	foreign key (itemID) references PurchasableItem(itemID) on delete cascade,
	primary key(ISBN, chapterNumber, sectionNumber)
);

--creating the Table called ShoppingCart
create table ShoppingCart(
	cartID integer NOT NULL primary key,
	studentNumber varchar(10) NOT NULL references Student(studentNumber),	
	foreign key (studentNumber) references Student(studentNumber) on delete cascade
);

--creating the Table called ShoppinCart_Contains_PurchasableItem
create table ShoppinCart_Contains_PurchasableItem(
	cartID integer NOT NULL references ShoppingCart(cartID),
	itemID integer NOT NULL references PurchasableItem(itemID),
	quantity integer default 0 NOT NULL,
	primary key(cartID, itemID)
);

--creating the Table called PurchasableItem
create table PurchasableItem(
	itemID integer NOT NULL primary key,
	price decimal(18,2),
	avalibility boolean
);

commit;