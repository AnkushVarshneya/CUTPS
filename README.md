How to unpack, compile, and run the program:

- Insert DVD into DVD drive
- in the directory of the DVD drive, enter "tar -xf D4_TeamJava.tar" in the terminal of the VM
- Run QtCreator
- Click File->Open File or Project
- Find cuTPS_server folder in the DVD drive directory
- Open the cuTPS_server.pro file in the folder (Click Configure Folder)
- Similarly, find the cuTPS_gui folder in the DVD drive directory, open the cuTPS_gui file (click Configure Folder)
- In Qt Creator Debug (Bottom area of the left Qt toolbar), select the cuTPS_server to be built and run first (select the project in Debug, and click the green play button)
- After cuTPS_server project has been built and is running, switch to the cuTPS project in Debug, build and run it. 
- You should now see a GUI window popping up to enter an IP address. If running client and server process on the VMs in the 4th floor CS labs,
  -if running a server process on another VM host, do an ipconfig on the physical windows matchine in the command prompt (CMD)
  to get the ipv4 address of the server host to enter in the client's GUI IP address prompt
  - if the client and server are on the same VM you may use IP address "10.0.2.15"
- You should now Be presented to select two roles: 1. Student or 2. Content Manager 
- If Choosing student role, you will be presented to the Shopping GUI to do all of the student features of buying content
  - to log in as a student you only need to provide a student number
  - student numbers enrolled currently in the system are: 100853074 (note: this number is populated in the Student GUI by default)
- If Choosing the content manager role, you will be presented two options: 1. Manage Content or 2. Manage Courses, clicking either will present the window to manage the respective object
  - note: the content manager does not require any credentials in this prototype.
- For anything to work, the client must be connected to the server, if it isn't, a warning box will appear saying that the client is disconnected from the server, restart the client process to re run things well. 


