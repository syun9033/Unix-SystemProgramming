
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

/* MACRO */
#define MALLOC(X, Y) (X*)malloc(sizeof(X) * Y)

/* FLAG ERROR Define */
#define FLAG_IP_ERROR 10
#define FLAG_BIND_ERROR 12
#define FLAG_LISTEN_ERROR 13
#define FLAG_SOCKET_ERROR 14
#define FLAG_CONNECT_ERROR 15

/* FLAG DATA Define */
#define FLAG_TRUE 1
#define FLAG_FALSE 0
#define FLAG_USER_NUM 6

/* MEMORY Define */
#define BUF_MSG 1024
#define BUF_REG 255

/* Struct */
typedef struct users
{
    /* Short */
    short sLoginState;
    
    /* Integer */
    int nVenID[FLAG_USER_NUM];
    int nVersion;
    int nFileDiscript;
    
    /* String */
    char sID[BUF_REG];
    char sPassword[BUF_REG];
} USER;

int anUser_Name_Flag[FLAG_USER_NUM];
USER asUser_Current[FLAG_USER_NUM];

void handle_Error(const short sError);
void send_Msg(const int nSocket, const ssize_t nLength, const char * sMsg);

/* Typedef */
typedef struct sockaddr_in SOCK_IN;

int main(int argc, char * argv[])
{
	/* Pthread */
    pthread_t read_id;
    pthread_mutex_init(&pMutx, NULL);

	if (argc != 2) { handle_Error(FLAG_IP_ERROR); }
    
    /* Integer */
    int nClnt_Sock = 0;
    int nServ_Sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    
    /* struct sockaddr_in */
    SOCK_IN sServ_Adr, sClnt_Adr;
    
    /* sockaddr_in Initialization */
    memset(&sServ_Adr, 0, sizeof(sServ_Adr));
    sServ_Adr.sin_family = AF_INET;
    sServ_Adr.sin_addr.s_addr = htonl(INADDR_ANY);
    sServ_Adr.sin_port = htons(atoi(argv[1]));
    
    /* Socket Bind & Listen */
    if (bind(nServ_Sock, (struct sockaddr *) &sServ_Adr, sizeof(sServ_Adr)) == EOF) { handle_Error(FLAG_BIND_ERROR); }
    if (listen(nServ_Sock, 10) == EOF) { handle_Error(FLAG_LISTEN_ERROR); }
    memset(asUser_Current, 0, sizeof(USER) * 6);
    while (FLAG_TRUE)
    {
        socklen_t unClnt_Adr_Sz = sizeof(sClnt_Adr);
        if ((nClnt_Sock = accept(nServ_Sock, (struct sockaddr *)&sClnt_Adr, &unClnt_Adr_Sz)) == EOF) { break; }

    }
    
    close(nServ_Sock);

	return 0;
}

void send_Msg(const int nSocket, const ssize_t nLength, const char * sMsg)
{
    write(nSocket, sMsg, nLength);
}

void handle_Error(const short sError)
{
    switch (sError)
    {
        case (FLAG_IP_ERROR): { printf("Using Current IP Address Error!!!\n"); break; }
        case (FLAG_SOCKET_ERROR): { printf("Create Socket Error!!!\n"); break; }
        case (FLAG_CONNECT_ERROR): { printf("Connect Server Error!!!\n"); break; }
        case (FLAG_BIND_ERROR): { printf("Bind Socket Error!!!\n"); break; }
        case (FLAG_LISTEN_ERROR): { printf("Listen Socket Error!!!\n"); break; }
        default: { printf("Network UnKnown Error!!!\n"); break; }
    }
}