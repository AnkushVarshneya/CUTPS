How to unpack, compile, and run the program:

- Insert DVD into DVD drive
- in the directory of the DVD drive, enter "tar -xf CUTPSD2.tar" in the terminal of the VM
- Run QtCreator
- Click File->Open File or Project
- Find cutps_server folder in the DVD drive directory
- Open the cutps_server.pro file in the folder (Click Configure Folder)
- Similarly, find the gui_test folder in the DVD drive directory, open the gui_test.pro file (click Configure Folder)
- In Qt Creator Debug (Bottom area of the left Qt toolbar), select the cutps_server to be built and run first (select the project in Debug, and click the green play button)
- After cutps_server project has been built and is running, switch to the gui_test project in Debug, build and run it. 
- You should now see a GUI with the test drivers in place. To execute a test, click a test case in the cascading menu located near the top of the window. 

Menu is branched as:

ContentManager-> Create Course-> test cases
	      -> Create Textbook -> test cases
	      -> Link Textbook -> test cases
              -> View Textbooks by Term -> test cases
	      -> View Courses by Term -> test cases

Student -> View Textbooks -> test cases
        -> View ShoppingCart -> test cases
        -> Empty Shopping Cart -> test cases
        -> Add Content -> test cases
        -> Get Existing Payment Information -> test cases
        -> Save Payment Information -> test cases

After selecting a test case, the textbox will display a description of the test case. Click "Execute" button near the bottom of the screen to execute the API to the server (assuming the server and client has connected). The text box will change with a Pass or Fail description after the Client/Server process communications have been done. 

