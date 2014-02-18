#include "mainframe.h"
#include "ui_mainframe.h"

#include <QWebView>
#include <QWebFrame>
#include <QWebElement>
#include <QUrl>
#include <QMessageBox>
#include <QTimer>
#include <QDatetime>

struct IucreUrlAddress
{
	static QString neteaseUrl;
	static QString alipayUrl;
	static QString tencentUrl;
};

QString IucreUrlAddress::neteaseUrl = QString("https://8.163.com");
QString IucreUrlAddress::alipayUrl = QString("https://financeprod.alipay.com/fund/index.htm");
QString IucreUrlAddress::tencentUrl = QString("http://www.chinaamc.com/yingxiao/2013/caifubao/index.html?tjmb=000000;tjly=98");

MainFrame::MainFrame(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainFrame),
	  m_webview(0),
	  m_step(StepNotStart)
{
    m_ui->setupUi(this);

	m_webview = new QWebView(this);
	m_webview->hide();
// 	connect(m_webview, SIGNAL(iconChanged()), this, SLOT(slotIconChanged()));
// 	connect(m_webview, SIGNAL(linkClicked(const QUrl&)), this, SLOT(slotLinkClicked(const QUrl&)));
	connect(m_webview, SIGNAL(loadFinished(bool)), this, SLOT(slotLoadFinished(bool)));
// 	connect(m_webview, SIGNAL(loadProgress(int)), this, SLOT(slotLoadProgress(int)));
// 	connect(m_webview, SIGNAL(loadStarted()), this, SLOT(slotLoadStarted()));
// 	connect(m_webview, SIGNAL(selectionChanged()), this, SLOT(slotSelectionChanged()));
// 	connect(m_webview, SIGNAL(statusBarMessage(const QString&)), this, SLOT(slotStatusBarMessage(const QString&)));
// 	connect(m_webview, SIGNAL(titleChanged(const QString&)), this, SLOT(slotTitleChanged(const QString&)));
// 	connect(m_webview, SIGNAL(urlChanged(const QUrl&)), this, SLOT(slotUrlChanged(const QUrl&)));

	on_pushButtonRefresh_clicked();

//	setCentralWidget(m_webview);
}

MainFrame::~MainFrame()
{
    delete m_ui;
}

void MainFrame::slotIconChanged()
{

}

void MainFrame::slotLinkClicked(const QUrl & url)
{

}

void MainFrame::slotLoadFinished(bool ok)
{
	if (ok) {
		switch(m_step)
		{
		case StepNetease:
			QTimer::singleShot(0, this, SLOT(slotGetIucre_netease()));
			break;
		case StepAlipay:
			QTimer::singleShot(0, this, SLOT(slotGetIucre_alipay()));
			break;
		case StepTencent:
			QTimer::singleShot(0, this, SLOT(slotGetIucre_tencent()));
			break;
		}
	} else {
		QString url;
		switch(m_step)
		{
		case StepNetease:
			url = IucreUrlAddress::neteaseUrl;
			break;
		case StepAlipay:
			url = IucreUrlAddress::alipayUrl;
			break;
		case StepTencent:
			url = IucreUrlAddress::tencentUrl;
			break;
		}
		QMessageBox::information(this, tr("Load Page Failed"), url);
	}
	
}

void MainFrame::slotLoadProgress(int progress)
{

}

void MainFrame::slotLoadStarted()
{

}

void MainFrame::slotSelectionChanged()
{

}

void MainFrame::slotStatusBarMessage(const QString & text)
{

}

void MainFrame::slotTitleChanged(const QString & title)
{

}

void MainFrame::slotUrlChanged(const QUrl & url)
{

}

void MainFrame::on_pushButtonRefresh_clicked()
{
	QDateTime datetime = QDateTime::currentDateTime();
	QString title = QString(tr("Iucre report - "));
	title += datetime.toString("yyyy-MM-dd");
	setWindowTitle(title);

	m_step = StepNetease;
	m_webview->load(QUrl(IucreUrlAddress::neteaseUrl));
	m_ui->pushButtonRefresh->setEnabled(false);
}

void MainFrame::slotGetIucre_netease()
{
	QWebFrame* frame = m_webview->page()->mainFrame();
	if (!frame) {
		return;
	}
	QWebElement e = frame->findFirstElement(QString("em[title]"));
	if (e.isNull()) {
		QMessageBox::information(this, tr("Netease"), tr("Get Iucre Failed"));
	} else {
		m_ui->lineEditNetease->setText(e.toPlainText());
	}
	m_step = StepAlipay;
	m_webview->load(QUrl(IucreUrlAddress::alipayUrl));
}

void MainFrame::slotGetIucre_alipay()
{
	QWebFrame* frame = m_webview->page()->mainFrame();
	if (!frame) {
		return;
	}
	QWebElement e = frame->findFirstElement(QString("em[class=\"nianhualv\"]"));
	if (e.isNull()) {
		QMessageBox::information(this, tr("Alipay"), tr("Get Iucre Failed"));
	} else {
		m_ui->lineEditAlipay->setText(e.toPlainText());
	}
	m_step = StepTencent;
	m_webview->load(QUrl(IucreUrlAddress::tencentUrl));
}

void MainFrame::slotGetIucre_tencent()
{
	QWebFrame* frame = m_webview->page()->mainFrame();
	if (!frame) {
		return;
	}
	QWebElement e = frame->findFirstElement(QString("div[class=\"shouyimingcheng2\"]"));
	if (e.isNull()) {
		QMessageBox::information(this, tr("Tencent"), tr("Get Iucre Failed"));
	} else {
		m_ui->lineEditTencent->setText(e.toPlainText());
	}
	m_step = StepDone;
	m_ui->pushButtonRefresh->setEnabled(true);
}