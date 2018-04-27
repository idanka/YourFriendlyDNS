#include "smallhttpserver.h"

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
with this program; if not, write to the Free Software Foundation, Inc*/

SmallHTTPServer::SmallHTTPServer(QObject *parent)
{
    Q_UNUSED(parent);
    html = "<html><head><title>Your Landing Page!</title><body bgcolor=\"skyblue\"><input type=\"text\" name=\"urlfield\" id=\"urlfield\" maxlength=\"200\" size=\"75\"></input><input type=\"button\" name=\"send\" id=\"send\" value=\"Go\" onclick=\"go()\"></input><h1>Your Landing Page!</h1> <a href=\"https://startpage.com/\">Start!</a><script>function go() { parent.window.location.href=document.getElementById(\"urlfield\").value; }</script></body></html>";
    response_header=R"(HTTP/1.1 200 OK
Content-Type: %1
Content-Encoding: %2
Content-Length: %3
Accept-Ranges: %4
Date: %5
Connection: %6)";
    response_header += "\r\n\r\n";
    contentType = "text/html", encodingType = "identity", acceptRanges = "bytes", connection = "close";

    connect(this, &QTcpServer::newConnection, this, &SmallHTTPServer::returnIndexPage);
}

bool SmallHTTPServer::startServer(QHostAddress address, quint16 port)
{
    if(port == 0)
    {
        qDebug() << "HTTP server disabled in settings (set to port 0)";
        return false;
    }
    return listen(address, port);
}

void SmallHTTPServer::setHTML(QString html)
{
    this->html = html;
}

void SmallHTTPServer::returnIndexPage()
{
    QTcpSocket *socket = nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);

    QString contentLength = QString("%1").arg(html.size());
    QString currentDateTime = QDateTime::currentDateTime().toString();
    QString response = response_header.arg(contentType).arg(encodingType).arg(contentLength).arg(acceptRanges).arg(currentDateTime).arg(connection);
    response += html;

    socket->write(response.toUtf8());
    socket->disconnectFromHost();
    //qDebug() << "[" << socket->socketDescriptor() << "] Wrote index page:" << response;
}
