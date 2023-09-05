#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h" 

//���������
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

//����� moc-�������
class DBConnection : public interface_DBConnection
{
public:
	MOCK_METHOD(void, open, (), (override));
	MOCK_METHOD(void, close, (), (override));
	MOCK_METHOD(void, execQuery, (), (override));
	
};

//�������� ��� ������������
void working(interface_DBConnection* iDBConnection)
{
	iDBConnection->open();
	iDBConnection->execQuery();
	iDBConnection->execQuery();
	iDBConnection->execQuery();
	iDBConnection->close();
}

//����
TEST(DBConnectionTest, test1)
{
	DBConnection dbCon;

	//������ ������ ���� ������� ����� 1 ���
	EXPECT_CALL(dbCon, open).Times(1);
	EXPECT_CALL(dbCon, close).Times(1);

	//����� ������ ���� ������ ���� �� 2 ����
	EXPECT_CALL(dbCon, execQuery).Times(::testing::AtLeast(2));

	working(&dbCon);

}

