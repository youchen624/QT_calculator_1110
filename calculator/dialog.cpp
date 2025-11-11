#include "dialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QtGlobal>
#include <QTime>
#include <QDebug>
// #include "ui_dialog.h"

/*class SquareButton : public QPushButton {
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
    }
};*/

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    //, ui(new Ui::Dialog)
{
    // ui->setupUi(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    editLayout = new QGridLayout;

    mainLayout->addLayout(editLayout);

    // edit-line
    editInput = new QLineEdit;
    editInput->setFixedHeight(64);
    {
        QFont font = editInput->font();
        font.setPointSize(16);
        editInput->setFont(font);
    }

    // number 9~1 0
    for (int r = 0, i = 9; r < 3; ++r) {
        for (int c = 0; c < 3; ++c, --i) {
            numButtons[i] = new SquareButton(QString::number(i));
            editLayout->addWidget(numButtons[i], r+3, 2-c);
        }
    }
    numButtons[0] = new SquareButton("0");
    editLayout->addWidget(numButtons[0], 6, 0, 1, 2);

    // dot .
    funcButtons[FuncButtons::Dot] = new SquareButton(".");
    editLayout->addWidget(funcButtons[FuncButtons::Dot], 6, 2);

    // do_calculatorButton
    funcButtons[FuncButtons::Cal] = new SquareButton("Enter");
    editLayout->addWidget(funcButtons[FuncButtons::Cal], 5, 3, 2, 1);

    // {
    //     QSizePolicy sizePolicy = funcButtons[FuncButtons::Cal]->sizePolicy();
    //     sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
    //     funcButtons[FuncButtons::Cal]->setSizePolicy(sizePolicy);
    // }

    // All Clear
    funcButtons[FuncButtons::AC] = new SquareButton("AC");
    editLayout->addWidget(funcButtons[FuncButtons::AC], 1, 0);

    // RND
    funcButtons[FuncButtons::RND] = new SquareButton("RND");
    editLayout->addWidget(funcButtons[FuncButtons::RND], 2, 0);
    // RNDB
    funcButtons[FuncButtons::RNDB] = new SquareButton("RDB");
    editLayout->addWidget(funcButtons[FuncButtons::RNDB], 1, 1);

    // RDC
    funcButtons[FuncButtons::RDC] = new SquareButton("RDC");
    editLayout->addWidget(funcButtons[FuncButtons::RDC], 1, 2);

    // backspace ←
    funcButtons[FuncButtons::Backspace] = new SquareButton("←");
    editLayout->addWidget(funcButtons[FuncButtons::Backspace], 1, 3);

    // div /
    funcButtons[FuncButtons::Div] = new SquareButton("/");
    editLayout->addWidget(funcButtons[FuncButtons::Div], 2, 1);

    // Mul *
    funcButtons[FuncButtons::Mul] = new SquareButton("*");
    editLayout->addWidget(funcButtons[FuncButtons::Mul], 2, 2);

    // Sub -
    funcButtons[FuncButtons::Sub] = new SquareButton("-");
    editLayout->addWidget(funcButtons[FuncButtons::Sub], 2, 3);

    // Add +
    funcButtons[FuncButtons::Add] = new SquareButton("+");
    editLayout->addWidget(funcButtons[FuncButtons::Add], 3, 3, 2, 1);

    for (int i = 0; i < 11; ++i) {
        QSizePolicy sizePolicy = funcButtons[i]->sizePolicy();
        sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
        funcButtons[i]->setSizePolicy(sizePolicy);
    }
    for (int i = 0; i < 10; ++i) {
        QSizePolicy sizePolicy = numButtons[i]->sizePolicy();
        sizePolicy.setVerticalPolicy(QSizePolicy::Expanding);
        numButtons[i]->setSizePolicy(sizePolicy);
    }

    editLayout->addWidget(editInput, 0, 0, 1, 4);




    // CONNECT s
    for (int i = 0; i < 10; ++i) {
        connect(
            numButtons[i],
            SIGNAL(clicked()),
            this,
            SLOT(numInput())
        );
        connect(
            funcButtons[i],
            SIGNAL(clicked()),
            this,
            SLOT(funcInput())
        );
    }
    connect(
        funcButtons[FuncButtons::RDC],
        SIGNAL(clicked()),
        this,
        SLOT(funcInput())
        );
}

