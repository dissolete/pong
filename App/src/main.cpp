#include <assert.h>
#include <stddef.h>
#include <new>
#include "CRCore.hpp"
#include "PongApp.hpp"

int main(int argc, char* argv[])
{
	// Defualt exit code
	int exitCode = CRE::STATUS_OK;

	// Create our app
	CRE::App * pong = new(std::nothrow) PongApp();
	assert(NULL != pong and "main() can't create application");

	// Execute the application
	exitCode = pong->run();

	delete pong;

	pong = NULL;

	return exitCode;
}