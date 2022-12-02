/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#include "MainDialog.hpp"
#include "m64p_types.h"
#include "m64p_config.h"
#include "../module.h"

using namespace UserInterface;

MainDialog::MainDialog(QWidget* parent) : QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint)
{
    this->setupUi(this);

    this->DisplayListToGraphicsPluginCheckBox->setChecked(ConfigGetParamBool(l_ConfigRsp, KEY_DisplayListToGraphicsPlugin));
    this->AudioListToAudioPluginCheckBox->setChecked(ConfigGetParamBool(l_ConfigRsp, KEY_AudioListToAudioPlugin));
    this->WaitForCPUHostCheckBox->setChecked(ConfigGetParamBool(l_ConfigRsp, KEY_WaitForCPUHost));
    this->SupportCPUSemaphoreLockCheckBox->setChecked(ConfigGetParamBool(l_ConfigRsp, KEY_SupportCPUSemaphoreLock));
}

MainDialog::~MainDialog()
{
}

void MainDialog::on_buttonBox_clicked(QAbstractButton* button)
{
    QPushButton *pushButton = (QPushButton *)button;
    QPushButton *okButton = this->buttonBox->button(QDialogButtonBox::Ok);

    if (pushButton != okButton)
    {
        return;
    }

    // checkboxes
    int DisplayListToGraphicsPluginValue = this->DisplayListToGraphicsPluginCheckBox->isChecked() ? 1 : 0; //(ConfigGetParamBool(l_ConfigRsp, KEY_DisplayListToGraphicsPlugin));
    int AudioListToAudioPluginValue = this->AudioListToAudioPluginCheckBox->isChecked() ? 1 : 0; //(ConfigGetParamBool(l_ConfigRsp, KEY_AudioListToAudioPlugin));
    int WaitForCPUHostValue = this->WaitForCPUHostCheckBox->isChecked() ? 1 : 0; //(ConfigGetParamBool(l_ConfigRsp, KEY_WaitForCPUHost));
    int SupportCPUSemaphoreLockValue = this->SupportCPUSemaphoreLockCheckBox->isChecked() ? 1 : 0; //(ConfigGetParamBool(l_ConfigRsp, KEY_SupportCPUSemaphoreLock));

    ConfigSetParameter(l_ConfigRsp, KEY_DisplayListToGraphicsPlugin, M64TYPE_BOOL, &DisplayListToGraphicsPluginValue);
    ConfigSetParameter(l_ConfigRsp, KEY_AudioListToAudioPlugin, M64TYPE_BOOL, &AudioListToAudioPluginValue);
    ConfigSetParameter(l_ConfigRsp, KEY_WaitForCPUHost, M64TYPE_BOOL, &WaitForCPUHostValue);
    ConfigSetParameter(l_ConfigRsp, KEY_SupportCPUSemaphoreLock, M64TYPE_BOOL, &SupportCPUSemaphoreLockValue);

    ConfigSaveSection("rsp-cxd4");
}
