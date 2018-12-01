#include <iostream>
#include "serverManager.h"
using namespace std;
void startUI(){
	printf("**********************\n");
	printf("Welcome\n");
	return;
}
int main(int argc, char *argv[]){

	const short port = 8000;
	startUI();
	ServerManager srvManager(port);
	srvManager.startServer();

	return 0;
}
