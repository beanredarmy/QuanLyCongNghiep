#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<vector>
#include<QString>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
using namespace std;


class Node
{
public:
    QString name;
    int time;
    vector<Node*> copy;
    Node* parent;
    vector<Node*>  children;

public:
    int ID;
    int TCK;
    Node();
    void init(QGraphicsScene* scene, QGraphicsView* view);
    Node(QString xName);
    Node(QString xName, int xTime);
    Node(int xID, QString xName);

    Node* SearchNode(QString xName);
    void addChild(Node* xChild);
    void setTime(int xTime);

    void searchNodeVec(QString xName, vector<Node *> *theVector);
    QString findAncestor();

    int sumOfTime();

    vector<Node*> groupSameName(QString xName);


    QByteArray _prepareGraph();
    void _graphWalk(Node* p,  QTextStream* stream);
    QPixmap show();

    QByteArray _prepareGraph2();
    void _graphWalk2(Node* p,  QTextStream* stream);
    void _graphWalk2addon(Node* p,  QTextStream* stream);
    void _timeAxisaddon(Node* p,  QTextStream* stream);
    QPixmap show2();

    QGraphicsScene* _scene;
    QGraphicsView* _view;

};

#endif // NODE_H
