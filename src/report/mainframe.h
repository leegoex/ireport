#ifndef IREPORT_MAINFRAME_H_
#define IREPORT_MAINFRAME_H_

#include <QMainWindow>

namespace Ui
{
    class MainFrame;
}

class QWebView;

class MainFrame : public QMainWindow
{
	Q_OBJECT
public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

	enum IStep {
		StepNotStart = 0,
		StepNetease,
		StepAlipay,
		StepTencent,
		StepDone,
	};

protected:
	void gotoNext();

private slots:
	void	slotIconChanged();
	void	slotLinkClicked(const QUrl & url);
	void	slotLoadFinished(bool ok);
	void	slotLoadProgress(int progress);
	void	slotLoadStarted();
	void	slotSelectionChanged();
	void	slotStatusBarMessage(const QString & text);
	void	slotTitleChanged(const QString & title);
	void	slotUrlChanged(const QUrl & url);

	void on_pushButtonRefresh_clicked();

	void slotGetIucre_netease();
	void slotGetIucre_alipay();
	void slotGetIucre_tencent();

private:
    Ui::MainFrame *m_ui;

	QWebView *m_webview;
	int m_step;
};

#endif // IREPORT_MAINFRAME_H_
