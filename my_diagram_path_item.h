#ifndef MY_DIAGRAM_PATH_ITEM_H
#define MY_DIAGRAM_PATH_ITEM_H

namespace Ui
{
    class My_diagram_path_item;
}
class My_diagram_arrow;

#include"QGraphicsPathItem"

class My_diagram_path_item : public QGraphicsPathItem
{
public:
    enum { Type = UserType + 17 };//������������ Type �������� ���������� ��������������� ������. �� ������������ qgraphicsitem_cast(), ������� ������ ������������ ���������� ����������� ���������. ��������� UserType �������� ����������� ���������, ������� ����� ���� ���������������� ��� ������������ ��������.
    enum DiagramType { Actor = 11 };

    My_diagram_path_item(DiagramType diagramType, QMenu *contextMenu, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);


    void removeArrow(My_diagram_arrow *arrow);
    void removeArrows();
    DiagramType diagramType() const
        { return myDiagramType; }
    void addArrow(My_diagram_arrow *arrow);

    QPainterPath get_path() const
        { return myPath;      }
    QPixmap image() const;
    int type() const
        { return Type;}
    QPolygonF poligon();
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    DiagramType myDiagramType;//��� ������� (�������, ���� � �.�.)
    QPainterPath myPath;
    QMenu *myContextMenu;
    QList<My_diagram_arrow *> arrows;// ������ ������� ������� � ��� ���������
};

#endif // MY_DIAGRAM_PATH_ITEM_H
