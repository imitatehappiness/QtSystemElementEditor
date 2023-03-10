#include "systemelementeditor.h"

#include <QApplication>
#include <QProxyStyle>
#include <QStyleFactory>
#include <QDir>
#include <QMessageBox>

const QString FONT_FAMILY_APP = "Times";
const uint FONT_SIZE_APP = 9;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    a.setStyle(new QProxyStyle(QStyleFactory::create("Fusion")));
    a.setFont(QFont(FONT_FAMILY_APP, FONT_SIZE_APP));
    QString stylePath = QDir::currentPath();
    stylePath = stylePath.left(stylePath.lastIndexOf(QChar('/'))) + "/SystemElementEditor/resources/style/appstyles.qss";
    QFile styleFile(stylePath);
    styleFile.open(QFile::ReadOnly);
    QString styleQSS = styleFile.readAll();

    if (styleQSS.length()==0){
        QMessageBox mBox;
        mBox.setIcon(QMessageBox::Warning);
        mBox.setText("Error appstyles.qss reading!");
        mBox.setButtonText(QMessageBox::Ok, "Ok");
        mBox.exec();
    }
    a.setStyleSheet(styleQSS);

    SystemElementEditor w;
    w.show();
    return a.exec();
}
