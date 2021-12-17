#ifndef SCANNER_H
#define SCANNER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Scanner; }
QT_END_NAMESPACE

class Scanner : public QWidget
{
    Q_OBJECT

public:
    Scanner(QWidget *parent = nullptr);
    ~Scanner();



private slots:
    void on_scanButton_clicked();


private:
    Ui::Scanner *ui;
    std::vector<int> m_ports;
    QString m_hostnameStr;
    QString m_portsStr;
};
#endif // SCANNER_H
