#include <git_header.h>

using namespace std;

void file(char mbranch[], char lbuff[])
{
    //char file_clone[] = "https://github.com/SamhithaN/asd.git";
    FILE *bat1 = fopen("E:\\C++\\qmnds.bat", "w");
    fprintf(bat1, "git checkout %s \n", mbranch);
    fclose(bat1);

    char lbranch[256],file_clone[256];
    int i=0,j=0;
    for (i=0; lbuff[i]!='\n'; i++)
        lbranch[i]=lbuff[i];
    lbranch[i] = '\0';
    i = i+1;
    while(lbuff[i]!='\0')
        file_clone[j++] = lbuff[i++];


    FILE *bat2 = fopen("E:\\C++\\qmnds.bat", "a");
    fprintf(bat2, "git clone %s \n", file_clone);
    //cout<<file_clone;
    fprintf(bat2, "git checkout -b %s \n", lbranch);
    //cout<<lbranch;
    fclose(bat2);
}

void socket()
{
    long SUCCESS;
    WSAData WinSockData;
    WORD DLLVERSION;

    DLLVERSION = MAKEWORD(2,1);

    SUCCESS = WSAStartup(DLLVERSION, &WinSockData);

    SOCKADDR_IN ADDRESS;
    int Address_size = sizeof(ADDRESS);

    SOCKET sock_listen, sock_connection;

    sock_connection = socket(AF_INET, SOCK_STREAM, NULL);
    ADDRESS.sin_addr.s_addr = inet_addr("127.0.0.1");
    ADDRESS.sin_family = AF_INET;
    ADDRESS.sin_port = htons(9250);

    sock_listen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sock_listen, (SOCKADDR*)&ADDRESS, sizeof(ADDRESS));
    listen(sock_listen, SOMAXCONN);
    char mbuff[256],lbuff[256];
    int rbytes;

    for(int i=0;i<1;i++)
    {
        cout<<"\n SERVER: Waiting for incoming connection";
        sock_connection = accept(sock_listen,(SOCKADDR*)&ADDRESS, &Address_size);

        if(sock_connection)
        {
            cout<<endl<<"A connection was found";

            //Sending data 1
            SUCCESS = send(sock_connection,"You have entered the server\n",28,NULL);

            //Master Branch
            rbytes = recv(sock_connection, mbuff, sizeof(mbuff), NULL); // similar to read(), but return -1 if socket closed
            if (rbytes < 0)
            {
                cout<<endl<<rbytes;
                cout<<"socket() failed:"<<errno;
                exit(1);
            }
            else
            {
                mbuff[rbytes] = '\0'; // set null terminal
                printf("\nMaster Branch: %s", mbuff);
            }

            //Local Branch
            rbytes = recv(sock_connection, lbuff, sizeof(lbuff), NULL); // contains both local branch and clone link
            cout<<endl<<rbytes;
            if (rbytes < 0)
            {
                cout<<endl<<rbytes;
                cout<<"socket() failed:"<<errno;
                exit(1);
            }
            else
            {
                lbuff[rbytes] = '\0'; // set null terminal
                printf("\nLocal Branch: %s", lbuff);
            }

            if(!(SUCCESS = send(sock_connection,"Messages sent and received!\n",28,NULL)))
                cout<<"Error in sending confirmation message";
        }
        closesocket(sock_connection);
        close(sock_listen);
    }

    file (mbuff,lbuff);
}

void process()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    LPCWSTR cmdPath = L"C:\\Windows\\System32\\cmd.exe";
    LPWSTR cmdArgs = (LPWSTR)L"C:\\Windows\\System32\\cmd.exe /c E:\\C++\\qmnds.bat";
    ZeroMemory (&si, sizeof(si));
    ZeroMemory (&pi, sizeof(pi));
    bool bCreateProcess = NULL;

    bCreateProcess = CreateProcess(
                cmdPath,
                cmdArgs,
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi
                );
    if(bCreateProcess == FALSE)
        cout<<"\n Create process failed & error number - " <<GetLastError()<<endl;

    cout<<"\n Create Process Success"<<endl;

    WaitForSingleObject( pi.hProcess, INFINITE );
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    return;
}

int main()
{
    socket();
    process();
}
