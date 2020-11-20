#include "ut_tabbar_test.h"

#include "tabbar.h"
#include "utils.h"

//Qt单元测试相关头文件
#include <QTest>
#include <QtGui>
#include <QSignalSpy>
#include <QDebug>
#include <QUuid>

UT_Tabbar_Test::UT_Tabbar_Test()
{
}

void UT_Tabbar_Test::SetUp()
{
}

void UT_Tabbar_Test::TearDown()
{
}

QString UT_Tabbar_Test::generateUniqueId()
{
    return QUuid::createUuid().toString();
}

#ifdef UT_TABBAR_TEST
TEST_F(UT_Tabbar_Test, setTabHeight)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    int tabHeight = 36;
    tabbar.setTabHeight(tabHeight);
    EXPECT_EQ(tabbar.height(), 36);
}

TEST_F(UT_Tabbar_Test, setTabItemMinWidth)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    int tabItemMinWidth = 110;
    tabbar.setTabItemMinWidth(tabItemMinWidth);
    EXPECT_EQ(tabbar.m_tabItemMinWidth, tabItemMinWidth);

}

TEST_F(UT_Tabbar_Test, setTabItemMaxWidth)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    int tabItemMaxWidth = 450;
    tabbar.setTabItemMaxWidth(tabItemMaxWidth);
    EXPECT_EQ(tabbar.m_tabItemMaxWidth, tabItemMaxWidth);
}

TEST_F(UT_Tabbar_Test, addTab)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }
    EXPECT_EQ(tabbar.count(), tabCount);
}

TEST_F(UT_Tabbar_Test, insertTab)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.insertTab(i, tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }
    EXPECT_EQ(tabbar.count(), tabCount);
}

TEST_F(UT_Tabbar_Test, removeTab)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QObject::disconnect(&tabbar, &DTabBar::tabIsRemoved, nullptr, nullptr);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.insertTab(i, tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }
    EXPECT_EQ(tabbar.count(), tabCount);

    QString firstTabId = tabbar.identifier(0);
    tabbar.removeTab(firstTabId);

    EXPECT_EQ(tabbar.count(), tabCount - 1);
}


TEST_F(UT_Tabbar_Test, identifier)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    int firstTabIndex = 0;
    EXPECT_EQ(tabbar.identifier(firstTabIndex), tabIdList.first());
}

TEST_F(UT_Tabbar_Test, getIndexByIdentifier)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    int firstTabIndex = 0;
    int tabIndex = tabbar.getIndexByIdentifier(tabIdList.first());
    EXPECT_EQ(tabIndex, firstTabIndex);
}

TEST_F(UT_Tabbar_Test, setTabText)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    int firstTabIndex = 0;
    QString tabText = QString("tab001");
    tabbar.setTabText(tabIdList.first(), tabText);
    EXPECT_EQ(tabbar.tabText(firstTabIndex), tabText);
}

TEST_F(UT_Tabbar_Test, getSessionIdTabIndexMap)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QMap<int, int> sessionIdTabIndexMap = tabbar.getSessionIdTabIndexMap();
    EXPECT_EQ(sessionIdTabIndexMap.isEmpty(), true);
}

TEST_F(UT_Tabbar_Test, saveSessionIdWithTabIndex)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    const int mapSize = 5;
    for (int i = 0; i < mapSize; i++) {
        tabbar.saveSessionIdWithTabIndex(i + 1, i);
    }

    QMap<int, int> sessionIdTabIndexMap = tabbar.getSessionIdTabIndexMap();
    EXPECT_EQ((mapSize == sessionIdTabIndexMap.size()), true);
}

TEST_F(UT_Tabbar_Test, saveSessionIdWithTabId)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    const int mapSize = 5;
    for (int i = 0; i < mapSize; i++) {
        tabbar.saveSessionIdWithTabId(i, generateUniqueId());
    }

    QMap<int, QString> sessionIdTabIdMap = tabbar.m_sessionIdTabIdMap;
    EXPECT_EQ((mapSize == sessionIdTabIdMap.size()), true);
}

TEST_F(UT_Tabbar_Test, queryIndexBySessionId)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    const int mapSize = 5;
    for (int i = 0; i < mapSize; i++) {
        tabbar.saveSessionIdWithTabIndex(i + 1, i);
    }

    int queryIndex = tabbar.queryIndexBySessionId(0);
    EXPECT_EQ((queryIndex == -1), true);
}

TEST_F(UT_Tabbar_Test, setChangeTextColor)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    QString firstTabId = tabbar.identifier(0);
    tabbar.setChangeTextColor(firstTabId);
}

TEST_F(UT_Tabbar_Test, setNeedChangeTextColor)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    QColor redColor = QColor(Qt::red);

    QString firstTabId = tabbar.identifier(0);
    tabbar.setNeedChangeTextColor(firstTabId, redColor);
}

TEST_F(UT_Tabbar_Test, removeNeedChangeTextColor)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    QString firstTabId = tabbar.identifier(0);
    tabbar.setChangeTextColor(firstTabId);

    tabbar.removeNeedChangeTextColor(firstTabId);
}

TEST_F(UT_Tabbar_Test, isNeedChangeTextColor)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    QColor redColor = QColor(Qt::red);

    QString firstTabId = tabbar.identifier(0);
    tabbar.setNeedChangeTextColor(firstTabId, redColor);

    EXPECT_EQ(tabbar.isNeedChangeTextColor(firstTabId), true);
}

TEST_F(UT_Tabbar_Test, setClearTabColor)
{
    TabBar tabbar;
    tabbar.resize(800, 50);
    tabbar.show();
    EXPECT_EQ(tabbar.isVisible(), true);

    QList<QString> tabIdList;
    const int tabCount = 6;
    for (int i = 0; i < tabCount; i++) {
        QString tabName = QString("tab%1").arg(i);
        QString tabIdentifier = generateUniqueId();
        tabbar.addTab(tabIdentifier, tabName);
        tabIdList.append(tabIdentifier);
#ifdef ENABLE_UI_TEST
        QTest::qWait(UT_WAIT_TIME);
#endif
    }

    QString firstTabId = tabbar.identifier(0);
    tabbar.setChangeTextColor(firstTabId);

    tabbar.setClearTabColor(firstTabId);
}

#endif