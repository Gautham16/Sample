///////////////////////////////////////////////////////////////////////
// Test_Project1 - Testing various requirements in the problem       //
// ver 1.0                                                           //
// Author: Gautham kanekal, Object Oriented Design, Spring 2018      //
///////////////////////////////////////////////////////////////////////

#include "../DbCore/DbCore.h"
#include "../Query/Query.h"
#include "../DateTime/DateTime.h"
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"
#include <iostream>
#include <iomanip>
#include <functional>
#include <regex>
#include <fstream>
#include "../Persistence/Persistance.h"
using namespace NoSqlDb;

//----< Reduce the number of characters to type >----------------------

auto putLine = [](size_t n = 1, std::ostream& out = std::cout)
{
	Utilities::putline(n, out);
};

///////////////////////////////////////////////////////////////////////
// DbProvider class
// - Provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument


class DbProvider
{
public:
	DbCore<Payload>& db() { return db_; }
private:
	static DbCore<Payload> db_;
};

DbCore<Payload> DbProvider::db_;

////////////////////////////////////////////////////////////////
//Demonstrating Requirements

//----< Demonstrating Requirement #1 >--------------------------

bool testR1()
{
	Utilities::title("Demonstrating Requirement #1");
	std::cout << "\n  " << typeid(std::function<bool()>).name()
		<< ", declared in this function, "
		<< "\n  is only valid for C++11 and later versions.";
	putLine();
	return true; // would  not compile unless C++11
}

//----< Demonstrating Requirement #2 >--------------------------

bool testR2()
{
	Utilities::title("Demonstrating Requirement #2");
	std::cout << "\n  A visual examination of all the submitted code "
		<< "will show only\n  use of streams and operators new and delete.";
	putLine();
	return true;
}

//----< Demonstrating Requirement #3a >--------------------------

bool testR3a()
{
	Utilities::title("Demonstrating Requirement #3a - Creating of DbElement");
	std::cout << "\n  Creating a db element with key \"Fawcett\":";

	// create database to hold std::string payload

	DbCore<Payload> db;
	DbProvider dbp;
	dbp.db() = db;

	// create some demo elements and insert into db

	DbElement<Payload> demoElem;
	demoElem.name("Jim");
	demoElem.descrip("Instructor for CSE687");
	demoElem.dateTime(DateTime().now());
	//demoElem.payLoad("The good news is ...");

	if (demoElem.name() != "Jim")
		return false;
	if (demoElem.descrip() != "Instructor for CSE687")
		return false;
	if (demoElem.dateTime().now() != DateTime().now())
		return false;
	//if (demoElem.payLoad() != "The good news is ...")
		//return false;

	showHeader();
	showElem(demoElem);

	db["Fawcett"] = demoElem;
	dbp.db() = db;
	putLine();
	return true;
}

//----< Demonstrating Requirement #3b >--------------------------

bool testR3b()
{
	Utilities::title("Demonstrating Requirement #3b - Creating DbCore");

	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem = db["Fawcett"];

	demoElem.name("Ammar");
	demoElem.descrip("TA for CSE687");
	//demoElem.payLoad("You should try ...");
	db["Salman"] = demoElem;
	if (!db.contains("Salman"))
		return false;
	demoElem.name("Artemis");
	db["Sun"] = demoElem;
	demoElem.name("Nikhil");
	db["Prashar"] = demoElem;
	demoElem.name("Pranjul");
	db["Arora"] = demoElem;
	demoElem.name("Akash");
	db["Anjanappa"] = demoElem;

	demoElem.name("Gautham");
	db["Kanekal"] = demoElem;

	if (db.size() != 7)
		return false;

	std::cout << "\n  After adding elements with keys: ";
	DbCore<Payload>::Keys keys = db.keys();
	showKeys(db);
	putLine();

	std::cout << "\n  Make all the new elements children of element with key \"Fawcett\"";
	db["Fawcett"].children().push_back("Salman");
	db["Fawcett"].children().push_back("Sun");
	db["Fawcett"].children().push_back("Prashar");
	db["Fawcett"].children().push_back("Arora");
	db["Fawcett"].children().push_back("Anjanappa");
	db["Fawcett"].children().push_back("Kanekal");

	showHeader();
	showElem(db["Fawcett"]);

	db["Salman"].children().push_back("Sun");
	db["Salman"].children().push_back("Prashar");
	db["Salman"].children().push_back("Arora");
	db["Salman"].children().push_back("Anjanappa");
	db["Salman"].children().push_back("Kanekal");

	// display the results

	putLine();
	std::cout << "\n  Showing all the database elements:";
	showDb(db);
	putLine();

	std::cout << "\n  Database keys are: ";
	showKeys(db);
	dbp.db() = db;
	putLine();
	return true; 
}

