#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

#include "graphe.h"

using namespace std;

std::vector<int> Graphe::getFinals() const
{
    return finals;
}

void Graphe::setFinals(const std::vector<int> &value)
{
    finals = value;
}

std::vector<std::vector<std::vector<char>>> Graphe::getMatrice_adj() const
{
    return matrice_adj;
}

void Graphe::setMatrice_adj(const std::vector<std::vector<std::vector<char>>> &value)
{
    matrice_adj = value;
}

std::vector<char> Graphe::getAlphabet() const
{
    return alphabet;
}

void Graphe::setAlphabet(const std::vector<char> &value)
{
    alphabet = value;
}

std::vector<string> Graphe::getDictionaire() const
{
    return dictionaire;
}

void Graphe::setDictionaire(const std::vector<std::string> &value)
{
    dictionaire = value;
}

Graphe::Graphe(std::vector<char> alphabet,std::vector<std::string> dictionaire){
    this->alphabet = alphabet;
    this->dictionaire = dictionaire;
    this->matrice_adj.clear();
    int nbrEtatDepart = 1; // etat S
    for( std::string elt : this->dictionaire){
        nbrEtatDepart += elt.size();
    }
    for (int n = 0;n<nbrEtatDepart;n++){
        std::vector<char> liste = std::vector<char>(1,'$');
        this->matrice_adj.push_back(std::vector<std::vector<char>>(nbrEtatDepart,liste));
    }
    int etat = 0;
    for ( std::string mot : this->dictionaire){
        for (int j= 0;j<mot.size();j++){
            if(j==0){
                etat++;
                this->matrice_adj.at(0).at(etat)=Union(this->matrice_adj.at(0).at(etat),std::vector<char>(1,mot[j]));
                //this->matrice_adj.at(etat).at(0)=Union(this->matrice_adj.at(etat).at(0),std::vector<char>(1,mot[j]));
            }else{
                this->matrice_adj.at(etat).at(etat+1)=Union(this->matrice_adj.at(etat).at(etat+1),std::vector<char>(1,mot[j]));
                //this->matrice_adj.at(etat+1).at(etat)=Union(this->matrice_adj.at(etat+1).at(etat),std::vector<char>(1,mot[j]));
                etat++;

            }
        }
        this->finals.push_back(etat);

    }
    this->affichage();
    for(int elt : finals){
        std::cout << elt << " ";
    }
    std::cout<<std::endl;
    for(std::tuple<int, int,char> elt : listeArc()){
        std::cout<<"arc "<<std::get<0>(elt)<<"->"<<std::get<1>(elt)<<std::endl;
    }

}

void Graphe::affichage()
{
    for(int i = 0;i<this->matrice_adj.size();i++){
        for(int j = 0; j<this->matrice_adj.at(i).size();j++){
            if(this->matrice_adj.at(i).at(j).size()>1){
                std::cout << this->matrice_adj.at(i).at(j).at(1)<<"1";
            }else{
                if(this->matrice_adj.at(i).at(j).size()>0)
                    std::cout << this->matrice_adj.at(i).at(j).at(0)<<" ";
            }
        }
        std::cout << std::endl;
    }
    std::cout<<"________________________________________________"<<std::endl;
    for(int i = 0;i<this->matrice_adj.size();i++){
        for(int j = 0; j<this->matrice_adj.at(i).size();j++){
            if(this->matrice_adj.at(i).at(j).size()>2){
                std::cout << this->matrice_adj.at(i).at(j).at(2)<<"2";
            }else{
                if(this->matrice_adj.at(i).at(j).size()>0)
                    std::cout << this->matrice_adj.at(i).at(j).at(0)<<" ";
            }
        }
        std::cout << std::endl;
    }
    std::cout<<"________________________________________________"<<std::endl;
    for(int i = 0;i<this->matrice_adj.size();i++){
        for(int j = 0; j<this->matrice_adj.at(i).size();j++){
            if(this->matrice_adj.at(i).at(j).size()>3){
                std::cout << this->matrice_adj.at(i).at(j).at(3)<<"3";
            }else{
                 if(this->matrice_adj.at(i).at(j).size()>0)
                    std::cout << this->matrice_adj.at(i).at(j).at(0)<<" ";
            }
        }
        std::cout << std::endl;
    }
}

