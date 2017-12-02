#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <node.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    vector<Node*> tree;
    //Add root
    QString rootName = ui->tableWidget->item(0,0)->text();
    int rootTime = ui->tableWidget->item(0,2)->text().toInt();
    Node* root = new Node(rootName, rootTime);
    root->ID = 0;
    tree.push_back(root);

    //Add root's children
    QString firstChildren = ui->tableWidget->item(0,1)->text();
    QStringList list1Children = firstChildren.split(',', QString::SkipEmptyParts);
    for(int i = 0; i <list1Children.size(); i++)
    {
        Node* newNode = new Node(0,list1Children[i]);
        root->addChild(newNode);
        tree.push_back(newNode);
    }


    //Add more node
    for(int i = 1; i<19; i++)
    {

        if(ui->tableWidget->item(i,0) && ui->tableWidget->item(i,2))
        {
            QString currentText = ui->tableWidget->item(i,0)->text();
            int currentTime = ui->tableWidget->item(i,2)->text().toInt();
            if(!currentText.contains(',')) //If there is only one Node
            {
                for(int j = 0; j < root->groupSameName(currentText).size() ;j++ )
                {
                    root->groupSameName(currentText)[j]->setTime(currentTime);
                }

                if(ui->tableWidget->item(i,1))
                {
                    QString currentChildren = ui->tableWidget->item(i,1)->text();
                    QStringList listCurChildren = currentChildren.split(',', QString::SkipEmptyParts);
                    for(int k = 0; k <listCurChildren.size(); k++)
                    {

                        for(int j = 0; j < root->groupSameName(currentText).size() ;j++ )
                        {
                            Node* newNode = new Node(root->groupSameName(listCurChildren[k]).size(), listCurChildren[k]);
                            root->groupSameName(currentText)[j]->addChild(newNode);
                            tree.push_back(newNode);
                        }
                    }

                }


            } else //If there are a list of nodes
            {               
                QStringList listChildren = currentText.split(',', QString::SkipEmptyParts);

                for(int k=0; k < listChildren.size(); k++)
                {
                    for(int j = 0; j < root->groupSameName(listChildren[k]).size() ;j++ )
                    {
                        root->groupSameName(listChildren[k])[j]->setTime(currentTime);
                    }


                    if(ui->tableWidget->item(i,1))
                    {
                        QString currentChildren = ui->tableWidget->item(i,1)->text();
                        QStringList listCurChildren = currentChildren.split(',', QString::SkipEmptyParts);
                        for(int l = 0; l <listCurChildren.size(); l++)
                        {

                            for(int m = 0; m < root->groupSameName(listChildren[k]).size() ;m++ )
                            {
                                Node* newNode = new Node(root->groupSameName(listCurChildren[l]).size(), listCurChildren[l]);
                                root->groupSameName(listChildren[k])[m]->addChild(newNode);
                                tree.push_back(newNode);
                            }
                        }

                    }
                }
             }
        }



    }


    qDebug() << tree.size();
    Node* CKNode = new Node();
    CKNode = root;
    int TCK = 0;
    for(int n =0; n < tree.size(); n++)
    {
        if(tree[n]->sumOfTime() > TCK)
        {
            TCK = tree[n]->sumOfTime();
            CKNode = tree[n];
        }
    }

    root->TCK = TCK;
    QString TCKString = QString::number(TCK);
    ui->label_2->setText("Tck = " + TCKString + "(ca)");
    ui->label_3->setText(CKNode->findAncestor());

    ui->label_4->setPixmap(root->show());
}

void MainWindow::on_pushButton_2_clicked()
{

    vector<Node*> tree;
    //Add root
    QString rootName = ui->tableWidget->item(0,0)->text();
    int rootTime = ui->tableWidget->item(0,2)->text().toInt();
    Node* root = new Node(rootName, rootTime);
    root->ID = 0;
    tree.push_back(root);

    //Add root's children
    QString firstChildren = ui->tableWidget->item(0,1)->text();
    QStringList list1Children = firstChildren.split(',', QString::SkipEmptyParts);
    for(int i = 0; i <list1Children.size(); i++)
    {
        Node* newNode = new Node(0,list1Children[i]);
        root->addChild(newNode);
        tree.push_back(newNode);
    }


    //Add more node
    for(int i = 1; i<19; i++)
    {

        if(ui->tableWidget->item(i,0) && ui->tableWidget->item(i,2))
        {
            QString currentText = ui->tableWidget->item(i,0)->text();
            int currentTime = ui->tableWidget->item(i,2)->text().toInt();
            if(!currentText.contains(',')) //If there is only one Node
            {
                for(int j = 0; j < root->groupSameName(currentText).size() ;j++ )
                {
                    root->groupSameName(currentText)[j]->setTime(currentTime);
                }

                if(ui->tableWidget->item(i,1))
                {
                    QString currentChildren = ui->tableWidget->item(i,1)->text();
                    QStringList listCurChildren = currentChildren.split(',', QString::SkipEmptyParts);
                    for(int k = 0; k <listCurChildren.size(); k++)
                    {

                        for(int j = 0; j < root->groupSameName(currentText).size() ;j++ )
                        {
                            Node* newNode = new Node(root->groupSameName(listCurChildren[k]).size(), listCurChildren[k]);
                            root->groupSameName(currentText)[j]->addChild(newNode);
                            tree.push_back(newNode);
                        }
                    }

                }


            } else //If there are a list of nodes
            {
                QStringList listChildren = currentText.split(',', QString::SkipEmptyParts);

                for(int k=0; k < listChildren.size(); k++)
                {
                    for(int j = 0; j < root->groupSameName(listChildren[k]).size() ;j++ )
                    {
                        root->groupSameName(listChildren[k])[j]->setTime(currentTime);
                    }


                    if(ui->tableWidget->item(i,1))
                    {
                        QString currentChildren = ui->tableWidget->item(i,1)->text();
                        QStringList listCurChildren = currentChildren.split(',', QString::SkipEmptyParts);
                        for(int l = 0; l <listCurChildren.size(); l++)
                        {

                            for(int m = 0; m < root->groupSameName(listChildren[k]).size() ;m++ )
                            {
                                Node* newNode = new Node(root->groupSameName(listCurChildren[l]).size(), listCurChildren[l]);
                                root->groupSameName(listChildren[k])[m]->addChild(newNode);
                                tree.push_back(newNode);
                            }
                        }

                    }
                }
             }
        }



    }


    qDebug() << tree.size();
    Node* CKNode = new Node();
    CKNode = root;
    int TCK = 0;
    for(int n =0; n < tree.size(); n++)
    {
        if(tree[n]->sumOfTime() > TCK)
        {
            TCK = tree[n]->sumOfTime();
            CKNode = tree[n];
        }
    }

    root->TCK = TCK;
    QString TCKString = QString::number(TCK);
    ui->label_2->setText("Tck = " + TCKString + "(ca)");
    ui->label_3->setText(CKNode->findAncestor());

    ui->label_4->setPixmap(root->show2());
}
