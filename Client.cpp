#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

#define BUFFER_MAX_SIZE 1024

void main() {

	// Cria o buffer
	char buffer[BUFFER_MAX_SIZE];

	// Inicializa o Winsock
	WSAData wsaData;
	int inicializado = WSAStartup(0x202, &wsaData);

	if (inicializado != 0) {

		cout << "Erro WSAStartup :: " << WSAGetLastError() << endl;
		return;
	}


	// Criar o socket do Client (UDP)
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sock == SOCKET_ERROR) {

		cout << "Erro ao criar SOCKET :: " << WSAGetLastError() << endl;
		return;
	}


	// Especificar o endereço do Servidor
	SOCKADDR_IN enderecoServidor;
	enderecoServidor.sin_family = AF_INET;
	enderecoServidor.sin_port   = htons(9999);
	enderecoServidor.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // Local

	// Avisar que o Client foi iniciado corretamente
	cout << "Client iniciado corretamente" << endl;

	// Loop principal
	while (true) {


		cout << "\n> " << ends;

		// Pegar texto do usuario
		gets_s(buffer, BUFFER_MAX_SIZE);

		// Enviar ao servidor
		if (sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)&enderecoServidor, sizeof(enderecoServidor))
			== SOCKET_ERROR) {

			cout << "Erro ao enviar mensagem para o servidor :: " << WSAGetLastError() << endl;
		}

		// Receber devolta o eco
		SOCKADDR_IN chegando;
		int tamanhoSocketVindo = sizeof(chegando);
		int bytesRecebidos = recvfrom(sock, buffer, BUFFER_MAX_SIZE, 0, (SOCKADDR*)&chegando, &tamanhoSocketVindo);

		if (bytesRecebidos == SOCKET_ERROR)
			cout << "Erro recvfrom (1) :: " << WSAGetLastError() << endl;

		// Printa o texto que veio do Server
		cout << "Server> " << buffer << endl;
	}
}