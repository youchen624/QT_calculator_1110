#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QGridLayout>
class SquareButton;
class QPushButton;
class QLineEdit;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    enum NumButtons {
        Num_0 = 0,
        Num_1,
        Num_2,
        Num_3,
        Num_4,
        Num_5,
        Num_6,
        Num_7,
        Num_8,
        Num_9,
    };
    // last = 9 (x10)
    enum FuncButtons {
        Cal, // calculate
        Backspace, // BS
        Dot, // dot .
        Add, // add
        Sub, // sub
        Div, // div
        Mul, // mul

        // Nope, //
        AC, // All Clear
        RNDB, // RND Button
        RND,
        RDC // RND CRAZY @!!!
    };
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    double num_l = 0, num_r = 0;
    char mode = -1;
    QLineEdit *editInput;
    QGridLayout *editLayout;

    SquareButton *numButtons[10];
    SquareButton *funcButtons[11];

    void cal(bool review = false);
    // QPushButton *do_calculatorButton;
    // QPushButton *dotButton;

    // QPushButton *func_backspace;
    // QPushButton *func_div;
    // QPushButton *func_mul;
    // QPushButton *func_add;
    // QPushButton *func_sub;

    // QPushButton *num_0;
    // QPushButton *num_1;
    // QPushButton *num_2;
    // QPushButton *num_3;
    // QPushButton *num_4;
    // QPushButton *num_5;
    // QPushButton *num_6;
    // QPushButton *num_7;
    // QPushButton *num_8;
    // QPushButton *num_9;
private slots:
    void numInput();
    void funcInput();
    void enterInput();
};


class SquareButton : public QPushButton {
    Q_OBJECT
public:
    using QPushButton::QPushButton;
    SquareButton(const QString &text, QWidget *parent = nullptr)
        : QPushButton(text, parent)
    {
        applyFixedFont();
    }
    SquareButton(QWidget *parent = nullptr)
        : QPushButton(parent)
    {
        applyFixedFont();
    }
    QSize sizeHint() const override {
        QSize hint = QPushButton::sizeHint();
        int size = qMax(hint.width(), hint.height());
        return QSize(size, size);
    }

    int heightForWidth(int w) const override {
        return w;
    }
protected:
    void applyFixedFont() {
        QFont font = this->font();
        font.setPointSize(20);
        this->setFont(font);
    };
};
#endif // DIALOG_H