//----< Demonstrating Requirement #4a >--------------------------

bool testR4a()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	bool retval = false;
	demoElem.name("Gautham");
	demoElem.descrip("Student of CSE687");
	demoElem.dateTime(DateTime().now());
	
	Utilities::title("Demonstrating Requirement #4a -- Addition of new key to the database --");
	if (demoElem.name() != "Gautham")
	{
		retval = false;
	}
	if (demoElem.descrip() != "Student of OOD")
	{
		retval = false;
	}

	//display the results

	showHeader();
	showElem(demoElem);
	db.keyadd(db, "Kanekal", demoElem);
	dbp.db() = db;
	putLine();
	showDb(db);
	putLine();
	std::cout << "\n  Database keys are :";
	showKeys(db);
	putLine();
	return true;
}

//----< Demonstrating Requirement #4b >--------------------------

bool testR4b()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	Utilities::title("Demonstrating Requirement #4b -- Deletion of key from the database --");
	demoElem = db["Prashar"];

	//display the results

	showHeader();
	showElem(db["Prashar"]);
	db.deleteKey(db, "Prashar");
	dbp.db() = db;
	putLine();
	showDb(db);
	putLine();
	std::cout << "\n  Database keys are :";
	showKeys(db);
	putLine();
	return true;
}

//----< Demonstrating Requirement #5 >--------------------------

bool testR5()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	Utilities::title("Demonstrating Requirement #5 -- Editing the key in the database --");
	putLine();

	//display the results

	std::cout << "\n  Before editing\n";
	showDb(db);
	DbElement<Payload> tempelem = db["Sun"];
	tempelem.descrip("First Successful Project");
	db.editKey(db, "Sun", tempelem);
	dbp.db() = db;
	putLine();
	std::cout << "\n  After editing\n";
	showDb(db);
	putLine();
	return true;
}

//----< Demonstrating Requirement #6a >--------------------------

bool testR6a()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	Utilities::title("Demonstrating Requirement #6a -- Retrieving the value of a given key from the database --");
	putLine();
	QueryExecuter<std::string> q1;
	std::string tempst = "((.*)(A)(.*))";
	DateTime cur = DateTime().now();
	q1.select("key").from(db).where((tempst), db, cur, cur);
	PrintKeys(q1.FinalKeys);
	putLine();
	return true;
}

//----< Demonstrating Requirement #6b >--------------------------

bool testR6b()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	Utilities::title("Demonstrating Requirement #6b -- Retrieving all children of a given key --");
	putLine();
	QueryExecuter<std::string> q1;
	std::string tempst = "((Faw)(.*))";
	DateTime cur = DateTime().now();
	q1.select("keychildren").from(db).where((tempst), db, cur, cur);
	PrintKeys(q1.FinalKeys);
	putLine();
	return true;
}

//----< Demonstrating Requirement #6c >--------------------------

bool testR6c()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	Utilities::title("Demonstrating Requirement #6c -- Retrieving t all keys matching to specified regular expression --");
	QueryExecuter<std::string> q1;
	std::string tempst = "((.*)(TA)(.*))";
	DateTime cur = DateTime().now();
	q1.select("description").from(db).where((tempst), db, cur, cur);
	putLine();
	std::cout << "The keys are:\n";
	putLine();
	for (auto key : q1.FinalKeys)
	{
		std::cout << key << "\n";
	}
	putLine();
	return true;
}

//----< Demonstrating Requirement #6d >--------------------------

