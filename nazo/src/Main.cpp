#include <zpch.h>
#include "NazoApplication.h"

int main()
{
	ApplicationSpecs settings;
	settings.name = "Nazo";
	Nazo::NazoApplication app = Nazo::NazoApplication(settings);
	app.Run();
	return 0;
}