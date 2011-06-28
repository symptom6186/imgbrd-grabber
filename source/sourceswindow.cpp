#include "sourceswindow.h"
#include "sitewindow.h"
#include "ui_sourceswindow.h"



/**
 * Constructor of the sourcesWindow, generating checkboxes and delete buttons
 * @param	selected	Bool list of currently selected websites, in the alphabetical order
 * @param	sites		QStringList of sites names
 * @param	parent		The parent window
 */
sourcesWindow::sourcesWindow(QList<bool> selected, QStringMapMap *sites, QWidget *parent) : QDialog(parent), ui(new Ui::sourcesWindow), m_selected(selected), m_sites(sites)
{
	ui->setupUi(this);

	bool checkall = true;
	for (int i = 0; i < selected.count(); i++)
	{
		if (!selected.at(i))
		{
			checkall = false;
			break;
		}
	}
	if (checkall)
	{ ui->checkBox->setChecked(true); }

	QSettings *settings = new QSettings(savePath("settings.ini"), QSettings::IniFormat);

	QStringList k = sites->keys();
	k.sort();
	for (int i = 0; i < k.count(); i++)
	{
		QCheckBox *check = new QCheckBox();
			check->setChecked(m_selected[i]);
			check->setText(k.at(i));
			m_checks << check;
			ui->gridLayout->addWidget(check, i, 0);
		QString t = settings->value("Sources/Types", "text").toString();
		int n = 1;
		if (t != "hide")
		{
			QString txt;
			QLabel *type = new QLabel();
				if (t == "icon" || t == "both")
				{ txt += "<img src=\"sites/"+sites->value(k.at(i))["Name"].toLower()+"/icon.png\" /> "; }
				if (t == "text" || t == "both")
				{ txt += sites->value(k.at(i))["Name"]; }
				type->setText(txt);
				type->setTextFormat(Qt::RichText);
				ui->gridLayout->addWidget(type, i, 1);
				m_labels << type;
				n++;
		}
		QBouton *del = new QBouton(k.at(i));
			del->setText(tr("Supprimer"));
			connect(del, SIGNAL(appui(QVariant)), this, SLOT(deleteSite(QVariant)));
			m_buttons << del;
			ui->gridLayout->addWidget(del, i, n);
	}
	ui->gridLayout->setColumnStretch(0, 1);

	ui->buttonOk->setFocus();
}
sourcesWindow::~sourcesWindow()
{
    delete ui;
}

/**
 * When closed, the window emit a signal wich will trigger a slot in the mainwindow.
 * @param	event	The event triggered wy window's closing
 * @todo	Why use a signal, since we can simply use a pointer to the parent window, or a signal giving not a pointer to this window, but directly m_selected ?
 */
void sourcesWindow::closeEvent(QCloseEvent *event)
{
	emit closed(this);
	event->accept();
}

/**
 * Saves current selection then close the window.
 */
void sourcesWindow::valid()
{
	for (int i = 0; i < m_checks.count(); i++)
	{ m_selected[i] = m_checks.at(i)->isChecked(); }
	emit valid(this);
	this->close();
}

void sourcesWindow::deleteSite(QVariant site)
{
	int reponse = QMessageBox::question(this, tr("Grabber - Supprimer un site"), tr("�tes-vous s�r de vouloir supprimer le site %1 ?").arg(site.toString()), QMessageBox::Yes | QMessageBox::No);
	if (reponse == QMessageBox::Yes)
	{
		int i = m_sites->keys().indexOf(site.toString());
		m_checks.at(i)->hide();
		ui->gridLayout->removeWidget(m_checks.at(i));
		m_buttons.at(i)->hide();
		ui->gridLayout->removeWidget(m_buttons.at(i));
		if (!m_labels.isEmpty())
		{
			m_labels.at(i)->hide();
			ui->gridLayout->removeWidget(m_labels.at(i));
		}
		QString type = m_sites->value(site.toString())["Name"].toLower();
		QFile f("sites/"+type+"/sites.txt");
		f.open(QIODevice::ReadOnly);
			QString sites = f.readAll();
		f.close();
		sites.replace("\r\n", "\n").replace("\r", "\n").replace("\n", "\r\n");
		QStringList stes = sites.split("\r\n");
		stes.removeAll(site.toString());
		f.open(QIODevice::WriteOnly);
			f.write(stes.join("\r\n").toAscii());
		f.close();
		m_sites->remove(site.toString());
		m_selected.removeAt(i);
	}
}

void sourcesWindow::addSite()
{
	siteWindow *sw = new siteWindow(m_sites, this);
	sw->show();
	connect(sw, SIGNAL(accepted()), this, SLOT(insertCheckBox()));
}
void sourcesWindow::insertCheckBox()
{
	QStringList k = m_sites->keys();
	for (int i = 0; i < m_checks.count(); i++)
	{
		m_checks.at(i)->hide();
		ui->gridLayout->removeWidget(m_checks.at(i));
		m_buttons.at(i)->hide();
		ui->gridLayout->removeWidget(m_buttons.at(i));
		if (!m_labels.isEmpty())
		{
			m_labels.at(i)->hide();
			ui->gridLayout->removeWidget(m_labels.at(i));
		}
	}

	QSettings *settings = new QSettings(savePath("settings.ini"), QSettings::IniFormat);
	for (int i = 0; i < m_sites->count(); i++)
	{
		if (k.at(i) != m_checks.at(i)->text())
		{
			m_selected.insert(i, false);
			QCheckBox *check = new QCheckBox();
				check->setChecked(m_selected[i]);
				check->setText(k.at(i));
				m_checks.insert(i, check);
			QString t = settings->value("Sources/Types", "text").toString();
			if (t != "hide")
			{
				QString txt;
				QLabel *type = new QLabel();
					if (t == "icon" || t == "both")
					{ txt += "<img src=\"sites/"+m_sites->value(k.at(i))["Name"].toLower()+"/icon.png\" /> "; }
					if (t == "text" || t == "both")
					{ txt += m_sites->value(k.at(i))["Name"]; }
					type->setText(txt);
					type->setTextFormat(Qt::RichText);
					m_labels.insert(i, type);
			}
			QBouton *del = new QBouton(k.at(i));
				del->setText(tr("Supprimer"));
				m_buttons.insert(i, del);
			break;
		}
	}

	for (int i = 0; i < m_checks.count(); i++)
	{
		ui->gridLayout->addWidget(m_checks.at(i), i, 0);
		m_checks.at(i)->show();
		int n = 1;
		if (!m_labels.isEmpty())
		{
			ui->gridLayout->addWidget(m_labels.at(i), i, 1);
			m_labels.at(i)->show();
			n++;
		}
		ui->gridLayout->addWidget(m_buttons.at(i), i, n);
		m_buttons.at(i)->show();
	}
}

/**
 * Check of uncheck all checkboxes, according to "check".
 * @param	check	Qt::CheckState saying if we must check or uncheck everithing (0 = uncheck, 2 = check)
 */
void sourcesWindow::checkAll(int check)
{
	for (int i = 0; i < m_checks.count(); i++)
	{ m_checks.at(i)->setChecked(check == 2); }
}

/**
 * Accessor for the "selected" variable.
 * @return A bool list corresponding to selected websites.
 */
QList<bool> sourcesWindow::getSelected()
{ return m_selected; }
