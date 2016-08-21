#include <QtTest>
#include "tag-test.h"


void TagTest::init()
{
	m_settings = new QSettings("tests/test_settings.ini", QSettings::IniFormat);
}
void TagTest::cleanup()
{
	m_settings->deleteLater();
}

void TagTest::testText()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.text(), QString("tag_text"));
}
void TagTest::testSetText()
{
	Tag tag(m_settings, "tag_not_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");
	tag.setText("tag_text");

	QCOMPARE(tag.text(), QString("tag_text"));
}

void TagTest::testType()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.type(), QString("artist"));
}
void TagTest::testTypeArtistEnding()
{
	Tag tag(m_settings, "tag_text (artist)", "unknown", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.type(), QString("artist"));
	QCOMPARE(tag.text(), QString("tag_text"));
}
void TagTest::testTypePrefix()
{
	Tag tag(m_settings, "artist:tag_text", "unknown", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.type(), QString("artist"));
	QCOMPARE(tag.text(), QString("tag_text"));
}
void TagTest::testSetType()
{
	Tag tag(m_settings, "tag_text", "character", 123, QStringList() << "related1" << "related2" << "related3");
	tag.setType("artist");

	QCOMPARE(tag.type(), QString("artist"));
}
void TagTest::testShortType()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.shortType(), 1);
}
void TagTest::testSetTypeShortType()
{
	Tag tag(m_settings, "tag_text", "character", 123, QStringList() << "related1" << "related2" << "related3");
	tag.setType("artist");

	QCOMPARE(tag.shortType(), 1);
}

void TagTest::testCount()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.count(), 123);
}
void TagTest::testSetCount()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");
	tag.setCount(1234);

	QCOMPARE(tag.count(), 1234);
}

void TagTest::testRelated()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.related(), QStringList() << "related1" << "related2" << "related3");
}
void TagTest::testSetRelated()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2");
	tag.setRelated(QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.related(), QStringList() << "related1" << "related2" << "related3");
}

void TagTest::testTypedTextArtist()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.typedText(), QString("artist:tag_text"));
}

void TagTest::testTypedTextGeneral()
{
	Tag tag(m_settings, "tag_text", "general", 123, QStringList() << "related1" << "related2" << "related3");

	QCOMPARE(tag.typedText(), QString("tag_text"));
}

void TagTest::testStylishedFavorite()
{
	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QList<Favorite> favorites;
	favorites.append(Favorite("tag_text", 50, QDateTime::currentDateTime()));

	QCOMPARE(tag.stylished(favorites), QString("<span style=\"color:pink\">tag_text</span>"));
}

void TagTest::testStylishedNotFavorite()
{
	m_settings->setValue("Coloring/Fonts/artists", ",8.25,-1,5,50,0,0,0,0,0");
	m_settings->setValue("Coloring/Colors/artists", "#aa0000");

	Tag tag(m_settings, "tag_text", "artist", 123, QStringList() << "related1" << "related2" << "related3");

	QList<Favorite> favorites;
	favorites.append(Favorite("tag_other", 50, QDateTime::currentDateTime()));

	QString expected = "<a href=\"tag_text\" style=\"color:#aa0000; font-family:''; font-size:8pt; font-style:normal; font-weight:400; text-decoration:none;\">tag_text</a>";
	QCOMPARE(tag.stylished(favorites), expected);
}

void TagTest::testCompare()
{
	Tag tag1(m_settings, "artist1", "artist", 1, QStringList() << "tag1");
	Tag tag2(m_settings, "artist1", "artist", 2, QStringList() << "tag2");
	Tag tag3(m_settings, "artist2", "artist", 3, QStringList() << "tag3");
	Tag tag4(m_settings, "artist1", "character", 4, QStringList() << "tag4");
	Tag tag5(m_settings, "artist1", "unknown", 5, QStringList() << "tag5");

	QCOMPARE(tag1 == tag1, true);
	QCOMPARE(tag1 == tag2, true);
	QCOMPARE(tag1 == tag3, false);
	QCOMPARE(tag1 == tag4, false);
	QCOMPARE(tag1 == tag5, true);
}

static TagTest instance;
