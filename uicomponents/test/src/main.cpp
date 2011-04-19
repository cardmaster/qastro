#include <QApplication>

void pieDelegateItemTest();
void piePlateTest();
void fanshapeTest();

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

//	fanshapeTest();
//	pieDelegateItemTest();
	piePlateTest();

	return app.exec();
}
