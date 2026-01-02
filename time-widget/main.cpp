#include <QApplication>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDateTime>
#include <QTimer>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QLineEdit>

class MyWidget : public QWidget {

    QPoint dragOffset;
    QLabel *label;
    bool dragging = false;

public:
    MyWidget() {
        setWindowFlags(Qt::FramelessWindowHint);
     //   setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_StyledBackground, true);
       // this->setStyleSheet("QLineEdit { background-color: #cfb0b0; border-radius: 100px; }");

        resize(300, 300);

        label = new QLabel(this);
        label->setStyleSheet("QLabel {min-width: 250px; max-height: 100px; color: white; font-size: 30px; background-color: #cfb0b0; border-radius: 15px; padding: 5px}");
        label->setAlignment(Qt::AlignCenter);
        label->resize(300, 300);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

        auto *layout = new QVBoxLayout(this);
        layout->addWidget(label, 0, Qt::AlignCenter);
        layout->addSpacing(5);
        setContentsMargins(20, 20, 20, 20);

        auto *timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, [this] {
            QString text = QDateTime::currentDateTime().toString("dd.MM HH:mm:ss");

            label->setText(text);
            update();
        });

        timer->start(1000);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter p(this);

        p.setCompositionMode(QPainter::CompositionMode_Source);
        p.fillRect(rect(), Qt::transparent);
        p.setCompositionMode(QPainter::CompositionMode_SourceOver);

        p.setPen(Qt::white);
        p.setFont(QFont("Arial", 50));
    }

    void mousePressEvent(QMouseEvent *e) override {
        auto s =  e->button();
        if (e->button() == Qt::LeftButton) {
            dragOffset = e->globalPos() - frameGeometry().topLeft();
            dragging = true;
            grabMouse();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (dragging && event->buttons() & Qt::LeftButton) {
            move(event->globalPos() - dragOffset);
        }
    }

    void mouseReleaseEvent(QMouseEvent *e) override {
        if (e->button() == Qt::LeftButton) {
            dragging = false;
            releaseMouse();
        }
    }
};

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QRect screen = QGuiApplication::primaryScreen()->geometry();

    auto widget = new MyWidget();
    widget->show();

    int x = screen.width()  - widget->width() * 2;
    int y = screen.height() - widget->height();

    widget->move(x, y);

    return QApplication::exec();
}