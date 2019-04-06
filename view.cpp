#include "view.h"
#include "ui_view.h"
#include <iostream>


View::View(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View)
{
    ui->setupUi(this);

    connect(ui->B_ajouter, SIGNAL(clicked()), this, SLOT(ajouter_mot()));

    connect(ui->button_forward, SIGNAL(clicked()), this, SLOT(step_forward()));
    connect(ui->button_backward, SIGNAL(clicked()), this, SLOT(step_backward()));
    connect(ui->button_finish, SIGNAL(clicked()), this, SLOT(finish()));


}



void View::setAlphabet(std::vector<char> alpha){
    std::string alphabet = "";
    for (char mot : alpha){
        alphabet += mot;
        alphabet += " ";
    }

    ui->TE_alphabet->setPlainText(QString::fromStdString(alphabet));
}

void View::setDictionnaire(std::vector<std::string> dict){
    std::string dictionnaire = "";
    for (std::string mot : dict){
        dictionnaire += mot + "\n";
    }
    ui->TE_dictionnaire->setPlainText(QString::fromStdString(dictionnaire));

}

void View::setGraph(std::string chemin_fichier_png){

    QPixmap image;
    image = QPixmap(QString::fromStdString(chemin_fichier_png));

    ui->label_graph->setPixmap(image);
}


View::~View()
{
    delete ui;
}

/*
 * SLOTS
 *
 */


/*
 * cette fonction retourne le mot qu'elle ajoute pour pour l'ajouter au traitement
 */
std::string View::ajouter_mot(){
    QString mot;
    mot = ui->LE_ajout_mot->text();

    QString dictionnaire;
    dictionnaire = ui->TE_dictionnaire->toPlainText();

    dictionnaire +=  mot;
    ui->TE_dictionnaire->setPlainText(dictionnaire);

    return mot.toUtf8().constData();
}

void View::step_forward(){

}

void View::step_backward(){

}

void View::finish(){

}