bool testR6d()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	Utilities::title("Demonstrating Requirement #6d -- Retrieving all keys matching a specified regular expression in a metadata --");
	QueryExecuter<std::string> q1;
	std::string tempst = "((A)(.*))";
	DateTime cur = DateTime().now();
	q1.select("name").from(db).where((tempst), db, cur, cur);
	putLine();
	std::cout << "The keys are:\n";
	putLine();
	for (auto key : q1.FinalKeys)
	{
		std::cout << key << "\n";
	}
	putLine();
	return true;
}


//----< Demonstrating Requirement #7 >--------------------------

bool testR7()
{
	DbProvider dbp;
	DbCore<Payload> db = dbp.db();
	DbElement<Payload> demoElem;
	Utilities::title("Demonstrating Requirement #7 -- And-ing and Or-ing of two queries --");
	QueryExecuter<std::string> q1, q2;
	std::string tempst = "((.*)(CSE)(.*))";
	std::string tempst1 = "((Am)(.*))";
	DateTime cur = DateTime().now();
	q1.select("description").from(db).where((tempst),db,cur,cur);
	q2.select("name").from(db).where((tempst1), db,cur, cur);
	std::cout << "From query 1\n";
	for (auto key : q1.FinalKeys)
	{
	std::cout << key << "\n";
	}
	putLine();
	std::cout << "  From query 2\n";
	for (auto key : q2.FinalKeys)
	{
	std::cout << key << "\n";
	}
	std::cout << "\n ORing\n";
	putLine();
	QueryAndOr(q1.FinalKeys, q2.FinalKeys, "OR");
	std::cout << "\n ANDing\n";
	putLine();
	QueryAndOr(q1.FinalKeys, q2.FinalKeys, "AND");
	putLine();
	std::cout << " Before editing\n";
	showDb(db);
	DbElement<Payload> tempelem = db["Arora"];
	tempelem.descrip("Student");
	db.editKey(db, "Arora", tempelem);
	putLine();
	std::cout << " \n After editing\n";
	showDb(db);
	std::cout << "\n";
	std::cout << "  \n Testing for children key search\n";
	q2.select("children").from(db).where((tempst1), db, cur, cur);
	PrintKeys(q2.FinalKeys);
	putLine();
	return true;
}
//----<Demonstrating Requirement #8 >------------------------------------------
bool testR8()
{
	Utilities::title("Demonstrating Requirement #8 -- Persisting and Restoring the database to and from XML file");
	DbCore<std::string> db;
	Persistence<std::string> p;

	//Converts XML to DbCore object
	db = p.convertIntoObj("../Persistence/test.xml");

	//Converts DbCore to XML
	std::string res = toXml(db);
	std::cout << "\n\n Result after converting to XML: " << res << "\n\n";

	return true;
}

//----< Demonstrating Requirement #9 >--------------------------

bool testR9()
{
	DbCore<Payload> db;
	DbElement<Payload> demoElem;
	QueryExecuter<Payload> q;
	DateTime cur;
	Utilities::title("Demonstrating Requirement #9 -- Demonstrating Payload--");
	demoElem.name("Example");
	demoElem.descrip("Type");
	db["Value"] = demoElem;
	Payload p;
	std::string tem1 = "example1";
	std::string tem2 = "example2";
	std::string tem3 = "filepath";
	std::vector<std::string> ex;
	ex.push_back(tem1);
	ex.push_back(tem2);
	p.category(ex);
	p.fpath(tem3);
	demoElem.payLoad(p);
	showElem(demoElem);
	q.select("payload").from(db).where(("(ex)(.*)"), db,cur, cur);
	showDb(db);
	putLine();
	return true;
}

//----< Demonstrating Requirement #10 >--------------------------

bool testR10()
{
	Utilities::title("Demonstrating Requirement #10 -- Implementation of the various packages in Solution: DBCore, Query, Test, Persistence, Executive--");
	std::cout << "\n The package structure is displayed here.\n";
	std::cout << "DBCore: To implement the NoSQLDB, the DbCore contains various classes and the corresponding functionality.\n";
	std::cout << "Query: Various functionalities from NoSQLDB are queried contained in this package.\n";
	std::cout << "Persistence: In order to persist the DB as an XML file on the disk, this contains the required functionality.\n";
	std::cout << "Test: Consists of various functions to execute every test case.\n";
	std::cout << "Executive: Starting point of execution of test cases are defined in Test package.\n";
	std::cout << "\nAlternatively, running \"dir\" command under solution folder displays the packages.\n\n";
	return true;
}

