#include "indexhtml.h"
#include "ui_indexhtml.h"

/* YourFriendlyDNS - A really awesome multi-platform (lin,win,mac,android) local caching and proxying dns server!
Copyright (C) 2018  softwareengineer1 @ github.com/softwareengineer1
Support my work so I can keep bringing you great free and open software!
I'm going entirely 100% free software this year in 2018 (and onwards I want to) :)
Everything I make will be released under a free software license! That's my promise!
If you want to contact me another way besides through github, insert your message into the blockchain with a BCH/BTC UTXO! ^_^
Thank you for your support!
BCH: bitcoincash:qzh3knl0xeyrzrxm5paenewsmkm8r4t76glzxmzpqs
BTC: 1279WngWQUTV56UcTvzVAnNdR3Z7qb6R8j

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

IndexHTML::IndexHTML(QWidget *parent) : QMainWindow(parent),ui(new Ui::IndexHTML)
{
    ui->setupUi(this);
}

IndexHTML::~IndexHTML()
{
    delete ui;
}

void IndexHTML::setHTML(QString &html)
{
   ui->html->clear();
   ui->html->appendPlainText(html);
}

QString IndexHTML::getHTML()
{
    return ui->html->toPlainText();
}
void IndexHTML::on_okButton_clicked()
{
    QString html = ui->html->toPlainText();
    emit htmlChanged(html);
    hide();
}
