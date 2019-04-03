#include <iostream>
#include <QtGui/QApplication>
#include <graphviz/gvc.h>
#include <fstream>
#include <vector>


#include "view.h"
#include "graphe.h"


using namespace std;


using namespace std;

int Noeud::id =0;

// pour graphviz https://stackoverflow.com/questions/45225761/generate-image-of-graphviz-graph-given-dot-text-c
//http://www.webgraphviz.com/ voir sample 4

void generer_graphe(){
    ofstream fichier("graph_test", ios::out | ios::trunc);
    if(fichier)
           {
        fichier << "digraph g {" << endl;
        fichier << "size=\"8,5\"" << endl;
        // if etat final
        fichier << "node [shape = doublecircle]; C A;" << endl;

        fichier << "node [shape = circle];" << endl;

        fichier << "A -> B [ label = \"une valeur\" ];" << endl;


        fichier << "}" << endl;
        fichier.close();
    }
    system("dot -Tpng graph_test -o outfile.png");
}
/*
std::vector<int> parcours_graphe(Noeud n, std::vector<int> noeuds_finaux){ // retourne la liste des états finaux
    if (n == null){ // condition d'arrêt si le graphe est vide
        return new std::vector<int>;
    }
    else {
        if (n.final()){ // si c'est un état final
            noeud_finaux.push_back(noeud.id); // on ajoute son id au état finaux
        }
        for each(noeud dans suivant de noeud){ // la il faut changer la classe noeud en mettant un vecteur de pointeur sur les noeuds suivant, sinon se demarder avec la mattric de ses morts
            std::vector<int> suite ;
            suite = parcours_graphe(noeud); // on récupère la suite
            noeuds_finaux = noeuds_finaux.insert(noeuds_finaux.begin(), suite.begin(), suite.end());// on la concatène au vecteur
        }
        return noeuds_finaux; // on ertourne la liste complete
    }
}
*/


int main(int argc, char *argv[])
{
        QApplication app(argc, argv);

        View fenetre;

        fenetre.show();
        fenetre.setAlphabet("coucou");
        fenetre.setDictionnaire("je suis un dictionanire entré automatiquement via le main, je dois etre long pour voir ce que ca donne à l'affichage");

        generer_graphe();

        fenetre.setGraph("/home/etudiant/build-test-Desktop-Debug/outfile.png");



    return app.exec();
}


