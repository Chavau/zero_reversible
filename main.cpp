#include <iostream>
#include <QtGui/QApplication>
#include <fstream>
#include <vector>


#include "view.h"


// pour graphviz https://stackoverflow.com/questions/45225761/generate-image-of-graphviz-graph-given-dot-text-c
//http://www.webgraphviz.com/ voir sample 4


int main(int argc, char *argv[])
{
        QApplication app(argc, argv);

        View fenetre;

        std::vector<std::string> dict;
            dict.push_back("ab");
            dict.push_back("aac");
            dict.push_back("aab");
            //dict.push_back("bb");
            dict.push_back("aba");

            std::vector<char> alpha;
            alpha.push_back('a');
            alpha.push_back('b');
            alpha.push_back('c');

            Graphe test = Graphe(alpha,dict);

        fenetre.show();
        fenetre.setAlphabet(alpha);
        fenetre.setDictionnaire(dict);
        fenetre.set_obj_graphe(test);


    return app.exec();
}


