/*
 *  Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
 *
 * Author:     zhaogongqiang <zhaogongqiang@uniontech.com>
 *
 * Maintainer: zhaogongqiang <zhaogongqiang@uniontech.com>
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

#ifndef TABRENAMEWIDGET_H
#define TABRENAMEWIDGET_H

#include <DLineEdit>
#include <DPushButton>
#include <DMenu>

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

class TabRenameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TabRenameWidget(bool isRemote, bool isSetting = false, QWidget *parent = nullptr);

    void initUi();
    void initChoseMenu();
    void initRemoteChoseMenu();
    void initNormalChoseMenu();
    void initConnections();

    void initLabel();
    void setLineEditText();

    DLineEdit *getInputedit() const;

private:
    bool m_isRemote = false;
    bool m_isSetting = false;

    QLabel *m_Label = nullptr;
    QHBoxLayout *m_layout = nullptr;

    DPushButton *m_choseButton = nullptr;
    DMenu *m_choseMenu = nullptr;
    DLineEdit *m_inputedit = nullptr;
};

#endif // TABRENAMEWIDGET_H
