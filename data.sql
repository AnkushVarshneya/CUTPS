INSERT INTO User (userName,firstName,lastName,password,roleID)
VALUES ("Nooyen", "Robert", "Nguyen", "hunter", 3);

INSERT INTO User (userName,firstName,lastName,password,roleID)
VALUES ("BurryInAHurry", "Graham", "Burry", "huntermanager", 2);

INSERT INTO User (userName,firstName,lastName,password,roleID)
VALUES ("Kushlord", "Ankush", "Varshneya", "hunter1", 1);

INSERT INTO Student (studentNumber,cmail,userName)
VALUES ("1337133713","ankushlord@cmail.carleton.ca","Kushlord");

INSERT INTO PaymentInformation (creditCardNumber, cvv, expirationDate, nameOnCard,postalCode,province,city,streetName,houseNumber,studentNumber)
Values (2345-5675-1234,756,1976-04-20,"Ankush Dabess Varshneya","H8R8H8","Ontario","Ottawa","Swag St.",420,"1337133713");

INSERT INTO Term (termID,startDate,endDate)
VALUES (1,"2014-05-01","2099-09-09");

INSERT INTO Course (courseCode,section,instructor,termID)
VALUES ("COMP666","F","Jesus Christine",1);

INSERT INTO Student_RegisteredIn_Course (studentNumber,courseCode,section,termID)
VALUES ("1337133713","COMP666","F",1);

INSERT INTO Textbook (ISBN,coverImageLocation,Desc,Author,TextbookTitle,Publisher,Edition,itemID)
VALUES ("978-3-16-148410-0","./pic.png","Oh god what","Robert Nooyin","Robert's Great Escape: The Un-Escape","Shitty Books Inc.","5th",1);

INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID)
VALUES ("978-3-16-148410-0",1,"Moore to Give: A Christmas Story",2);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("978-3-16-148410-0",1,1,"The Givening",3);

INSERT INTO Chapter (ISBN,chapterNumber,chapterTitle,itemID)
VALUES ("978-3-16-148410-0",2,"Ankush is out of the Group",4);

INSERT INTO Section (ISBN,chapterNumber,sectionNumber,sectionTitle,itemID)
VALUES ("978-3-16-148410-0",2,1,"Retribution",5);

INSERT INTO Course_Assigned_Textbook (ISBN,courseCode,section,termID)
VALUES ("978-3-16-148410-0","COMP666","F",1);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (1,4.20,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (2,13.37,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (3,9.99,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (4,5000.00,0);

INSERT INTO PurchasableItem (itemID,price,availability)
VALUES (5,50.00,0);