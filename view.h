#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

namespace Ui {
class View;
}

class View : public QMainWindow
{
    Q_OBJECT

public:
    explicit View(QWidget *parent = 0);
    ~View();
    void setAlphabet(std::string alphabet);
    void setDictionnaire(std::string dictionnaire);
    void setGraph(std::string chemin_fichier_png);

private:
    Ui::View *ui;

public slots:
     std::string chemin_fichier();
     std::string ajouter_mot();

     void step_forward();
     void step_backward();
     void finish();

};

#endif // VIEW_H
