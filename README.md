Starting point of API Calls we need in D2 (Based on occurrences of accessing the storage in the sequence diagrams):

### *Student API Calls:* ###

input: QString for student number, Term object    output: a list of textbooks 

**studentViewTextbooks (QString StudentNumber, term)**

input: QString for student number output:1 A list of purchasable items

**viewShoppingCart (QString studentNumber)**

input: student, PurchasableItem, quantity of item   output: void

**addContent(student number,purchasableItemID,quantity)** 

input: Student     output: void

**emptyShoppingCart(Student number)**

input: Student    output: modified student with BillingInformation

**getExistingBillingInfo (Student number)**

input: Student, BillingInfo   output: void

**saveBillingInformation(Student number, BillingInformation)**


### ContentManager API Calls ###

createTextbook(Textbook)

createCourse(Course)

linkTextbook(Textbook,Course)

viewAllTextbooks(term)

viewCourses(term)