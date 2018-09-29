#include "my_diagram_text_item.h"
#include "my_diagram_scene.h"

#include <QTextDocument>
My_diagram_text_item::My_diagram_text_item(QGraphicsItem *parent, QGraphicsScene *scene,ItemTextType itemTextType,NameTextType nameTextType)
    : QGraphicsTextItem(parent, scene)
{
    myItemTextType = itemTextType;
    myNameTextType = nameTextType;
    switch(myItemTextType)
    {
    case Label:
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemIsSelectable);
        break;
    case Margin:
        setTextWidth(200);
        setFlag(QGraphicsItem::ItemIsMovable,false);
        setFlag(QGraphicsItem::ItemIsSelectable);
        switch(myNameTextType)
        {
        case Class:
            setPlainText("��� ������");
            break;
        case Attribute:
            setPlainText("��������");
            break;
        case Operation:
            setPlainText("��������");
            break;
        case Interface:
            setTextWidth(230);
            setPlainText("                    <<���������>>");
            break;
        case Actor_name:
            setTextWidth(90);
            setPlainText("����� �����");
            break;
        case Option_disc:
            setTextWidth(230);
            setPlainText("����� ������� �������������");
            break;
        case State_name:
            setTextWidth(230);
            setPlainText("               ��� ������ ���������");
            break;
        case State_disc:
            setTextWidth(230);
            setPlainText("������ ���������� ��������");
            break;
        }
        break;
    default:
        break;
    }
}

QVariant My_diagram_text_item::itemChange(GraphicsItemChange change,const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
        emit selectedChange(this);
    return value;
}

void My_diagram_text_item::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);//������ �������������� � ������� ����������!
    if(myItemTextType==Margin && myNameTextType==Class && document()->toPlainText() == "")
        setPlainText("��� ������");
    if(myItemTextType==Margin && myNameTextType==Attribute && (document()->toPlainText() == "�����_������� : ���" || document()->toPlainText() == ""))
        setPlainText("��������");
    if(myItemTextType==Margin && myNameTextType==Operation && (document()->toPlainText() == "�����_��������()" || document()->toPlainText() == ""))
        setPlainText("��������");
    if(myItemTextType==Margin && myNameTextType==Interface && !document()->toPlainText().contains("<<���������>>"))
    {
        setPlainText("                    <<���������>>\n" + document()->toPlainText());
    }
    if(document()->toPlainText() == "" && myItemTextType==Margin && myNameTextType==Actor_name)
    {
        setPlainText("����� �����");
    }
    if(document()->toPlainText() == "" && myItemTextType==Margin && myNameTextType==Option_disc)
    {
        setPlainText("����� ������� �������������");
    }
    if(document()->toPlainText() == "" && myItemTextType==Margin && myNameTextType==State_name)
    {
        setPlainText("               ��� ������ ���������");
    }
    if((document()->toPlainText() == "�����_�e������/���������_��������" || document()->toPlainText() == "")&& myItemTextType==Margin && myNameTextType==State_disc)
    {
        setPlainText("������ ���������� ��������");
    }
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void My_diagram_text_item::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
    setFocus();
    if(myItemTextType==Margin && myNameTextType==Class && document()->toPlainText() == "��� ������")
    {
        document()->setPlainText("");
    }
    if(myItemTextType==Margin && myNameTextType==Attribute && document()->toPlainText() == "��������")
    {
        document()->setPlainText("�����_������� : ���");
    }
    if(myItemTextType==Margin && myNameTextType==Operation && document()->toPlainText() == "��������")
    {
        document()->setPlainText("�����_��������()");
    }
    if(myItemTextType==Margin && myNameTextType==Interface && document()->toPlainText() == "                    <<���������>>")
         document()->setPlainText("");

    if(myItemTextType==Margin && myNameTextType==Actor_name && document()->toPlainText() == "����� �����")
         document()->setPlainText("");

    if(myItemTextType==Margin && myNameTextType==Option_disc && document()->toPlainText() == "����� ������� �������������")
         document()->setPlainText("");

    if(myItemTextType==Margin && myNameTextType==State_name && document()->toPlainText() == "               ��� ������ ���������")
         document()->setPlainText("");
    if(myItemTextType==Margin && myNameTextType==State_disc && document()->toPlainText() == "������ ���������� ��������")
         document()->setPlainText("�����_�e������/���������_��������");
    emit items_changed();
}
QDataStream &operator<<(QDataStream &out, const My_diagram_text_item &boxItem)
{
    out << boxItem.pos() << boxItem.document()->toPlainText() << boxItem.font() << boxItem.textWidth() << boxItem.zValue();
    return out;
}
QDataStream &operator>>(QDataStream &in, My_diagram_text_item &boxItem)
{
      QPointF position;
      QString a; QFont font;
      qreal t,z;
      in >> position;
      in >> a;
      in >> font;
      in >> t;
      in >> z;
      boxItem.setPos(position);
      boxItem.setFont(font);
      boxItem.setPlainText(a);
      boxItem.setTextWidth(t);
      boxItem.setZValue(z);
  return in;

//  textItem = new My_diagram_text_item();
//  textItem->setFont(myFont);
//  textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
//  textItem->setZValue(1000.0);
//  connect(textItem, SIGNAL(lostFocus(My_diagram_text_item*)),
//          this, SLOT(editorLostFocus(My_diagram_text_item*)));
//  connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
//          this, SIGNAL(itemSelected(QGraphicsItem*)));
//  addItem(textItem);
//  textItem->setDefaultTextColor(myTextColor);
//  textItem->setPos(mouseEvent->scenePos());
}