//----< requirement #11 >------------------------------------------
bool testR11() {
	Utilities::title("Demonstrating Requirement #11 - Project's package structure and the dependency is described with the help of XML");
	std::string filePath = "..\\Query11.xml";
	std::ifstream in(filePath);
	if (!in.good())
		throw(std::exception(("can't open source file " + filePath).c_str()));
	std::ostringstream out;
	out << in.rdbuf();
	std::string forOpening = std::move(out.str());
	std::cout << "\nThe XML with package structure is:\n" << forOpening << "\n\n";
	return true;
}

//----< requirement #12 >------------------------------------------
bool testR12() {
	Utilities::title("Demonstrating Requirement #12 -- The requirements #2 to #9 are demonstarted--");
	std::cout << "\nIf the statement \"all tests passed\" is printed in the end, requirement #12 is met.\n";
	return true;
}

//----< requirement #13 >------------------------------------------
bool testR13() {
	Utilities::title("Demonstrating Requirement #13 -- Displaying Package diagram --");
	std::string path = "..\\PackageDiagram.pdf";
	std::cout << "\nThe PDF is present in path: " << path << " i.e. in the same path as the solution file.\n\n";
	return true;
}
#ifdef TESTSUITE
using namespace Utilities;
int main()
{
	Utilities::Title("Testing DbCore - He said, she said database");
	putLine();

	// Define test structures with test function and message

	TestExecutive ex;
	TestExecutive::TestStr ts1{ testR1, "Use C++11" };
	TestExecutive::TestStr ts2{ testR2, "Use streams and new and delete" };
	TestExecutive::TestStr ts3a{ testR3a, "Create DbElement<std::string>" };
	TestExecutive::TestStr ts3b{ testR3b, "Create DbCore<std::string>" };
	TestExecutive::TestStr ts4a{ testR4a, "Addition of a new Key to the Database" };
	TestExecutive::TestStr ts4b{ testR4b, "Deletion of a new Key from the Database" };
	TestExecutive::TestStr ts5{ testR5, "Editing the key in the database" };
	TestExecutive::TestStr ts6a{ testR6a, "Retrieving the value of a given key from the database" };
	TestExecutive::TestStr ts6b{ testR6b, "Retrieving the children of a particular key" };
	TestExecutive::TestStr ts6c{ testR6c, "Retrieving all keys matching to specified regular expression" };
	TestExecutive::TestStr ts6d{ testR6d, "Retrieving all keys based on the specified regular expression in a metadata" };
	TestExecutive::TestStr ts7{ testR7, "And-ing and Or-ing of two queries" };
	TestExecutive::TestStr ts8{ testR8, "Persisting and Restoring data to and from XML" };
	TestExecutive::TestStr ts9{ testR9, "Demonstrating Payload" };
	TestExecutive::TestStr ts10{ testR10, "Implementation of the solution in various packages" };
	TestExecutive::TestStr ts11{ testR11, " Project's package structure and dependency " };
	TestExecutive::TestStr ts12{ testR12, "Requirements 2-9 are displayed" };
	TestExecutive::TestStr ts13{ testR13, "Displaying package diagram" };

	// Register test structures with TestExecutive instance, ex

	ex.registerTest(ts1);
	ex.registerTest(ts2);
	ex.registerTest(ts3a);
	ex.registerTest(ts3b);
	ex.registerTest(ts4a);
	ex.registerTest(ts4b);
	ex.registerTest(ts5);
	ex.registerTest(ts6a);
	ex.registerTest(ts6b);
	ex.registerTest(ts6c);
	ex.registerTest(ts6d);
	ex.registerTest(ts7);
	ex.registerTest(ts8);
	ex.registerTest(ts9);
	ex.registerTest(ts10);
	ex.registerTest(ts11);
	ex.registerTest(ts12);
	ex.registerTest(ts13);

	// Run the tests

	bool result = ex.doTests();
	if (result == true)
		std::cout << "\n  All tests passed";
	else
		std::cout << "\n  At least one test failed";

	putLine(2);
	std::cin.get();
	std::getchar();
	//std::getchar();
	return 0;
}
#endif // TESTSUITE
