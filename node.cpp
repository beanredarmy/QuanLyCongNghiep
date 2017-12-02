#include "node.h"
#include <QFile>
#include <QDebug>

Node::Node()
{
    this->name = "";
    this->time = 0;
    this->parent = NULL;
}

void Node::init(QGraphicsScene* scene, QGraphicsView *view)
{
    this->_scene = scene;
    this->_view = view;
}

Node::Node(QString xName)
{
    this->name = xName;
    this->time = 0;
    this->parent = NULL;
}

Node::Node(QString xName, int xTime)
{
    this->name = xName;
    this->time = xTime;
    this->parent = NULL;
}

Node::Node(int xID, QString xName)
{
    this->ID = xID;
    this->name = xName;
    this->time = 0;
    this->parent = NULL;
}



Node* Node::SearchNode(QString xName)
{

    if(this->name == xName)
    {
        return this;
    } else
    {
        if(this->children.size() == 0) return NULL;
        else
        {
            for(int i=0; i < this->children.size(); i++)
            {
                if(this->children[i]->SearchNode(xName) != NULL)
                {
                    return this->children[i]->SearchNode(xName);
                    break;
                }

            }
        }

    }

}

void Node::searchNodeVec(QString xName, vector<Node *> *theVector)
{

    if(this->name == xName) theVector->push_back(this);
    else
    {
            for(int i = 0; i<this->children.size();i++)
            {
                this->children[i]->searchNodeVec(xName, theVector);
            }
    }

}

QString Node::findAncestor()
{
    if(this->parent == NULL)
    {
        return (this->name);
    }
    else return (this->parent->findAncestor() + " -> " + this->name );
}


int Node::sumOfTime()
{
    if(this->parent == NULL)
    {
        return this->time;
    }
    else return (this->time + this->parent->sumOfTime());
}




vector<Node *> Node::groupSameName(QString xName)
{
    vector<Node*> vectorOfName;
    this->searchNodeVec(xName, &vectorOfName);

    return vectorOfName;
}


void Node::addChild(Node* xChild)
{

    xChild->parent = this;
    this->children.push_back(xChild);
}



void Node::setTime(int xTime)
{
    this->time = xTime;
}


//-------------------------------------------------------------------------------------------------------------

void Node::_graphWalk(Node *p, QTextStream *stream)
{
    if (p != NULL){
        *stream << "\t\t" << "n" << p->name << p->ID << "[shape = box, label=\"" << p->name << "\n" << p->time <<"\"];" << endl;

        if(p->children.size() != 0)
        {
            for(int i=0; i < p->children.size(); i++)
            {

               *stream << "\t\tn" << p->name << p->ID << "--" << "n" << p->children[i]->name << p->children[i]->ID <<  ";" << endl;
                this->_graphWalk(p->children[i], stream);
                //"[ minlen =" << (p->children[i]->time + 1)/2 << "]" <<
            }
        }

    }
}

QByteArray Node::_prepareGraph()
{
    QByteArray a = QByteArray();

    QTextStream stream(&a, QIODevice::ReadWrite);
    stream << "graph ""{" << endl;
    stream << "splines= ortho" << endl;
    stream << "overlap = false" << endl;
    stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
    stream << "\tsubgraph cluster17{" << endl;

    this->_graphWalk(this, &stream);
    stream << "\t}\n" << "}" << endl;

    QFile file("myfile.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream a(&file);
        a << "graph ""{" << endl;
        a << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
        a << "\tsubgraph cluster17{" << endl;

        this->_graphWalk(this, &a);
        a << "\t}\n" << "}" << endl;
        file.flush();
        file.close();
        qDebug() << "ahihi";
    }

    stream.flush();
    return a;

}



QPixmap Node::show()
{
    QProcess* p = new QProcess();
    QByteArray a = this->_prepareGraph();

    p->setProcessChannelMode(QProcess::MergedChannels);
    p->start("dot", QStringList() << "-Tpng");
    p->write(a);

    QByteArray data;
    QPixmap pixmap = QPixmap();

    while(p->waitForReadyRead(100)){
        data.append(p->readAll());
    }

    pixmap.loadFromData(data);


    return pixmap;

}


//----------------------------------------------------------------------------------------------------
void Node::_graphWalk2(Node *p, QTextStream *stream)
{
    if (p != NULL){
        QString allChildrenName = "";
        for(int k =0; k < p->children.size();k++)
        { 
            allChildrenName  += "+" + p->children[k]->name ;
        }
        allChildrenName.remove(0,1);

        *stream << "\t\t" << "n" << p->name << p->ID << "[shape = box, label=\"" << allChildrenName <<"\"];" << endl;

        if(p->children.size() != 0)
        {
            for(int i=0; i < p->children.size(); i++)
            {

               *stream << "\t\tn" << p->name << p->ID << "->" << "n" << p->children[i]->name << p->children[i]->ID << "[dir=back, minlen =" << (p->children[i]->time) << ", label=\"" << p->children[i]->name << ":" << p->children[i]->time<<"\"]" << ";" << endl;
                this->_graphWalk2(p->children[i], stream);
                //"[ minlen =" << (p->children[i]->time + 1)/2 << "]" <<
            }
        }

    }
}

void Node::_graphWalk2addon(Node *p, QTextStream *stream)
{
    *stream << "\t\t" <<  "done" << "->" << "n" <<p->name << p->ID << "[dir=back, minlen =" << (p->time) << ", label=\"" << p->name << ":" << p->time<<"\"]" << ";" << endl;
}

void Node::_timeAxisaddon(Node *p, QTextStream *stream)
{
    *stream << "\tsubgraph cluster2{" << endl;
    for(int i = p->TCK; i>0; i--)
    {
         *stream <<"\t\t" << i <<"->"<< i-1 <<"[shape=circle,dir=back];" << endl;
    }
    *stream << "\t}\n"  << endl;
}



QByteArray Node::_prepareGraph2()
{
    QByteArray a = QByteArray();

    QTextStream stream(&a, QIODevice::ReadWrite);
    stream << "digraph""{" << endl;
    stream << "rankdir=RL" << endl;
    stream << "nodesep = 0.3" << endl;
    stream << "ranksep = 0.3" << endl;
    stream << "splines=polyline" << endl;
    stream << "overlap = false" << endl;
    stream << "\tnode[fontsize=12,margin=0,width=\".4\", height=\".3\"];" << endl;
    stream << "\tedge[fontsize=12];" << endl;
    stream << "\tsubgraph cluster3{" << endl;
    this->_graphWalk2addon(this, &stream);
    this->_graphWalk2(this, &stream);
    stream << "\t}\n"  << endl;
    this->_timeAxisaddon(this, &stream);
    stream << "}" << endl;


    QFile file("myfile.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream a(&file);
        a << "graph ""{" << endl;
        a << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
        a << "\tsubgraph cluster0{" << endl;

        this->_graphWalk2(this, &a);
        a << "\t}\n" << "}" << endl;

        file.flush();
        file.close();
        qDebug() << "ahihi";
    }

    stream.flush();
    return a;

}



QPixmap Node::show2()
{
    QProcess* p = new QProcess();
    QByteArray a = this->_prepareGraph2();

    p->setProcessChannelMode(QProcess::MergedChannels);
    p->start("dot", QStringList() << "-Tpng");
    p->write(a);

    QByteArray data;
    QPixmap pixmap = QPixmap();

    while(p->waitForReadyRead(100)){
        data.append(p->readAll());
    }

    pixmap.loadFromData(data);


    return pixmap;

}





