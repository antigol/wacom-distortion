#ifndef CALIBRATIONDIALOG_HH
#define CALIBRATIONDIALOG_HH

#include <QWidget>
#include <QDialog>
#include <QTabletEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QKeyEvent>
#include <QMoveEvent>
#include <QShowEvent>
#include <QPoint>
#include <QPointF>
#include <QTimer>

class CalibrationDialog : public QDialog
{
	Q_OBJECT

public:
	CalibrationDialog(QWidget *parent = 0);
	~CalibrationDialog();

	const QVector<QPointF>& getPhysicalPoints() const {
		return m_phy_points;
	}
	const QVector<QPointF>& getRawPoints() const {
		return m_raw_points;
	}
	double getBorderTopX() const { return m_borders[0].pos; }
	double getBorderTopY() const { return m_borders[1].pos; }
	double getBorderBottomX() const { return m_borders[2].pos; }
	double getBorderBottomY() const { return m_borders[3].pos; }
	double getScreenWidth() const { return m_w; }
	double getScreenHeight() const { return m_h; }
	void setBorders(bool on) { m_show_borders = on; }
	void setText(const QString& text) { m_text = text; }
	void setLineMode(bool on) { m_lineMode = on; }
	void clearAll();

private:
	virtual void tabletEvent(QTabletEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
	virtual void closeEvent(QCloseEvent* event);
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void moveEvent(QMoveEvent* event);
	virtual void showEvent(QShowEvent* event);

	void add_point(const QPointF& point);

	double m_w, m_h;

	QVector<QPointF> m_phy_points;
	QVector<QPointF> m_raw_points;
	bool m_show_borders;
	QString m_text;

	QPointF m_tabletGlobalPosF;

	struct Border {
		double pos;
		double limit;
		bool horizontal;
		int state;

		void paint(QPainter* p, double w, double h);
		void move(double new_pos);
	} m_borders[4];

	bool m_lineMode;
};

#endif // CALIBRATIONDIALOG_HH
