#include "AuthNetwork.h"

int main(int argc, char* argv[])
{
	Logger::Log("DBO - AuthServer\n");
	AuthServer app;

	int rc = app.Create(argc, argv);
	if (0 != rc)
	{
		Logger::Log("Server Application Create Fail %d\n", rc);
		return rc;
	}

	app.Start();
	app.WaitForTerminate();
	return 0;
}

