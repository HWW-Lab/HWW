#include "marketbrowser.h"
#include "ui_marketbrowser.h"
#include "main.h"
#include "wallet.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include <QDesktopServices>

#include <sstream>
#include <string>

using namespace json_spirit;

const QString kBaseUrl = "http://HWW.io/HWWusd.php";
const QString kBaseUrl1 = "http://blockchain.info/tobtc?currency=USD&value=1";
const QString kBaseUrl2 = "http://HWW.io/HWWmc.php";
const QString kBaseUrl3 = "http://HWW.io/HWWbtc.php";

QString bitcoinp = "";
QString HWWp = "";
QString HWWmcp = "";
QString HWWbtcp = "";
double bitcoin2;
double HWW2;
double HWWmc2;
double HWWbtc2;
QString bitcoing;
QString HWWmarket;
QString dollarg;
int mode=1;
int o = 0;


MarketBrowser::MarketBrowser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketBrowser)
{
    ui->setupUi(this);
    setFixedSize(400, 420);


requests();
QObject::connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseNetworkResponse(QNetworkReply*)));
connect(ui->startButton, SIGNAL(pressed()), this, SLOT( requests()));
connect(ui->egal, SIGNAL(pressed()), this, SLOT( update()));

}

void MarketBrowser::update()
{
    QString temps = ui->egals->text();
    double totald = dollarg.toDouble() * temps.toDouble();
    double totaldq = bitcoing.toDouble() * temps.toDouble();
    ui->egald->setText("$ "+QString::number(totald)+" USD or "+QString::number(totaldq)+" BTC");

}

void MarketBrowser::requests()
{
	getRequest(kBaseUrl);
    getRequest(kBaseUrl1);
	getRequest(kBaseUrl2);
	getRequest(kBaseUrl3);
}

void MarketBrowser::getRequest( const QString &urlString )
{
    QUrl url ( urlString );
    QNetworkRequest req ( url );
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");
    m_nam.get(req);
}

void MarketBrowser::parseNetworkResponse(QNetworkReply *finished )
{

    QUrl what = finished->url();

    if ( finished->error() != QNetworkReply::NoError )
    {
        // A communication error has occurred
        emit networkError( finished->error() );
        return;
    }
	
if (what == kBaseUrl) // HWW Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString HWW = finished->readAll();
    HWW2 = (HWW.toDouble());
    HWW = QString::number(HWW2, 'f', 2);
	
    if(HWW > HWWp)
    {
        ui->HWW->setText("<font color=\"yellow\">$" + HWW + "</font>");
    } else if (HWW < HWWp) {
        ui->HWW->setText("<font color=\"red\">$" + HWW + "</font>");
        } else {
    ui->HWW->setText("$"+HWW+" USD");
    }

    HWWp = HWW;
	dollarg = HWW;
}

if (what == kBaseUrl1) // Bitcoin Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString bitcoin = finished->readAll();
    bitcoin2 = (1 / bitcoin.toDouble());
    bitcoin = QString::number(bitcoin2, 'f', 2);
    if(bitcoin > bitcoinp)
    {
        ui->bitcoin->setText("<font color=\"yellow\">$" + bitcoin + " USD</font>");
    } else if (bitcoin < bitcoinp) {
        ui->bitcoin->setText("<font color=\"red\">$" + bitcoin + " USD</font>");
        } else {
    ui->bitcoin->setText("$"+bitcoin+" USD");
    }

    bitcoinp = bitcoin;
}

if (what == kBaseUrl2) // HWW Market Cap
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString HWWmc = finished->readAll();
    HWWmc2 = (HWWmc.toDouble());
    HWWmc = QString::number(HWWmc2, 'f', 2);
	
    if(HWWmc > HWWmcp)
    {
        ui->HWWmc->setText("<font color=\"yellow\">$" + HWWmc + "</font>");
    } else if (HWWmc < HWWmcp) {
        ui->HWWmc->setText("<font color=\"red\">$" + HWWmc + "</font>");
        } else {
    ui->HWWmc->setText("$"+HWWmc+" USD");
    }

    HWWmcp = HWWmc;
	HWWmarket = HWWmc;
}

if (what == kBaseUrl3) // HWW BTC Price
{

    // QNetworkReply is a QIODevice. So we read from it just like it was a file
    QString HWWbtc = finished->readAll();
    HWWbtc2 = (HWWbtc.toDouble());
    HWWbtc = QString::number(HWWbtc2, 'f', 8);
	
    if(HWWbtc > HWWbtcp)
    {
        ui->HWWbtc->setText("<font color=\"yellow\">" + HWWbtc + " BTC</font>");
    } else if (HWWbtc < HWWbtcp) {
        ui->HWWbtc->setText("<font color=\"red\">" + HWWbtc + " BTC</font>");
        } else {
    ui->HWWbtc->setText(HWWbtc+" BTC");
    }

    HWWbtcp = HWWbtc;
	bitcoing = HWWbtc;
}

finished->deleteLater();
}


void MarketBrowser::setModel(ClientModel *model)
{
    this->model = model;
}

MarketBrowser::~MarketBrowser()
{
    delete ui;
}
