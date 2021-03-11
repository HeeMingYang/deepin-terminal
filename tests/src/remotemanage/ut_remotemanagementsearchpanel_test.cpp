/*
 *  Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
 *
 * Author:     daizhengwen <daizhengwen@uniontech.com>
 *
 * Maintainer: daizhengwen <daizhengwen@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ut_remotemanagementsearchpanel_test.h"

#include "remotemanagementsearchpanel.h"
#include "service.h"
#include "mainwindow.h"
#include "stub.h"

// DTK
#include <DApplicationHelper>

//Qt单元测试相关头文件
#include <QTest>
#include <QtGui>

//Google GTest 相关头文件
#include <gtest/gtest.h>

void stub_focusCurrentPage()
{
    return;
}

UT_RemoteManagementSearchPanel_Test::UT_RemoteManagementSearchPanel_Test()
{
}

void UT_RemoteManagementSearchPanel_Test::SetUp()
{
    if (!Service::instance()->property("isServiceInit").toBool()) {
        Service::instance()->init();
        Service::instance()->setProperty("isServiceInit", true);
    }

    m_normalTermProperty[QuakeMode] = false;
    m_normalTermProperty[SingleFlag] = true;
    m_normalWindow = new NormalWindow(m_normalTermProperty, nullptr);
    m_normalWindow->resize(800, 600);
    m_normalWindow->show();

    m_normalWindow->showPlugin(MainWindow::PLUGIN_TYPE_REMOTEMANAGEMENT);
}

void UT_RemoteManagementSearchPanel_Test::TearDown()
{
    if (m_normalWindow) {
        delete m_normalWindow;
    }
}

#ifdef UT_REMOTEMANAGEMENTSEARCHPANEL_TEST

/*******************************************************************************
 1. @函数:    refreshDataByGroupAndFilter
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-22
 4. @说明:    测试组内搜索
*******************************************************************************/
TEST_F(UT_RemoteManagementSearchPanel_Test, refreshDataByGroupAndFilter)
{
    RemoteManagementSearchPanel searchPanel;
    ServerConfig groupConfig;
    groupConfig.m_serverName = "group_item";
    groupConfig.m_address = "127.0.0.1";
    groupConfig.m_group = "group2020";
    groupConfig.m_userName = "dzw";
    groupConfig.m_port = "22";
    //添加数据
    ServerConfig config;
    config.m_serverName = "test_item";
    config.m_address = "127.0.0.1";
    config.m_userName = "dzw";
    config.m_group = "group2020";
    config.m_port = "22";
    ServerConfig config2;
    config2.m_serverName = "test_item2";
    config2.m_address = "127.0.0.1";
    config2.m_userName = "dzw";
    config2.m_port = "22";
    ServerConfigManager::instance()->m_serverConfigs.clear();
    // 分组数据存储结构
    QList<ServerConfig *> list;
    list.append(&groupConfig);
    list.append(&config);
    QList<ServerConfig *> list2;
    list2.append(&config2);
    // 数据存储结构
    ServerConfigManager::instance()->m_serverConfigs.insert("group2020", list);
    ServerConfigManager::instance()->m_serverConfigs.insert("", list2);
    // 刷新列表,填充数据
    searchPanel.refreshDataByGroupAndFilter("group2020", "test_item");
    // 获取当前列表内的数据
    int count = searchPanel.m_listWidget->count();
    EXPECT_EQ(count, 1);
    // 重新搜索 => 找不到的情况
    searchPanel.refreshDataByGroupAndFilter("group2020", "test_item2");
    count = searchPanel.m_listWidget->count();
    EXPECT_EQ(count, 0);
    ServerConfigManager::instance()->m_serverConfigs.clear();
}

TEST_F(UT_RemoteManagementSearchPanel_Test, refreshDataByFilter)
{
    RemoteManagementSearchPanel searchPanel;
    ServerConfig groupConfig;
    groupConfig.m_serverName = "group_item";
    groupConfig.m_address = "127.0.0.1";
    groupConfig.m_group = "group2020";
    groupConfig.m_userName = "dzw";
    groupConfig.m_port = "22";
    //添加数据
    ServerConfig config;
    config.m_serverName = "test_item";
    config.m_address = "127.0.0.1";
    config.m_userName = "dzw";
    config.m_group = "group2020";
    config.m_port = "22";
    ServerConfig config2;
    config2.m_serverName = "test_item2";
    config2.m_address = "127.0.0.1";
    config2.m_userName = "dzw";
    config2.m_port = "22";
    ServerConfigManager::instance()->m_serverConfigs.clear();
    // 分组数据存储结构
    QList<ServerConfig *> list;
    list.append(&groupConfig);
    list.append(&config);
    QList<ServerConfig *> list2;
    list2.append(&config2);
    // 数据存储结构
    ServerConfigManager::instance()->m_serverConfigs.insert("group2020", list);
    ServerConfigManager::instance()->m_serverConfigs.insert("", list2);
    // 刷新列表,填充数据
    searchPanel.refreshDataByFilter("item");
    int count = searchPanel.m_listWidget->count();
    EXPECT_EQ(count, 3);
    searchPanel.refreshDataByFilter("group");
    count = searchPanel.m_listWidget->count();
    EXPECT_EQ(count, 2);
    searchPanel.refreshDataByFilter("test_item2");
    count = searchPanel.m_listWidget->count();
    EXPECT_EQ(count, 1);
    searchPanel.refreshDataByFilter("1988");
    count = searchPanel.m_listWidget->count();
    EXPECT_EQ(count, 0);
    ServerConfigManager::instance()->m_serverConfigs.clear();
}

