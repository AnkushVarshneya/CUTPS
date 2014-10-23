Starting point of API Calls we need in D2 (Based on occurrences of accessing the storage in the sequence diagrams):

### *Student API Calls:* ###

input: Student, Term    output: a list of textbooks 

**studentViewTextbooks (student, term)**

input: Student output:1 ShoppingCart

**viewShoppingCart (student)**

input: student, PurchasableItem, quantity of item   output: void

**addContent(student,purchasableItem,quantity)** 

input: Student     output: void

**emptyShoppingCart(Student)**

input: Student    output: modified student with BillingInformation

**getExistingBillingInfo (Student)**

input: Student, BillingInfo   output: void

**saveBillingInformation(Student, BillingInformation)**


### ContentManager API Calls ###

createTextbook()

createCourse()

linkTextbook(Textbook,Course)

viewAllTextbooks(term)

viewCourses(term)