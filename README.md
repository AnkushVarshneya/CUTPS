Starting point of API Calls we need in D2 (Based on occurrences of accessing the storage in the sequence diagrams):

Student API Calls:

//input: Student, Term    output: a list of textbooks 
studentViewTextbooks (student, term)

//input: Student output:1 ShoppingCart
viewShoppingCart (student)

//input: student, PurchasableItem, quantity of item   output: void
addContent(student,purchasableItem,quantity) 

//input: Student     output: void
emptyShoppingCart(Student)