/*******************************************************************************
 1. @函数:    clearAllFocus
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-23
 4. @说明:    清除所有焦点
*******************************************************************************/
TEST_F(UT_RemoteManagementSearchPanel_Test, clearAllFocus)
{
    RemoteManagementSearchPanel searchPanel;
    searchPanel.show();
    searchPanel.clearAllFocus();
    EXPECT_EQ(searchPanel.m_rebackButton->hasFocus(), false);
    EXPECT_EQ(searchPanel.m_listWidget->hasFocus(), false);
    EXPECT_EQ(searchPanel.m_label->hasFocus(), false);
}

/*******************************************************************************
 1. @函数:    setFocusBack
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-23
 4. @说明:    返回设置
*******************************************************************************/
TEST_F(UT_RemoteManagementSearchPanel_Test, setFocusBack)
{
    Stub s;
    s.set(ADDR(MainWindow, focusCurrentPage), stub_focusCurrentPage);
    // 初始化界面
    RemoteManagementSearchPanel searchPanel;
    searchPanel.show();
    // 新增服务器配置数据
    ServerConfig groupConfig;
    groupConfig.m_serverName = "group_item";
    groupConfig.m_address = "127.0.0.1";
    groupConfig.m_group = "group2020";
    groupConfig.m_userName = "dzw";
    groupConfig.m_port = "22";
    // 分组数据存储结构
    QList<ServerConfig *> list;
    list.append(&groupConfig);
    // 数据存储结构
    ServerConfigManager::instance()->m_serverConfigs.insert("group2020", list);
    // 填充数据
    searchPanel.refreshDataByFilter("item");
    // 返回分组
    searchPanel.setFocusBack("group2020", false, 0);
    // 返回分组2
    searchPanel.setFocusBack("group2020", true, 0);

    // 还原
    ServerConfigManager::instance()->m_serverConfigs.clear();
    s.reset(ADDR(MainWindow, focusCurrentPage));
}

TEST_F(UT_RemoteManagementSearchPanel_Test, getListIndex)
{
    EXPECT_EQ(m_normalWindow->isVisible(), true);

    RemoteManagementPlugin *remotePlugin = m_normalWindow->findChild<RemoteManagementPlugin *>();
    RemoteManagementTopPanel *remoteTopPanel = remotePlugin->getRemoteManagementTopPanel();
    EXPECT_NE(remoteTopPanel, nullptr);
    EXPECT_EQ(remoteTopPanel->isVisible(), true);

    RemoteManagementSearchPanel *searchPanel = remoteTopPanel->findChild<RemoteManagementSearchPanel *>();
    int listIndex = searchPanel->getListIndex();
    EXPECT_EQ(listIndex, -1);
}

/*******************************************************************************
 1. @函数:    onItemClicked
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-23
 4. @说明:    点击事件
*******************************************************************************/
TEST_F(UT_RemoteManagementSearchPanel_Test, onItemClicked)
{
    // 初始化搜索界面
    RemoteManagementSearchPanel searchPanel;
    searchPanel.show();

    // 初始化数据
    ServerConfig config;
    config.m_serverName = "test_item";
    config.m_address = "127.0.0.1";
    config.m_userName = "dzw";
    config.m_port = "22";
    // 添加数据到列表中
    // 分组数据存储结构
    QList<ServerConfig *> list;
    list.append(&config);
    // 数据存储结构
    ServerConfigManager::instance()->m_serverConfigs.insert("", list);
    // 刷新列表,填充数据
    searchPanel.refreshDataByFilter("item");

    // 模拟数据被点击
    // 传来被点击的key值
    searchPanel.onItemClicked("test_item");
    // 清空测试数据
    ServerConfigManager::instance()->m_serverConfigs.clear();
}

/*******************************************************************************
 1. @函数:    lambda
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-23
 4. @说明:    测试lambda表达式
*******************************************************************************/
TEST_F(UT_RemoteManagementSearchPanel_Test, lambda)
{
    // 初始化界面
    RemoteManagementSearchPanel searchPanel;
    searchPanel.show();

    // 发送焦点切出信号
//    emit searchPanel.m_listWidget->focusOut(Qt::TabFocusReason);
//    searchPanel.show();
    emit searchPanel.m_listWidget->focusOut(Qt::BacktabFocusReason);
    // 切换主题
    emit DApplicationHelper::instance()->themeTypeChanged(DApplicationHelper::DarkType);
    emit DApplicationHelper::instance()->themeTypeChanged(DApplicationHelper::LightType);
}
#endif
