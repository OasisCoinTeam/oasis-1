// Copyright (c) 2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qt/oasis/sendchangeaddressdialog.h"
#include "qt/oasis/forms/ui_sendchangeaddressdialog.h"
#include "walletmodel.h"
#include "qt/oasis/qtutils.h"

SendChangeAddressDialog::SendChangeAddressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendChangeAddressDialog)
{
    ui->setupUi(this);
    this->setStyleSheet(parent->styleSheet());

    // Container
    ui->frame->setProperty("cssClass", "container-dialog");

    // Text
    ui->labelTitle->setText(tr("Custom Change Address"));
    ui->labelTitle->setProperty("cssClass", "text-title-dialog");

    ui->labelMessage->setText(tr("The remainder of the value resultant from the inputs minus the outputs value goes to the \"change\" OASIS address"));
    ui->labelMessage->setProperty("cssClass", "text-main-grey");

    ui->lineEditAddress->setPlaceholderText("Enter OASIS address (e.g oWBxLjXs5ywmmses1utC... ");
    initCssEditLine(ui->lineEditAddress, true);

    // Buttons
    ui->btnEsc->setText("");
    ui->btnEsc->setProperty("cssClass", "ic-close");

    ui->btnCancel->setProperty("cssClass", "btn-dialog-cancel");
    ui->btnSave->setText("SAVE");
    setCssBtnPrimary(ui->btnSave);

    connect(ui->btnEsc, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnSave, &QPushButton::clicked, [this](){ selected = true; accept(); });
}

void SendChangeAddressDialog::setAddress(QString address){
    ui->lineEditAddress->setText(address);
}

bool SendChangeAddressDialog::getAddress(WalletModel *model, QString *retAddress){
    QString address = ui->lineEditAddress->text();
    if(!address.isEmpty() && model->validateAddress(address)){
        *retAddress = address;
        return true;
    }
    return false;
}

void SendChangeAddressDialog::showEvent(QShowEvent *event)
{
    if (ui->lineEditAddress) ui->lineEditAddress->setFocus();
}

SendChangeAddressDialog::~SendChangeAddressDialog(){
    delete ui;
}