#include "scanner.h"
#include "ui_scanner.h"
#include <QtDebug>
#include <QAbstractSocket>
#include <QTcpSocket>

Scanner::Scanner(QWidget *parent) : QWidget(parent), ui(new Ui::Scanner)
{
    ui->setupUi(this);
}

Scanner::~Scanner()
{
    delete ui;
}


void Scanner::on_scanButton_clicked()
{
   ui->portStatusDisplay->clear();
   m_ports.clear();

   m_hostnameStr = ui->hostName->text();
   m_portsStr = ui->portsToScan->text();
   
   QStringList splitPorts = m_portsStr.split(",");

   for(auto a : splitPorts)
   {
       if(a.contains("-"))
       {
           QStringList fromTo = a.split("-");
           if(fromTo[0].toInt() < fromTo[1].toInt())
           {
               for(int i = fromTo[0].toInt(); i <= fromTo[1].toInt(); i++)
               {
                   m_ports.push_back(i);
               }
           }
           else
           {
               for(int i = fromTo[1].toInt(); i <= fromTo[0].toInt(); i++)
               {
                   m_ports.push_back(i);
               }
           }
       }
       else
       {
           m_ports.push_back(a.toInt());
       }
    }

   QTcpSocket* socket = new QTcpSocket(this);

   for(auto port : m_ports)
   {
        socket->connectToHost(m_hostnameStr, port);

        if(!socket->waitForConnected(1000))
        {
            ui->portStatusDisplay->setTextColor(Qt::red);
            ui->portStatusDisplay->append("port: " + QString::number(port) + " not connected");
            ui->portStatusDisplay->repaint();
        }
        else
        {
            socket->disconnectFromHost();
            ui->portStatusDisplay->setTextColor(Qt::green);
            ui->portStatusDisplay->append("port: " + QString::number(port) + " connected");
            ui->portStatusDisplay->repaint();
        }
        //hallo
   }
}
