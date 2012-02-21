/*
 * Cantata
 *
 * Copyright (c) 2011-2012 Craig Drummond <craig.p.drummond@gmail.com>
 *
 * ----
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "devicepropertiesdialog.h"
#include "devicepropertieswidget.h"
#include <KDE/KGlobal>
#include <KDE/KLocale>

DevicePropertiesDialog::DevicePropertiesDialog(QWidget *parent)
    : KDialog(parent)
{
    setButtons(KDialog::Ok|KDialog::Cancel);
    setCaption(i18n("Device Properties"));
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::WindowModal);
    devProp=new DevicePropertiesWidget(this);
    setMainWidget(devProp);
}

void DevicePropertiesDialog::show(const QString &path, const QString &coverName, const Device::Options &opts, int props)
{
    devProp->update(path, coverName, opts, props);
    connect(devProp, SIGNAL(updated()), SLOT(enableOkButton()));
    KDialog::show();
    enableButtonOk(false);
}

void DevicePropertiesDialog::enableOkButton()
{
    enableButtonOk(devProp->isSaveable());
}

void DevicePropertiesDialog::slotButtonClicked(int button)
{
    switch (button) {
    case KDialog::Ok:
        emit updatedSettings(devProp->music(), devProp->cover(), devProp->settings());
        break;
    case KDialog::Cancel:
        emit cancelled();
        reject();
        break;
    default:
        break;
    }

    if (KDialog::Ok==button) {
        accept();
    }

    KDialog::slotButtonClicked(button);
}
