#ifndef CARDDATABASE_H
#define CARDDATABASE_H

#include <QHash>
#include <QPixmap>
#include <QMap>
#include <QDataStream>
#include <QList>
#include <QXmlStreamReader>
#include <QNetworkRequest>
#include <QThread>
#include <QMutex>

class CardDatabase;
class CardInfo;
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;

class CardSet : public QList<CardInfo *> {
private:
	QString shortName, longName;
	unsigned int sortKey;
public:
	CardSet(const QString &_shortName = QString(), const QString &_longName = QString());
	QString getShortName() const { return shortName; }
	QString getLongName() const { return longName; }
	int getSortKey() const { return sortKey; }
	void setSortKey(unsigned int _sortKey);
	void updateSortKey();
};

class SetList : public QList<CardSet *> {
private:
	class CompareFunctor;
public:
	void sortByKey();
};

class PictureLoadingThread : public QThread {
	Q_OBJECT
private:
	QString _picsPath;
        QList<QPair<CardInfo*, bool> > loadQueue;
	QMutex mutex;
protected:
	void run();
public:
	PictureLoadingThread(QObject *parent);
	~PictureLoadingThread();
	void setPicsPath(const QString &path);
        void loadImage(CardInfo *card, bool stripped);
signals:
        void imageLoaded(CardInfo *card, const QImage &image, bool stripped);
};

class CardInfo : public QObject {
	Q_OBJECT
private:
	CardDatabase *db;

	QString name;
	SetList sets;
	QString manacost;
	QString cardtype;
	QString powtough;
	QString text;
	QStringList colors;
        QString picURL, picHqURL, picStURL;
	bool cipt;
	int tableRow;
	QPixmap *pixmap;
        QPixmap *pixmapSt;
	QMap<int, QPixmap *> scaledPixmapCache;
        QMap<int, QPixmap *> scaledPixmapStCache;
public:
	CardInfo(CardDatabase *_db,
		const QString &_name = QString(),
		const QString &_manacost = QString(),
		const QString &_cardtype = QString(),
		const QString &_powtough = QString(),
		const QString &_text = QString(),
		const QStringList &_colors = QStringList(),
		bool cipt = false,
		int _tableRow = 0,
		const SetList &_sets = SetList(),
                const QString &_picURL = QString(),
                const QString &_picHqURL = QString(),
                const QString &_picStURL = QString());
	~CardInfo();
	const QString &getName() const { return name; }
	const SetList &getSets() const { return sets; }
	const QString &getManaCost() const { return manacost; }
	const QString &getCardType() const { return cardtype; }
	const QString &getPowTough() const { return powtough; }
	const QString &getText() const { return text; }
	bool getCipt() const { return cipt; }
	void setText(const QString &_text) { text = _text; }
	const QStringList &getColors() const { return colors; }
	const QString &getPicURL() const { return picURL; }
        const QString &getPicHqURL() const { return picHqURL; }
        const QString &getPicStURL() const { return picStURL; }
	QString getMainCardType() const;
	QString getCorrectedName() const;
	int getTableRow() const { return tableRow; }
	void setTableRow(int _tableRow) { tableRow = _tableRow; }
	void setPicURL(const QString &_picURL) { picURL = _picURL; }
        void setPicHqURL(const QString &_picHqURL) { picHqURL = _picHqURL; }
        void setPicStURL(const QString &_picStURL) { picStURL = _picStURL; }
        void addToSet(CardSet *set);
        QPixmap *loadPixmap(bool stripped);
        QPixmap *getPixmap(QSize size, bool stripped);
	void clearPixmapCache();
        void clearPixmapStCache();
	void clearPixmapCacheMiss();
        void imageLoaded(const QImage &image, bool stripped);
public slots:
        void updatePixmapCache(bool stripped);
signals:
	void pixmapUpdated();
};

class CardDatabase : public QObject {
	Q_OBJECT
protected:
	QHash<QString, CardInfo *> cardHash;
	QHash<QString, CardSet *> setHash;
	QNetworkAccessManager *networkManager;
        QList<QPair<CardInfo *, bool> > cardsToDownload;
        QPair<CardInfo *, bool> cardBeingDownloaded;
	bool downloadRunning;
	bool loadSuccess;
        bool failLQ;
	CardInfo *noCard;
	PictureLoadingThread *loadingThread;
private:
	void loadCardsFromXml(QXmlStreamReader &xml);
	void loadSetsFromXml(QXmlStreamReader &xml);
	void startNextPicDownload();
public:
	CardDatabase(QObject *parent = 0);
	~CardDatabase();
	void clear();
	CardInfo *getCard(const QString &cardName = QString());
	CardSet *getSet(const QString &setName);
	QList<CardInfo *> getCardList() const { return cardHash.values(); }
	SetList getSetList() const;
	bool loadFromFile(const QString &fileName);
	bool saveToFile(const QString &fileName);
        void startPicDownload(CardInfo *card, bool stripped);
	QStringList getAllColors() const;
	QStringList getAllMainCardTypes() const;
	bool getLoadSuccess() const { return loadSuccess; }
        void cacheCardPixmaps(const QStringList &cardNames);
        void loadImage(CardInfo *card, bool stripped);
public slots:
	void clearPixmapCache();
        void clearPixmapStCache();
	bool loadCardDatabase(const QString &path);
	bool loadCardDatabase();
private slots:
	void picDownloadFinished(QNetworkReply *reply);
	void picDownloadChanged();
        void imageLoaded(CardInfo *card, QImage image, bool stripped);
};

#endif
