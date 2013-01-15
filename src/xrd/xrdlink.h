#ifndef QTXXRD_LINK_H
#define QTXXRD_LINK_H

#include "xrdglobal.h"
#include "xrdproperty.h"
#include <QtxXml>
#include <QtCore>

QTX_BEGIN_NAMESPACE


class XrdLinkPrivate;

class XrdLink : public QObject,
                public IXmlDeserializing
{
    Q_OBJECT
    
public:
    static QString xmlNamespaceUri();
    static QString xmlName();
    
public:
    XrdLink(QObject *parent = 0);
    ~XrdLink();
    
    QUrl href() const;
    QString type() const;
    QString rel() const;
    QString uriTemplate() const;
    QString title() const;
    XrdPropertyList properties() const;

    void setHref(const QUrl & url);
    void setType(const QString & type);
    void setRel(const QString & rel);
    void setUriTemplate(const QString & uriTemplate);
    void setTitle(const QString & title);
    
    
    virtual IXmlDeserializing *deserializeXmlStartElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlEndElement(XmlDeserializer *deserializer, const QStringRef & namespaceUri, const QStringRef & name);
    virtual void deserializeXmlAttributes(XmlDeserializer *deserializer, const QXmlStreamAttributes & attributes);
    virtual void deserializeXmlCharacters(XmlDeserializer *deserializer, const QStringRef & text);
    
protected:
    XrdLinkPrivate *d_ptr;
private:
    Q_DECLARE_PRIVATE(XrdLink);
};

typedef QList<XrdLink *> XrdLinkList;


QTX_END_NAMESPACE

#endif // QTXXRD_PROPERTY_H
