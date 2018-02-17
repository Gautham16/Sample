#include "Persistance.h"
#include "../DbCore/DbCore.h"

#ifdef TEST_PERSISTANCE

int main() {
	std::cout << "\n Test of Persistance \n";
	Persistence<std::string> p;
	DbCore<std::string> db;
	DbElement<std::string> dbe;
	dbe.name("Raj");
	dbe.dateTime(DateTime().now());
	dbe.descrip("New York");
	dbe.payLoad(" Crazy Day");
	std::vector<std::string> c;
	c.push_back("c1");
	c.push_back("c2");
	dbe.children(c);
	db["Kumar"] = dbe;
	showDb(db);
	std::string res = toXml(db);
	std::cout << "\nThe output is shown below:\n" << res << "\n";
	db = p.loadXml("test.xml");
	std::cout << "\n Displaying contents from \"test.xml\" file\n\n";
	showDb(db);
	std::cin.get();
	return 0;
}

#endif 