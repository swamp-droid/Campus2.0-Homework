# Campus2.0-Homework
[Campus 2.0] Command Line Chat

# Task
Create a command line application that functions as a chat. The application has to read input from commandline and send it to all peers using **UDP**. When a message from other instance of the app is received the message has to be output in the console.  
- **Use [winsock](https://docs.microsoft.com/en-us/windows/win32/winsock/getting-started-with-winsock) for networking**.  
- Use broadcast to make sure all instances of the application running within a local network receive the messages.  
- **[OPTIONAL]** Use broadcast only to discover peers and then send the message to all peers directly.
