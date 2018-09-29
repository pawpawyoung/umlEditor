#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontComboBox>
#include "QSettings"
#include "my_diagram_item.h"

class My_diagram_scene;
namespace Ui
{
    class MainWindow;
}

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QSplitter;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFontComboBox *fontCombo; // ��� ��������� ������
    QComboBox *fontSizeCombo; // ��� ��������� ������� ������
    QComboBox *sceneScaleCombo; // ��� ��������� �������� View
    QButtonGroup *pointerTypeGroup;// ��� ��������� ������ ������ ����� (����� ��������, ����� ���������� �����)
    QButtonGroup *buttonGroup;// �������� ����������� ���������
    QButtonGroup *tab_2_Group;
    QButtonGroup *State_Group;
    QMenu *itemMenu;// ���� ���������� ������ ������� ���� �� �����
    My_diagram_scene *scene;
    void readSettings();
    void writeSettings();
    void create_tool_bars();
    void create_font_text_scale();
    QWidget *createCellWidget(const QString &text,My_diagram_item::DiagramType type);
private slots:
    // Saving slots
    void on_Save_triggered();
    void on_Open_triggered();
    void on_New_triggered();
    // Saving slots
    void on_Italic_triggered();
    void on_Underline_triggered();
    void on_Bold_triggered();
    void on_On_front_triggered();
    void on_On_back_triggered();
    void on_On_delete_triggered();
    void fontSizeChanged(const QString &size);  // �������� ������ ������
    void currentFontChanged(const QFont &font); // �������� ������� �����
    void handleFontChange();
    void sceneScaleChanged(QString);
    //=======================C���� toolbar
    void pointerGroupClicked(int id);
    void buttonGroupClicked(int id);
    void tab_2_GroupClicked(int id);
    void State_GroupClicked(int id);
    //=======================C���� �����
    void itemInserted(My_diagram_item *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);
    void help();

protected:
    void closeEvent(QCloseEvent *event);
private:
    //-----------------------���������� �����
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName); // ���������� ��� �������� ����� ���� ��� ������ �� ��������� ���� � ������ "���_�����"
    bool save();
    bool saveAs();
    void writeItems(QDataStream &out,const QList<QGraphicsItem*> &items);
    void readItems(QDataStream &in);
    QString curFile; // ������� ����
    int elms_on_scene;
};

#endif // MAINWINDOW_H
