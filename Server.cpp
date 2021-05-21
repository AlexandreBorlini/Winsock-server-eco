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


	// Criar o socket do Server (UDP)
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (sock == SOCKET_ERROR) {

		cout << "Erro ao criar SOCKET :: " << WSAGetLastError() << endl;
		return;
	}


	// Bindar o Socket a uma porta
	SOCKADDR_IN enderecoLocal;
	enderecoLocal.sin_port        = htons(9999);
	enderecoLocal.sin_addr.s_addr = INADDR_ANY;
	enderecoLocal.sin_family      = AF_INET;


	if (bind(sock, (SOCKADDR*)&enderecoLocal, sizeof(enderecoLocal))) {

		cout << "Erro ao bindar Socket :: " << WSAGetLastError() << endl;
		return;
	}


	// Avisarque o server foi iniciado corretamente
	cout << "Server iniciado corretamente\n" << endl;

	// Loop principal
	while (true) {

		SOCKADDR_IN chegando;
		int tamanhoSocketVindo = sizeof(chegando);
		int bytesRecebidos = recvfrom(sock, buffer, BUFFER_MAX_SIZE, 0, (SOCKADDR*)&chegando, &tamanhoSocketVindo);
		
		if (bytesRecebidos == SOCKET_ERROR)
			cout << "Erro recvfrom (1) :: " << WSAGetLastError() << endl;

		else {

			// Trata o array como uma string
			buffer[bytesRecebidos] = 0;

			// Printa o texto que veio do Client
			cout << "Client> " << buffer << endl;

			// Envia devolta o eco
			if (sendto(sock, buffer, BUFFER_MAX_SIZE, 0, (SOCKADDR*)&chegando, tamanhoSocketVindo) == SOCKET_ERROR) {

				cout << "Erro ao enviar eco (1) :: " << WSAGetLastError() << endl;
			}
		}
	}
}