void buttonValueSwap(SquareButton* a, SquareButton* b) {
    QString str = a->text();
    a->setText(b->text());
    b->setText(str);
};
void buttonCRAZYSwap(QGridLayout *glayout,SquareButton* a, SquareButton* b) {
    int r_a, c_a, rs_a, cs_a, r_b, c_b, rs_b, cs_b;
    int index_a = glayout->indexOf(a);
    int index_b = glayout->indexOf(b);
    // if (index_a == -1 || index_b == -1) return;
    glayout->getItemPosition(
        index_a,
        &r_a,
        &c_a,
        &rs_a,
        &cs_a
    );
    // qDebug() << "r_a" << r_a << "\nc_a" << c_a;
    glayout->getItemPosition(
        index_b,
        &r_b,
        &c_b,
        &rs_b,
        &cs_b
    );
    glayout->removeWidget(a);
    glayout->removeWidget(b);
    glayout->addWidget(a, r_b, c_b, rs_b, cs_b);
    glayout->addWidget(b, r_a, c_a, rs_a, cs_a);
};

void Dialog::numInput() {
    SquareButton* btn = qobject_cast<SquareButton*>(sender());
    QString str = btn->text();
    editInput->insert(str);
};
void Dialog::funcInput() {
    SquareButton* btn = qobject_cast<SquareButton*>(sender());
    int bn = -1;
    for (int i = 0; i < 11; ++i) {
        if (btn == funcButtons[i])
            bn = i;
    }
    switch(bn) {
    case (FuncButtons::AC): {
        mode = -1;
        num_l = 0;
        return editInput->setText("");
    }
    case (FuncButtons::Backspace): { return editInput->backspace(); }

    case (FuncButtons::Dot): { return editInput->insert("."); } break;
    case (FuncButtons::Cal): {
        cal(true);
        // num_l = 0;
    } break;

    case (FuncButtons::Add):
    case (FuncButtons::Sub):
    case (FuncButtons::Mul):
    case (FuncButtons::Div):
    {
        mode = bn;
        if (num_l) {
            return cal();
        }
        QString str = editInput->text();
        bool ok;
        num_l = str.toDouble(&ok);
        editInput->setText(ok ? "" : "Error");
    } break;

    case (FuncButtons::RND): {
        editInput->setText(QString::number(rand() % 100000000));
    } break;
    case (FuncButtons::RNDB): {
        srand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        for (int i = 0; i < 10; ++i) {
            size_t r = rand() % 10;
            buttonValueSwap(numButtons[0], numButtons[r]);
        }
        // make button rnd switch
    } break;
    case (FuncButtons::RDC): {
        srand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        for (int i = 0; i < 10; ++i) {
            size_t r = rand() % 10;
            // SquareButton* ptr = funcButtons[i];
            buttonCRAZYSwap(editLayout, funcButtons[i], funcButtons[r]);
        }
    } break;
    }
};
void Dialog::enterInput() {};

void Dialog::cal(bool review)  {
    QString str = editInput->text();
    bool ok;
    num_r = str.toDouble(&ok);
    if (!ok) {
        return editInput->setText("Error");
    }
    switch(mode) {
    case (FuncButtons::Add): {
        num_l += num_r;
    } break;
    case (FuncButtons::Sub): {
        num_l -= num_r;
    } break;
    case (FuncButtons::Mul): {
        num_l *= num_r;
    } break;
    case (FuncButtons::Div): {
        num_l /= num_r;
    } break;
    }
    editInput->setText(review ? QString::number(num_l) : "");
}

Dialog::~Dialog()
{
    // delete ui;
}