std::vector<std::tuple<int, int, char>> Graphe::listeArc()
{
    std::vector<std::tuple<int, int,char>> ret;
    for(int i = this->matrice_adj.size()-1;i>=0;i--)
        for( int j = this->matrice_adj.size()-1;j>=0;j--)
            for( int d = 0;d<this->matrice_adj.at(i).at(j).size();d++){
                if(this->matrice_adj.at(i).at(j).at(d)!='$')
                    ret.push_back(std::make_tuple(i,j,this->matrice_adj.at(i).at(j).at(d)));
            }
    return ret;

}

bool Graphe::checkDerterminisme(std::vector<int> &fusion){
    // verification que le graphe est déterministe
    std::vector<char> listSymbole;
    std::vector<int> premiereItSymb;
    fusion.clear();
    bool ret = true;
    for(int i = this->matrice_adj.size()-1;i>=0;i--){
        for( int j = this->matrice_adj.size()-1;j>=0;j--){
            for( int d = 0;d<this->matrice_adj.at(i).at(j).size();d++){
                if(this->matrice_adj.at(i).at(j).at(d)!='$'){
                    if(!(listSymbole.empty())&&fusion.empty()){
                        for(int k =0;listSymbole.size()>k;k++){
                            if( this->matrice_adj.at(i).at(j).at(d) == listSymbole.at(k)) {
                                    ret = false;
                                    fusion.push_back(j);
                                    fusion.push_back(premiereItSymb.at(k));
                            }
                    }

                    if(ret){
                            listSymbole.push_back(this->matrice_adj.at(i).at(j).at(d));
                            premiereItSymb.push_back(j);
                        }

                } else {
                    listSymbole.push_back(this->matrice_adj.at(i).at(j).at(d));
                    premiereItSymb.push_back(j);
               }
            }
}
        }
        listSymbole.clear();
        premiereItSymb.clear();
        }
    return ret;
}
bool Graphe::checkUniqFinal(std::vector<int> &fusion){
    // verifie qu'il y a bien que un état final
    fusion.clear();
    if(this->finals.size()>1){
        for(int elt : this->finals)
            fusion.push_back(elt);
        return false;}
    return true;
}

bool Graphe::checkZeroRever(std::vector<int> &fusion){
    // verifie qu'il n'y a pas deux (ou plusieurs) arc avec la même valeurs menant au même noeud
    for(tuple<int,int,char> elt : this->listeArc()){
        for(tuple<int,int,char> elt2 : this->listeArc()){
            if(std::get<0>(elt)!=std::get<0>(elt2)){
                if((std::get<1>(elt)==std::get<1>(elt2))&&(std::get<2>(elt)==std::get<2>(elt2))){
                        fusion.push_back(std::get<0>(elt));
                        fusion.push_back(std::get<0>(elt2));
                        std::sort(fusion.begin(),fusion.end());
                        return false;
                }
            }
        }
    }
    return true;
}

std::vector<std::vector<std::vector<char>>> Graphe::fusionNoeud(std::vector<int> &fusion){
    //fonction permettant de fusionner deux noeud en ajoutant les arc qui vont et qui vienne sur B a A puis en supprimant B4
    std::vector<std::vector<std::vector<char>>> ret;
    int rece = fusion.at(0);
        int supp = fusion.at(1);
        for(int i = 0;i<this->matrice_adj.size();i++){
            ret.push_back(std::vector<std::vector<char>>(this->matrice_adj.at(0).size()));
        }
        for(int i = 0;i<this->matrice_adj.size();i++){
            for(int j = 0; j<this->matrice_adj.at(i).size();j++){
                for( int d = 0;d<this->matrice_adj.at(i).at(j).size();d++){
                    ret.at(i).at(j).push_back(this->matrice_adj.at(i).at(j).at(d));
                    if(i==supp){
                        ret.at(rece).at(j)=Union(ret.at(rece).at(j),ret.at(i).at(j));
                        ret.at(j).at(rece)=Union(ret.at(j).at(rece),ret.at(j).at(i));

                    }
                }
            }
        }

        ret.at(rece).at(rece)=Union(ret.at(rece).at(rece),ret.at(rece).at(supp));
        ret.at(rece).at(rece)=Union(ret.at(rece).at(rece),ret.at(supp).at(rece));
        ret.erase(ret.begin()+supp);
        for(int i = 0;i<ret.at(0).size();i++){
            ret.at(i).erase(ret.at(i).begin()+supp);
        }
        fusion.erase(fusion.begin()+1);
        std::vector<int> newFinals;
        for(int m =0;m< this->finals.size();m++){
            if(this->finals.at(m)==supp){
                if(std::find(newFinals.begin(),newFinals.end(),rece)==newFinals.end())
                    newFinals.push_back(rece);
            }else{
                if(this->finals.at(m)<supp){
                    newFinals.push_back(this->finals.at(m));
                    }else{
                        newFinals.push_back(this->finals.at(m)-1);
                    }
                 }
            }
        std::sort(newFinals.begin(),newFinals.end());
        this->setFinals(newFinals);
        //this->affichage();
        return ret;
}
std::vector<char> clearDols(std::vector<char> list){
    if(list.size()>1){
        for(int i= 0;i<list.size();i++){
            if(list.at(i)=='$')
                list.erase(list.begin()+i);
        }
    }
    return list;


}

