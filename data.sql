begin transaction;

INSERT INTO User (userName,fullName,password,roleID)
VALUES ("Nooyen", "Robert Nguyen", "hunter", 3);

INSERT INTO User (userName,fullName,password,roleID)
VALUES ("BurryInAHurry", "Graham Burry", "huntermanager", 2);

INSERT INTO User (userName,fullName,password,roleID)
VALUES ("Kushlord", "Ankush Varshneya", "hunter1", 1);

INSERT INTO User (userName,fullName,password,roleID)
VALUES ("Mooreloaded", "Ryan Moore", "hunter2", 1)

INSERT INTO User (userName,fullName,password,roleID)
VALUES ("LorettaBetta","Loretta Lee","hunter3",1)

INSERT INTO Student (studentNumber,cmail,userName)
VALUES ("100853074","ankushlord@cmail.carleton.ca","Kushlord");

INSERT INTO Student (studentNumber,cmail,userName)
VALUES ("195372839","ryanmoore@cmail.carleton.ca","Mooreloaded");

INSERT INTO Student (studentNumber,cmail,userName)
VALUES ("123456789","somestudent@cmail.carleton.ca","LorettaBetta");

INSERT INTO PaymentInformation (creditCardNumber, cardType, cvv, expirationDate, nameOnCard,postalCode,province,city,streetName,houseNumber,studentNumber)
Values ("2345-5675-1234", "Master Card", "756","19760420","Ankush Dabess Varshneya","H8R8H8","Ontario","Ottawa","Swag St.",420,"100853074");

INSERT INTO Term (termID,startDate,endDate)
VALUES (1,"20140905","20141209");

INSERT INTO Course (courseCode,section,instructor,termID)
VALUES ("PHIL1002","C","Peter Dinklage");

INSERT INTO Course (courseCode,section,instructor,termID)
VALUES ("COMP3004","A", "Christine Laurendeau",1);

INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID)
VALUES ("195372839","PHIL1002","C",1);

INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID)
VALUES ("100853074","COMP3004", "A", 1);

INSERT INTO Textbook (ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition,itemID)
VALUES ("111-1-11-111111-0","./COMP3004.png","COMP3004 course pack is required!","Author of COMP3004","COMP3004 A Course Pack","Carleton Course Pack Inc.","1st",1);

INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID)
VALUES ("111-1-11-111111-0",1,"Intro To COMP3004",2);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("111-1-11-111111-0",1,1,"Pre-reqs for COMP3004",3);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("111-1-11-111111-0",1,2,"Review needed information for COMP3004",4);

INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID)
VALUES ("111-1-11-111111-0",2,"COMP3004 Midterm",5);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("111-1-11-111111-0",2,1,"COMP3004 Midterm mark break-up",6);

INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID)
VALUES ("111-1-11-111111-0","COMP3004","A",1);


INSERT INTO Course (courseCode,section,instructor,termID)
VALUES("COMP3804", "A", "Amin Gheibi",1);

INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID)
VALUES ("100853074","COMP3804", "A", 1);

INSERT INTO Textbook (ISBN,coverImageLocation,desc,author,textbookTitle,publisher,edition,itemID)
VALUES ("222-2-22-222222-0","./COMP3804.png","COMP3804 course pack is required!","Author of COMP3804","COMP3804 A Course Pack","Carleton Course Pack Inc.","1st",7);

INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID)
VALUES ("222-2-22-222222-0",1,"Intro To COMP3804",8);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("222-2-22-222222-0",1,1,"Pre-reqs for COMP3804",9);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("222-2-22-222222-0",1,2,"Review needed information for COMP3804",10);

INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID)
VALUES ("222-2-22-222222-0",2,"COMP3804 Midterm",11);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("222-2-22-222222-0",2,1,"COMP3804 Midterm mark break-up",12);

INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID)
VALUES ("222-2-22-222222-0","COMP3804","A",1);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (1,1.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (2,2.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (3,3.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (4,4.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (5,5.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (6,6.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (7,7.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (8,8.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (9,9.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (10,10.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (11,11.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (12,12.99,0);

commit;
