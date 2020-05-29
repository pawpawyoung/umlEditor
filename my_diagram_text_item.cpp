#include "my_diagram_text_item.h"
#include "my_diagram_scene.h"

#include <QTextDocument>
My_diagram_text_item::My_diagram_text_item(QGraphicsItem *parent, QGraphicsScene *scene,ItemTextType itemTextType,NameTextType nameTextType)
    // : QGraphicsTextItem(parent, scene)
    : QGraphicsTextItem("scene", parent)
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
            setPlainText("类名称");
            break;
        case Attribute:
            setPlainText("属性");
            break;
        case Operation:
            setPlainText("业务");
            break;
        case Interface:
            setTextWidth(230);
            setPlainText("                    <<接口>>");
            break;
        case Actor_name:
            setTextWidth(90);
            setPlainText("新演员");
            break;
        case Option_disc:
            setTextWidth(230);
            setPlainText("新的使用方案");
            break;
        case State_name:
            setTextWidth(230);
            setPlainText("               新的状态名称");
            break;
        case State_disc:
            setTextWidth(230);
            setPlainText("内部活动列表");
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
    setTextInteractionFlags(Qt::NoTextInteraction);//ставим взаимодействие с текстом невозможно!
    if(myItemTextType==Margin && myNameTextType==Class && document()->toPlainText() == "")
        setPlainText("类名称");
    if(myItemTextType==Margin && myNameTextType==Attribute && (document()->toPlainText() == "新属性：类型" || document()->toPlainText() == ""))
        setPlainText("属性");
    if(myItemTextType==Margin && myNameTextType==Operation && (document()->toPlainText() == "新的操作()" || document()->toPlainText() == ""))
        setPlainText("业务");
    if(myItemTextType==Margin && myNameTextType==Interface && !document()->toPlainText().contains("<<接口>>"))
    {
        setPlainText("                    <<接口>>\n" + document()->toPlainText());
    }
    if(document()->toPlainText() == "" && myItemTextType==Margin && myNameTextType==Actor_name)
    {
        setPlainText("新演员");
    }
    if(document()->toPlainText() == "" && myItemTextType==Margin && myNameTextType==Option_disc)
    {
        setPlainText("新的使用方案");
    }
    if(document()->toPlainText() == "" && myItemTextType==Margin && myNameTextType==State_name)
    {
        setPlainText("               新的状态名称");
    }
    if((document()->toPlainText() == "行动标号" || document()->toPlainText() == "")&& myItemTextType==Margin && myNameTextType==State_disc)
    {
        setPlainText("内部活动列表");
    }
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void My_diagram_text_item::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
    setFocus();
    if(myItemTextType==Margin && myNameTextType==Class && document()->toPlainText() == "类名称")
    {
        document()->setPlainText("");
    }
    if(myItemTextType==Margin && myNameTextType==Attribute && document()->toPlainText() == "属性")
    {
        document()->setPlainText("新属性：类型");
    }
    if(myItemTextType==Margin && myNameTextType==Operation && document()->toPlainText() == "业务")
    {
        document()->setPlainText("新的操作()");
    }
    if(myItemTextType==Margin && myNameTextType==Interface && document()->toPlainText() == "                    <<接口>>")
         document()->setPlainText("");

    if(myItemTextType==Margin && myNameTextType==Actor_name && document()->toPlainText() == "新演员")
         document()->setPlainText("");

    if(myItemTextType==Margin && myNameTextType==Option_disc && document()->toPlainText() == "新的使用方案")
         document()->setPlainText("");

    if(myItemTextType==Margin && myNameTextType==State_name && document()->toPlainText() == "               新的状态名称")
         document()->setPlainText("");
    if(myItemTextType==Margin && myNameTextType==State_disc && document()->toPlainText() == "内部活动列表")
         document()->setPlainText("行动标号");
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