std::vector<char> Graphe::Union(std::vector<char> l1, std::vector<char> l2){
    std::vector<char> ret = l1;
    for(char elt : l2){
        if(elt!='$'){
            if(std::find(l1.begin(),l1.end(),elt)==l1.end()){
                ret.push_back(elt);
            }
        }

    }
    //l1 = clearDols(l1);
    if(ret.size()==0){
        ret.push_back('$');
    }
    return ret;
}

string Graphe::affichageUI()
{
    string ret = "node [shape = doublecircle];";
    for(auto elt : this->finals){
        ret += " "+std::to_string(elt);
    }
    ret+= ";\nnode [shape = circle];\n";
    for (tuple<int,int,char> arc:listeArc()){
        ret+= std::to_string(std::get<0>(arc))+" -> "+std::to_string(std::get<1>(arc))+" [ label = \""+std::get<2>(arc)+"\" ];\n";
    }
    return ret;
}

std::vector<std::vector<std::vector<char> > > Graphe::doublon()
{
    for(int i = 0;i<this->matrice_adj.size();i++){
        for(int j = 0; j<this->matrice_adj.at(i).size();j++){
            std::vector<char> symb;
            std::vector<char> tmp;
            for( int d = 0;d<this->matrice_adj.at(i).at(j).size();d++){
                if(std::find(symb.begin(),symb.end(),this->matrice_adj.at(i).at(j).at(d))!=symb.end()||matrice_adj.at(i).at(j).at(d)=='$'){
                }else{
                    symb.push_back(this->matrice_adj.at(i).at(j).at(d));
                    tmp.push_back(this->matrice_adj.at(i).at(j).at(d));
                }
            }
        matrice_adj.at(i).at(j)=tmp;
        }
    }
    std::vector<std::vector<std::vector<char>>> ret = this->matrice_adj;
    return ret;
}

void Graphe::rendreZR(int maxTour){
    // se sert des fonction précédente pour rendre le graphe zero_réversible
    //création du grapphe
    std::vector<int>  noeudFusion;
    bool fin = true;
    int compt = 0;
    while(fin&&compt<maxTour){
    if (checkDerterminisme(noeudFusion)){
        if (checkUniqFinal(noeudFusion)){
            if( checkZeroRever(noeudFusion)){
                    fin = false;
            }else{
                //std::cout<< "non ZR"<<std::endl;
                this->setMatrice_adj(this->fusionNoeud(noeudFusion));
            }
        }else{
            //std::cout<< "non one final"<<std::endl;
            this->matrice_adj = this->fusionNoeud(noeudFusion);
        }
    }else{
    //std::cout<< "non deterministe"<<std::endl;
    this->setMatrice_adj(this->fusionNoeud(noeudFusion));
    }
    //std::cout<<this->affichageUI();
    compt++;
    noeudFusion.clear();
    }
}

Graphe::Graphe(){
    this->alphabet.clear();
    this->dictionaire.clear();
    this->matrice_adj.clear();
    this->setFinals(std::vector<int>(1,0));
}
