#include "mainframe.h"
#include "ui_mainframe.h"

#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKit/QWebElement>
#include <QtCore/QUrl>
#include <QtCore/QTimer>
#include <QtCore/QDatetime>
#include <QtWidgets/QMessageBox>

struct IucreUrlAddress
{
	static QString neteaseUrl;
	static QString alipayUrl;
	static QString tencentUrl;
};

QString IucreUrlAddress::neteaseUrl = QString("https://8.163.com");
QString IucreUrlAddress::alipayUrl = QString("http://www.thfund.com.cn/column.dohsmode=searchtopic&pageno=0&channelid=2&categoryid=2435&childcategoryid=2436.htm");
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

	gotoNext();
}

MainFrame::~MainFrame()
{
    delete m_ui;
}

void MainFrame::gotoNext()
{
	switch (m_step)
	{
	case StepNotStart:
	case StepDone:
		on_pushButtonRefresh_clicked();
		break;
	case StepNetease:
		m_step = StepAlipay;
		m_webview->load(QUrl(IucreUrlAddress::alipayUrl));
		break;
	case StepAlipay:
		m_step = StepTencent;
		m_webview->load(QUrl(IucreUrlAddress::tencentUrl));
		break;
	case StepTencent:
		m_step = StepDone;
		m_ui->pushButtonRefresh->setEnabled(true);
		break;
	}
}

void MainFrame::slotIconChanged()
{

}

void MainFrame::slotLinkClicked(const QUrl & url)
{
	Q_UNUSED(url);
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
	Q_UNUSED(progress);
}

void MainFrame::slotLoadStarted()
{

}

void MainFrame::slotSelectionChanged()
{

}

void MainFrame::slotStatusBarMessage(const QString & text)
{
	Q_UNUSED(text);
}

void MainFrame::slotTitleChanged(const QString & title)
{
	Q_UNUSED(title);
}

void MainFrame::slotUrlChanged(const QUrl & url)
{
	Q_UNUSED(url);
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
	if (frame != NULL) {
		QWebElement e = frame->findFirstElement(QString("em[title]"));
		if (e.isNull()) {
			QMessageBox::information(this, tr("Netease"), tr("Get Iucre Failed"));
		} else {
			m_ui->lineEditNetease->setText(e.toPlainText());
		}
	}
	
	gotoNext();
}

void MainFrame::slotGetIucre_alipay()
{
	QWebFrame* frame = m_webview->page()->mainFrame();
	if (frame != NULL) {
		QWebElement e = frame->findFirstElement(QString("div[class=\"fenji\"]>table>tbody"));
		if (e.isNull()) {
			QMessageBox::information(this, tr("Alipay"), tr("Get Iucre Failed"));
		} else {
			e = e.firstChild().nextSibling().firstChild().nextSibling().nextSibling().nextSibling().firstChild();
			if (!e.isNull())
				m_ui->lineEditAlipay->setText(e.toPlainText());
			else
				QMessageBox::information(this, tr("Alipay"), tr("Get Iucre Failed"));
		}
	}
	
	gotoNext();
}

void MainFrame::slotGetIucre_tencent()
{
	QWebFrame* frame = m_webview->page()->mainFrame();
	if (frame != NULL) {
		QWebElement e = frame->findFirstElement(QString("div[class=\"shouyimingcheng2\"]"));
		if (e.isNull()) {
			QMessageBox::information(this, tr("Tencent"), tr("Get Iucre Failed"));
		} else {
			m_ui->lineEditTencent->setText(e.toPlainText());
		}
	}
	
	gotoNext();
}