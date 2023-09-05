#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h" 

//интерфейс
class interface_DBConnection
{
public:
	interface_DBConnection()
	{}
	virtual ~interface_DBConnection()
	{}
	virtual void open() = 0;
	virtual void close() = 0;
	virtual void execQuery() = 0;
};

//класс moc-объекта
class DBConnection : public interface_DBConnection
{
public:
	MOCK_METHOD(void, open, (), (override));
	MOCK_METHOD(void, close, (), (override));
	MOCK_METHOD(void, execQuery, (), (override));
	
};

//алгоритм для тестирования
void working(interface_DBConnection* iDBConnection)
{
	iDBConnection->open();
	iDBConnection->execQuery();
	iDBConnection->execQuery();
	iDBConnection->execQuery();
	iDBConnection->close();
}

//тест
TEST(DBConnectionTest, test1)
{
	DBConnection dbCon;

	//методы должны быть вызваны ровно 1 раз
	EXPECT_CALL(dbCon, open).Times(1);
	EXPECT_CALL(dbCon, close).Times(1);

	//метод должен быть вызван хотя бы 2 раза
	EXPECT_CALL(dbCon, execQuery).Times(::testing::AtLeast(2));

	working(&dbCon);

}

