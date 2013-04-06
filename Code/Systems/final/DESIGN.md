--- NAMES ---
Helen Nie
Sarah Duncan

--- DESCRIPTION ---
A chat program that allows people at different computers to communicate via a server.

--- HOW THE PROJECT IS USED ---
All that's needed to run the project is to run the server code in one terminal and client code in two other terminals. For details as to how to do that, look at README.md

--- TOPICS ---
Allocating memory.
Reading and writing
Processes (forking, exec etc.).
Pipes (named and unnamed).
Networking.

--- BREAKDOWN ---
We do everything together, either in class or using Skype and screenshare.

--- DATA STRUCTURES ---
Sockets
Arrays
Pointers


--- ALGORITHMS ---
void subserver(int socket_clent, int to_server, int from_server)
char * send_online_list(char **names, int client_pids[], int last_client)
static void sighandler(int signo)
int main()

--- TIMELINE ---
by Jan 9: figure out how the networking aspects will work
by Jan 13: have networking aspects coded
by Jan 16: have messaging aspects coded
by due date: debug and polish