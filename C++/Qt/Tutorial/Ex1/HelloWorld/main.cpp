/****************************************************************
**
** Qt tutorial 1
**
****************************************************************/

#include <QApplication>
#include <QPushButton>
#include <qfont.h>
#include <QVBoxLayout>

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    QWidget *window = new QWidget;
    QVBoxLayout *box = new QVBoxLayout ;
    QPushButton *quit = new QPushButton("Quit");

    quit->setFont( QFont( "Times", 18, QFont::Bold ) );
    QObject::connect( quit, SIGNAL(clicked()), &a, SLOT(quit()) );

    box->addWidget(quit);
    window->setLayout(box);
    window->show();

    return a.exec();
}
