#include "view.h"
#include "ui_view.h"
#include <iostream>
#include <fstream>

using namespace std;

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

void View::set_obj_graphe(Graphe graphe){
    this->graphe = graphe;
    this->generer_graphe();
}

void View::generer_graphe(){
    ofstream fichier("graph_test", ios::out | ios::trunc);
    if(fichier)
           {
        fichier << "digraph g {" << endl;
        //fichier << "size=\"8,5\";" << endl;
        fichier << "rankdir=\"LR\";" << endl;
        // if etat final
        //fichier << "node [shape = doublecircle];2 A;" << endl;

        //fichier << "node [shape = circle];" << endl;

        //fichier << "A -> B [ label = \"bonjour\" ];" << endl;

        fichier << this->graphe.affichageUI();
        fichier << "}" << endl;
        fichier.close();
    }
    system("dot -Tpng graph_test -o outfile.png");

    this->setGraph("./outfile.png");

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
 * cette fonction retourne le mot qu'elle ajoute pour l'ajouter au traitement
 */
void View::ajouter_mot(){
    QString mot;
    mot = ui->LE_ajout_mot->text();
    std::string test = mot.toUtf8().constData();
    mot += "\n";

    QString dictionnaire;
    dictionnaire = ui->TE_dictionnaire->toPlainText();

    dictionnaire +=  mot;
    ui->TE_dictionnaire->setPlainText(dictionnaire);
    this->graphe.dictionaire.push_back(test);

    //this->generer_graphe();

}

void View::step_forward(){
    this->graphe.rendreZR(1);
    this->generer_graphe();
}

void View::step_backward(){
    this->graphe = Graphe(this->graphe.alphabet, this->graphe.dictionaire);
    this->generer_graphe();
}

void View::finish(){
    this->graphe.rendreZR(999);
    this->generer_graphe();
}

