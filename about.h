#ifndef ABOUT_H
#define ABOUT_H

# include <QDialog>
# include "ui_about.h"

class AboutDlg : public QDialog
{
   Q_OBJECT

public:
   AboutDlg(QWidget *parent = 0) : QDialog(parent)
   {
      ui.setupUi(this);
   };

private:
   Ui::AboutDlg ui;
};

#endif
