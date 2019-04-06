#include <iostream>
#include <QtGui/QApplication>
#include <fstream>
#include <vector>


#include "view.h"
#include "graphe.h"


using namespace std;


using namespace std;

// pour graphviz https://stackoverflow.com/questions/45225761/generate-image-of-graphviz-graph-given-dot-text-c
//http://www.webgraphviz.com/ voir sample 4

void generer_graphe(Graphe graphe){
    ofstream fichier("graph_test", ios::out | ios::trunc);
    if(fichier)
           {
        fichier << "digraph g {" << endl;
        fichier << "size=\"8,5\"; \nrankdir=\"LR\";" << endl;
        // if etat final
        //fichier << "node [shape = doublecircle];2 A;" << endl;

        //fichier << "node [shape = circle];" << endl;

        //fichier << "A -> B [ label = \"bonjour\" ];" << endl;

        fichier << graphe.affichageUI();
        fichier << "}" << endl;
        fichier.close();
    }
    system("dot -Tpng graph_test -o outfile.png");
}


int main(int argc, char *argv[])
{
        QApplication app(argc, argv);

        View fenetre;

        std::vector<std::string> dict;
            dict.push_back("ab");
            dict.push_back("aa");
            dict.push_back("b");
            dict.push_back("bb");
            dict.push_back("aaa");

            std::vector<char> alpha;
            alpha.push_back('a');
            alpha.push_back('b');

            Graphe test = Graphe(alpha,dict);

        fenetre.show();
        fenetre.setAlphabet(alpha);
        fenetre.setDictionnaire(dict);

        generer_graphe(test);

        fenetre.setGraph("./outfile.png");



    return app.exec();
}


