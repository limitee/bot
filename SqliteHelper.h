/** ********************************************************************
 * FileName:    CSqlite.h
 * Description: 封装SQLite 的使用类, 当前使用的SQLite 版本是3.4.0
 * Function:     运行SQLite 的继承类
 * History:       2007.11.13 增加函数IsOpen()
 *                   2007.12.3   增加函数FreeStmt(void)
 *                   2007.12.27 增加函数Fetch( vector<string> & ioValues, vector<int>& ioNull ) 增加列空值记录
 *
 ********************************************************************* */
#ifndef __CSQLITE__H__
#define __CSQLITE__H__

// 头文件包含
#include ".\lib\sqlite3\sqlite3.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

/** ************************************************* */
// 补充一些错误码
#define  DEF_INPUTISNULL        -1        /* 输入参数为空 */
#define  DEF_TABLEEXIST         -2        /* 表存在 */
#define  DEF_TABLENOTEXIST      -3        /* 表不存在 */

extern const char * STRBEGINTRANS;
extern const char * STRCOMMITTRANS;
extern const char * STRROLLBACK;

class CSQLite {
	private:
		sqlite3 * m_pDb; // SQLite 对象指针
		sqlite3_stmt * m_pStmt; // 执行SQL 的句柄
		int m_nState; // 当前SQLite 状态
		string m_strFileName; // SQLite的库文件名
		string m_strErrInfo; // 错误信息
		unsigned long m_nTimeoutMs; // 设置超时毫秒数

		unsigned int m_nCurFieldNum; // 当前查询的表中字段的总个数
		unsigned int m_nLimitNum; // 执行SQL忙时最大的尝试次数
		bool m_bIsOpen;

		// 数据库是否打开
		/** ****** 接口函数声明******** */
	public:
		// 构造与析构函数
		CSQLite(void);
		virtual ~CSQLite(void);

		/* 打开SQLite
		 ** 参数说明:
		 **     inDbName:          打开或创建的数据库文件名
		 **     inSynFlag:         是否打开同步开关
		 ** 返回值：
		 **     true:              成功打开SQLite
		 **     false:             打开SQLite失败
		 */
		bool Open(const char * inDbName, bool inSynFlag = false);

		/* 重新打开SQLite
		 ** 参数说明:
		 **     inSynFlag:         是否打开同步开关
		 ** 返回值：
		 **     true:              成功打开SQLite
		 **     false:             打开SQLite失败
		 */
		bool Reopen(bool inSynFlag = false);

		// 关闭SQLite
		void Close(void);

		/* 设置超时时间
		 ** 参数说明：
		 **     inMs:              设置的毫秒数
		 ** 返回值说明:
		 **     SQLITE_OK:      执行成功
		 **     SQLITE_BUSY:    SQLITE文件被锁定
		 **     other:          其它错误信息
		 */
		int SetBusyTimeout(unsigned int inMS);

		/* 获取超时时间 */
		unsigned int GetBusyTimeout(void)const {
			return m_nTimeoutMs;
		}

		// 获取当前SQLite 的状态
		inline int GetState(void)const {
			return m_nState;
		}

		// 获取最后一次的错误信息
		inline const char * GetLastError(void)const {
			return m_strErrInfo.c_str();
		}

		// 获取执行忙时的最大尝试次数
		inline unsigned int GetLimitNum(void)const {
			return m_nLimitNum;
		}

		// 设置执行忙时的最大尝试次数
		inline void SetLimitNum(unsigned int inLimitNum) {
			m_nLimitNum = inLimitNum;
		}

		// 判断数据库是否打开
		inline bool IsOpen(void) {
			return m_bIsOpen;
		}

		// 转换错误码为字符串
		const char * ErrCodeAsString(int inErrCode);

		/*
		 ** Derect Execute SQL  DML  sentence
		 ** 参数说明:
		 **     inSql:          需要执行的SQL语句
		 ** 返回值说明:
		 **     SQLITE_OK:      执行成功
		 **     SQLITE_BUSY:    SQLITE文件被锁定
		 **     other:          其它错误信息
		 */
		int ExecDML(const char * inSql);

		/*
		 ** 事务方式执行一批SQL语句
		 ** 参数说明:
		 **     inTransation:   需要执行的一批SQL语句数组
		 ** 返回值说明:
		 **     SQLITE_OK:      执行成功
		 **     other:          执行失败, 其它错误信息
		 */
		int ExecDML(const vector<string> & inTransation);

		/*
		 ** 执行SQL查询语句
		 ** 参数说明：
		 **     inSql:          执行查询的SQL语句
		 ** 返回值说明：
		 **     SQLITE_OK:      执行成功
		 **     other:          执行失败, 其它错误信息
		 */
		int ExecQuery(const char * inSql);

		/*
		 ** 取一条查询记录
		 ** 参数说明：
		 **     ioValues:      输出参数, 取得查询语句需要得到的字段值
		ioNull,    保存空值的标志 0  为空, 1 非空
		 ** 返回值说明：
		 **     SQLITE_BUSY:   数据库被锁
		 **     SQLITE_ROW:    数据未取完, 需要继续读取数据
		 **     SQLITE_DONE:   数据已经读取完成
		 **     other:         读取数据库记录失败
		 */
		int Fetch(vector<string> & ioValues);
		int Fetch(vector<string> & ioValues, vector<int>& ioNull);

		/* 检查指定的表是否存在
		 ** 参数说明：
		 **     inTabName:             需要检查的表
		 ** 返回值说明：
		 **     DEF_TABLEEXIST:        表存在
		 **     DEF_TABLENOTEXIST:     表不存在
		 **     other:                 执行失败, 其它错误信息
		 */
		int TableExists(const char * inTabName);

		/* 启动一个事务
		 ** 返回值说明:
		 **     SQLITE_OK:      执行成功
		 **     SQLITE_BUSY:    SQLITE文件被锁定
		 **     other:          其它错误信息
		 */
		inline int BeginTrans(void) {
			return ExecDML(STRBEGINTRANS);
		}

		/* 结束一个事务
		 ** 返回值说明:
		 **     SQLITE_OK:      执行成功
		 **     SQLITE_BUSY:    SQLITE文件被锁定
		 **     other:          其它错误信息
		 */
		inline int CommitTrnas(void) {
			return ExecDML(STRCOMMITTRANS);
		}

		/* 回滚一个事务
		 ** 返回值说明:
		 **     SQLITE_OK:      执行成功
		 **     SQLITE_BUSY:    SQLITE文件被锁定
		 **     other:          其它错误信息
		 */
		inline int RollbackTrans(void) {
			return ExecDML(STRROLLBACK);
		}

		// 默认释放类成员m_pStmt  //add 2007.12.3
		void FreeStmt(void);

	private:
		CSQLite(const CSQLite & inSqlite);
		CSQLite & operator = (const CSQLite & inSqlite);

};

#endif

